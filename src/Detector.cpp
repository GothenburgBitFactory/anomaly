////////////////////////////////////////////////////////////////////////////////
// Detector - Anomalous data detection
//
// Copyright 2013, Göteborg Bit Factory.
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
#include <iostream>
#include <deque>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <Detector.h>

////////////////////////////////////////////////////////////////////////////////
Detector::Detector ()
: _algorithm ("stddev")
, _use_upper (false)
, _use_lower (false)
, _upper (0.0)
, _lower (0.0)
, _sample (10)
, _coefficient (1.0)
, _quiet (false)
, _script ("")
, _pid (0)
{
}

////////////////////////////////////////////////////////////////////////////////
void Detector::algorithm (const std::string& value)
{
  if (value != "stddev" &&
      value != "threshold")
    throw std::string ("Unrecognized algorithm '") + value + "' specified.";

  _algorithm = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::upper (double value)
{
  if (_use_lower && value < _lower)
    throw std::string ("The upper value must be higher than the lower value.");

  _use_upper = true;
  _upper = value;
}

////////////////////////////////////////////////////////////////////////////////
void Detector::lower (double value)
{
  if (_use_upper && value > _upper)
    throw std::string ("The lower value must be lower than the upper value.");

  _use_lower = true;
  _lower = value;
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
void Detector::run ()
{
       if (_algorithm == "threshold") run_threshold ();
  else if (_algorithm == "stddev")    run_stddev ();
}

////////////////////////////////////////////////////////////////////////////////
void Detector::run_threshold ()
{
  // Make sure settings are acceptable.
  if (!_use_upper && !_use_lower)
    throw std::string ("A lower, and upper, or both threshold values should be "
                       "specified.");

  if (_quiet &&
      _pid == 0 &&
      _script == "")
    throw std::string ("A reaction must be specified.");

  double input;
  while (std::cin >> input)
    if ((_use_upper && input >= _upper) ||
        (_use_lower && input <= _lower))
      react ();
}

////////////////////////////////////////////////////////////////////////////////
void Detector::run_stddev ()
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
  double input;
  while (std::cin >> input)
  {
    if (data.size () >= _sample)
    {
      // Calculate mean, standard deviation.
      double sum = 0.0;
      double sum_squares = 0.0;
      std::deque <double>::iterator i;
      for (i = data.begin (); i != data.end (); ++i)
      {
        sum += *i;
        sum_squares += (*i) * (*i);
      }

      double sigma = sqrt (((_sample * sum_squares) - (sum * sum)) /
                           (_sample * (_sample - 1)));
      double mean = sum / _sample;

      if ((input < (mean - (_coefficient * sigma))) ||
          (input > (mean + (_coefficient * sigma))))
        react ();
    }

    data.push_back (input);
    if (data.size () > _sample)
      data.pop_front ();
  }
}

////////////////////////////////////////////////////////////////////////////////
void Detector::react ()
{
  react_complain ();
  react_sigusr1 ();
  react_execute ();
}

////////////////////////////////////////////////////////////////////////////////
void Detector::react_complain ()
{
  if (!_quiet)
  {
    std::cout << "Anomaly\n";
  }
}

////////////////////////////////////////////////////////////////////////////////
void Detector::react_execute ()
{
  if (_pid)
  {
    kill (_pid, SIGUSR1);
  }
}

////////////////////////////////////////////////////////////////////////////////
void Detector::react_sigusr1 ()
{
  if (_script != "")
  {
    system (_script.c_str ());
  }
}

////////////////////////////////////////////////////////////////////////////////
