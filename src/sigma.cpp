////////////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <math.h>

int main (int argc, char** argv)
{
  int rc = 0;

  // TODO Populate data: read from stdin, if present.
  // TODO Populate data: read from args, if present.
  std::vector <double> data;


  // Calculate mean, standard deviation.
  double sum = 0.0;
  double sum_squares = 0.0;
  std::vector <double>::iterator i;
  for (i = data.begin (); i != data.end (); ++i)
  {
    sum += *i;
    sum_squares += (*i) * (*i);
  }

  int n = data.size ();

  double sigma = 0.0;
  if (n > 1)
    sigma = sqrt (((n * sum_squares) - (sum * sum)) / (n * (n - 1)));

  double mean = sum / n;

  std::cout << mean  << "\n"
            << sigma << "\n";

  return rc;
}

////////////////////////////////////////////////////////////////////////////////

