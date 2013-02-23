#! /usr/bin/env perl
################################################################################
## anomaly - Anomalous data detection
##
## Copyright 2013, Göteborg Bit Factory.
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

# anomaly --threshold --over 3.14
my $output = qx{echo '1' | ../src/anomaly --threshold --over 3.14};
is ($output, '', 'threshold (over 3.14) 1 -->');

$output = qx{echo '1 2' | ../src/anomaly --threshold --over 3.14};
is ($output, '', 'threshold (over 3.14) 1 2 -->');

$output = qx{echo '1 2 3' | ../src/anomaly --threshold --over 3.14};
is ($output, '', 'threshold (over 3.14) 1 2 3 -->');

$output = qx{echo '1 2 3 4' | ../src/anomaly --threshold --over 3.14};
isnt ($output, '', 'threshold (over 3.14) 1 2 3 4 --> ALERT');

# anomaly --threshold --under 3.14
$output = qx{echo '4' | ../src/anomaly --threshold --under 3.14};
is ($output, '', 'threshold (under 3.14) 4 -->');

$output = qx{echo '4 3' | ../src/anomaly --threshold --under 3.14};
isnt ($output, '', 'threshold (under 3.14) 4 3 --> ALERT');

exit 0;

