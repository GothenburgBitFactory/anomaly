////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013 - 2017, Göteborg Bit Factory.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#include <cmake.h>
#include <Detector.h>
#include <iostream>
#include <sstream>
#include <deque>
#include <cstdlib>
#include <cmath>
#include <csignal>

////////////////////////////////////////////////////////////////////////////////
void Detector::algorithm (const std::string& value)
{
  if (value != "stddev" && value != "threshold")
    throw std::string ("Unrecognized algorithm '") + value + "' specified.";

  _algorithm = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::max (double value)
{
  if (_use_min &&value < _min)
    throw std::string ("The max value must be higher than the min value.");

  _use_max = true;
  _max = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::min (double value)
{
  if (_use_max && value > _max)
    throw std::string ("The min value must be lower than the max value.");

  _use_min = true;
  _min = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::sample (int value)
{
  if (value < 2)
    throw std::string ("Sample size must be greater than 1.");

  _sample = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::coefficient (double value)
{
  _coefficient = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::quiet ()
{
  _quiet = true;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::execute (const std::string& value)
{
  if (value == "")
    throw std::string ("A non-trivial path must be specified.");

  _script = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::pid (int value)
{
  if (value == 0)
    throw std::string ("A non-zero PID must be specified.");

  _pid = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::debug ()
{
  _debug = true;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::run () const
{
       if (_algorithm == "threshold") run_threshold ();
  else if (_algorithm == "stddev")    run_stddev ();
}

////////////////////////////////////////////////////////////////////////////////
void Detector::run_threshold () const
{
  // Make sure settings are acceptable.
  if (! _use_max && !_use_min)
    throw std::string ("A min, and max, or both threshold values should be "
                       "specified.");

  if (_quiet && _pid == 0 && _script == "")
    throw std::string ("A reaction must be specified.");

  long long counter {0};
  double input;
  while (std::cin >> input)
  {
    ++counter;
    if (_debug)
    {
      std::cout << "[" << counter << "] ";

      if (_use_min)
        std::cout << "min " << _min << " <= ";

      std::cout << "value " << input;

      if (_use_max)
        std::cout << " <= max " << _max;

      if (_use_min && input < _min)
        std::cout << " = Anomaly\n";

      else if (_use_max && input > _max)
        std::cout << " = Anomaly\n";

      else
        std::cout << " = Nominal\n";
    }

    if (_use_max && input > _max)
    {
      std::stringstream s;
      s << "Anomalous data detected.  The value "
        << input
        << " is above the maximum of "
        << _max
        << ".";
      react (s.str ());
    }
    else if (_use_min && input < _min)
    {
      std::stringstream s;
      s << "Anomalous data detected.  The value "
        << input
        << " is below the minimum of "
        << _min
        << ".";
      react (s.str ());
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
void Detector::run_stddev () const
{
  // Make sure settings are acceptable.
  if (_sample < 2)
    throw std::string ("A sample size of 2 or more must be specified.");

  if (_coefficient < 1e-6)
    throw std::string ("A non-trivial coefficient should be specified.");

  if (_quiet &&
      _pid == 0 &&
      _script == "")
    throw std::string ("A reaction must be specified.");

  std::deque <double> data;
  long long counter {0};
  double input;
  while (std::cin >> input)
  {
    ++counter;
    if (data.size () >= static_cast<unsigned int> (_sample))
    {
      // Calculate mean, standard deviation.
      double sum = 0.0;
      double sum_squares = 0.0;
      for (auto& i : data)
      {
        sum += i;
        sum_squares += i * i;
      }

      double sigma = sqrt (((_sample * sum_squares) - (sum * sum)) /
                           (_sample * (_sample - 1)));
      double mean = sum / _sample;

      if (input < (mean - (_coefficient * sigma)))
      {
        if (_debug)
          std::cout << "[" << counter << "] "
                    << "mean " << mean
                    << ", sigma " << sigma
                    << ", coeff " << _coefficient
                    << ", value " << input
                    << " < " << (mean - (_coefficient * sigma))
                    << " = Anomaly\n";

        std::stringstream s;
        s << "Anomalous data detected.  The value "
          << input
          << " is more than "
          << _coefficient
          << " sigma(s) below the mean value "
          << mean
          << ", with a sample size of "
          << _sample
          << ".";
        react (s.str ());
      }
      else if (input > (mean + (_coefficient * sigma)))
      {
        if (_debug)
          std::cout << "[" << counter << "] "
                    << "mean " << mean
                    << ", sigma " << sigma
                    << ", coeff " << _coefficient
                    << ", value " << input
                    << " > " << (mean + (_coefficient * sigma))
                    << " = Anomaly\n";

        std::stringstream s;
        s << "Anomalous data detected.  The value "
          << input
          << " is more than "
          << _coefficient
          << " sigma(s) above the mean value "
          << mean
          << ", with a sample size of "
          << _sample
          << ".";
        react (s.str ());
      }
      else
      {
        if (_debug)
          std::cout << "[" << counter << "] "
                    << "mean " << mean
                    << ", sigma " << sigma
                    << ", coeff " << _coefficient
                    << ", " << (mean - (_coefficient * sigma))
                    << " <= value " << input
                    << " <= " << (mean + (_coefficient * sigma))
                    << " = Nominal\n";
      }
    }
    else
    {
      if (_debug)
        std::cout << "[" << counter << "] "
                  << "value " << input
                  << ", insufficient data - need " << _sample << " items\n";
    }

    data.push_back (input);
    if (data.size () > static_cast<unsigned int> (_sample))
      data.pop_front ();
  }
}

////////////////////////////////////////////////////////////////////////////////
void Detector::react (const std::string& message) const
{
  react_complain (message);
  react_sigusr1 ();
  react_execute ();
}

////////////////////////////////////////////////////////////////////////////////
void Detector::react_complain (const std::string& message) const
{
  if (!_quiet)
    std::cout << message << "\n";
}

////////////////////////////////////////////////////////////////////////////////
void Detector::react_execute () const
{
  if (_script != "")
    system (_script.c_str ());
}

////////////////////////////////////////////////////////////////////////////////
void Detector::react_sigusr1 () const
{
  if (_pid)
    kill (_pid, SIGUSR1);
}

////////////////////////////////////////////////////////////////////////////////
