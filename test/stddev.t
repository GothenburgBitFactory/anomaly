#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-
###############################################################################
#
# Copyright 2006 - 2016, Paul Beckingham, Federico Hernandez.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# http://www.opensource.org/licenses/mit-license.php
#
###############################################################################

import sys
import os
import unittest
from datetime import datetime
# Ensure python finds the local simpletap module
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from basetest import Anomaly, TestCase

# Test methods available:
#     self.assertEqual(a, b)
#     self.assertNotEqual(a, b)
#     self.assertTrue(x)
#     self.assertFalse(x)
#     self.assertIs(a, b)
#     self.assertIsNot(substring, text)
#     self.assertIsNone(x)
#     self.assertIsNotNone(x)
#     self.assertIn(substring, text)
#     self.assertNotIn(substring, text
#     self.assertRaises(e)
#     self.assertRegexpMatches(text, pattern)
#     self.assertNotRegexpMatches(text, pattern)
#     self.tap("")

class TestBugNumber(TestCase):
    def setUp(self):
        """Executed before each test in the class"""
        self.t = Anomaly()

    def test_stddev_1_data_point(self):
        """Test stddev with 1 data point"""
        code, out, err = self.t("--stddev --sample 5 --coefficient 1.0", input="1\n")
        self.assertEqual(out, '')

    def test_stddev_2_data_points(self):
        """Test stddev with 2 data points"""
        code, out, err = self.t("--stddev --sample 5 --coefficient 1.0", input="1 2\n")
        self.assertEqual(out, '')

    def test_stddev_3_data_points(self):
        """Test stddev with 3 data points"""
        code, out, err = self.t("--stddev --sample 5 --coefficient 1.0", input="1 2 3\n")
        self.assertEqual(out, '')

    def test_stddev_4_data_points(self):
        """Test stddev with 4 data points"""
        code, out, err = self.t("--stddev --sample 5 --coefficient 1.0", input="1 2 3 4\n")
        self.assertEqual(out, '')

    def test_stddev_5_data_points(self):
        """Test stddev with 5 data points"""
        code, out, err = self.t("--stddev --sample 5 --coefficient 1.0", input="1 2 3 4 5\n")
        self.assertEqual(out, '')

    def test_stddev_6_data_points(self):
        """Test stddev with 6 data points"""
        code, out, err = self.t("--stddev --sample 5 --coefficient 1.0", input="1 2 3 4 5 6\n")
        self.assertIn('The value 6 is more than 1 sigma(s) above the mean value 3, with a sample size of 5.', out)

if __name__ == "__main__":
    from simpletap import TAPTestRunner
    unittest.main(testRunner=TAPTestRunner())

# vim: ai sts=4 et sw=4 ft=python
