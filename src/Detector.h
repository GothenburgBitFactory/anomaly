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

#ifndef INCLUDED_DETECTOR_H
#define INCLUDED_DETECTOR_H

#include <string>

class Detector
{
public:
  Detector () = default;
  void algorithm (const std::string&);
  void max (double);
  void min (double);
  void sample (int);
  void coefficient (double);
  void quiet ();
  void execute (const std::string&);
  void pid (int);
  void debug ();

  void run () const;

private:
  void run_threshold () const;
  void run_stddev () const;
  void react (const std::string&) const;
  void react_complain (const std::string&) const;
  void react_execute () const;
  void react_sigusr1 () const;

private:
  std::string _algorithm   {"stddev"};
  bool        _use_max     {false};
  bool        _use_min     {false};
  double      _max         {0.0};
  double      _min         {0.0};
  int         _sample      {10};
  double      _coefficient {1.0};
  bool        _quiet       {false};
  std::string _script      {};
  int         _pid         {0};
  bool        _debug       {false};
};

#endif
////////////////////////////////////////////////////////////////////////////////
