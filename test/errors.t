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
use Test::More tests => 9;

my $output = qx{../src/anomaly --foo};
like ($output, qr/Unrecognized/, 'Unrecognized arg -foo');

$output = qx{../src/anomaly --threshold --upper 3.1 --lower 3.2};
like ($output, qr/must be lower/, '--lower > --higher');

$output = qx{../src/anomaly --threshold --lower 3.2 --upper 3.1};
like ($output, qr/must be higher/, '--lower > --higher');

$output = qx{../src/anomaly --stddev --sample 1};
like ($output, qr/Sample size/, '--sample < 2');

$output = qx{../src/anomaly --execute ''};
like ($output, qr/non-trivial path/, '--execute \'\'');

$output = qx{../src/anomaly --pid 0};
like ($output, qr/non-zero/, '--pid 0');

$output = qx{../src/anomaly --threshold};
like ($output, qr/or both/, '--threshold, no bounds');

$output = qx{../src/anomaly --quiet};
like ($output, qr/reaction must be/, 'no reaction');

$output = qx{../src/anomaly --coefficient 0.0000001};
like ($output, qr/non-trivial coefficient/, '--coefficient 0.0000001');

exit 0;

