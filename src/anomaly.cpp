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
#include <stdlib.h>
#include <anomaly.h>
#include <cmake.h>
#include <commit.h>

////////////////////////////////////////////////////////////////////////////////
static int usage ()
{
  std::cout << "\n"
            << "Usage: anomaly [options]\n"
            << "\n"
            << "Options:\n"
            << "  -h|--help         Show this message\n"
            << "  -v|--version      Show anomaly version & copyright\n"
            << "  -s|--stddev       Standard Deviation algorithm (default)\n"
            << "  -t|--threshold    Threshold algorithm\n"
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
  try
  {
    // Process command line arguments.
    std::string algorithm = "stddev";
    int sample            = 5;
    double coefficient    = 1.0;
    double limit          = 1.0;
    bool over             = true;

    for (int i = 1; i < argc; ++i)
    {
      if (!strcmp (argv[i], "-h") || !strcmp (argv[i], "--help"))
        return usage ();

      else if (!strcmp (argv[i], "-v") || !strcmp (argv[i], "--version"))
        return version ();

      else if (!strcmp (argv[i], "-s") || !strcmp (argv[i], "--stddev"))
        algorithm = "stddev";

      else if (!strcmp (argv[i], "-t") || !strcmp (argv[i], "--threshold"))
        algorithm = "threshold";

      else if (!strcmp (argv[i], "-o") || !strcmp (argv[i], "--over"))
      {
        limit = strtod (argv[++i], NULL);
        over = true;
      }

      else if (!strcmp (argv[i], "-u") || !strcmp (argv[i], "--under"))
      {
        limit = strtod (argv[++i], NULL);
        over = false;
      }

      else if (!strcmp (argv[i], "-n") || !strcmp (argv[i], "--sample"))
        sample = strtol (argv[++i], NULL, 10);

/*
      else error?
*/
    }

    // Dispatch to selected algorithm.
         if (algorithm == "stddev")    return algorithm_sigma ();
    else if (algorithm == "threshold") return algorithm_threshold (limit, over);
  }

  catch (const std::string& error)
  {
    std::cout << error << "\n";
    return -1;
  }

  catch (...)
  {
    std::cout << "Unknown error\n";
    return -2;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////

