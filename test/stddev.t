#! /usr/bin/env perl
################################################################################
## anomaly - Anomalous data detection
##
## Copyright 2013 - 2014, Göteborg Bit Factory.
##
## Permission is hereby granted, free of charge, to any person obtaining a copy
## of this software and associated documentation files (the "Software"), to deal
## in the Software without restriction, including without limitation the rights
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
## copies of the Software, and to permit persons to whom the Software is
## furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included
## in all copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
## OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
## THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.
##
## http://www.opensource.org/licenses/mit-license.php
##
################################################################################

use strict;
use warnings;
use Test::More tests => 6;

# anomaly --stddev --sample 5,  1 2 3 4 5 6 -> Anomaly
# The sequence 1 2 3 4 5 has mean 3, sigma 1.58.
my $output = qx{echo '1' | ../src/anomaly --stddev --sample 5 --coefficient 1.0};
is ($output, '', 'stddev (sample 5 coeff 1.0) 1 -->');
$output = qx{echo '1 2' | ../src/anomaly --stddev --sample 5 --coefficient 1.0};
is ($output, '', 'stddev (sample 5 coeff 1.0) 1 2 -->');
$output = qx{echo '1 2 3' | ../src/anomaly --stddev --sample 5 --coefficient 1.0};
is ($output, '', 'stddev (sample 5 coeff 1.0) 1 2 3 -->');
$output = qx{echo '1 2 3 4' | ../src/anomaly --stddev --sample 5 --coefficient 1.0};
is ($output, '', 'stddev (sample 5 coeff 1.0) 1 2 3 4 -->');
$output = qx{echo '1 2 3 4 5' | ../src/anomaly --stddev --sample 5 --coefficient 1.0};
is ($output, '', 'stddev (sample 5 coeff 1.0) 1 2 3 4 5 -->');
$output = qx{echo '1 2 3 4 5 6' | ../src/anomaly --stddev --sample 5 --coefficient 1.0};
like ($output, qr/Anomalous data detected/, 'stddev (sample 5 coeff 1.0) 1 2 3 4 5 6 --> Anomaly');

exit 0;

