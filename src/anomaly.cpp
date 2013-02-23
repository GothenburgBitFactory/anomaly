////////////////////////////////////////////////////////////////////////////////
// anomaly - Anomalous data detection
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
#include <anomaly.h>
#include <cmake.h>
#include <commit.h>

////////////////////////////////////////////////////////////////////////////////
static int usage ()
{
  std::cout << "\n"
            << "Usage: anomaly [-h|--help] [-v|--version]\n"
            << "\n";

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
static int version ()
{
  std::cout << "\n"
            << PACKAGE_STRING
#if defined (HAVE_COMMIT)
            << "."
            << COMMIT
#endif
            << " built for "
#if defined (DARWIN)
            << "darwin"
#elif defined (SOLARIS)
            << "solaris"
#elif defined (CYGWIN)
            << "cygwin"
#elif defined (OPENBSD)
            << "openbsd"
#elif defined (HAIKU)
            << "haiku"
#elif defined (NETBSD)
            << "netbsd"
#elif defined (FREEBSD)
            << "freebsd"
#elif defined (LINUX)
            << "linux"
#else
            << "unknown"
#endif
            << "\n"
            << "Copyright (C) 2013 Göteborg Bit Factory\n"
            << "\n"
            << "Anomaly may be copied only under the terms of the MIT "
               "license, which may be found in the source kit.\n"
            << "\n"
            << "Documentation for anomaly can be found using 'man anomaly' "
               "or at http://tasktools.org/projects/anomaly.html\n"
            << "\n";

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
int main (int argc, char** argv)
{
  // TODO Process command line arguments.
  for (int i = 1; i < argc; ++i)
  {
    if (!strcmp (argv[i], "-h") || !strcmp (argv[i], "--help"))
      return usage ();

    else if (!strcmp (argv[i], "-v") || !strcmp (argv[i], "--version"))
      return version ();
    }

  // TODO Initialize input stream.
  // TODO Initialize output stream.
  // TODO Dispatch to selected algorithm.

  return 0;
}

////////////////////////////////////////////////////////////////////////////////

