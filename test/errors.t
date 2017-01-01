#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-
###############################################################################
#
# Copyright 2006 - 2017, Paul Beckingham, Federico Hernandez.
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

class TestErrors(TestCase):
    def setUp(self):
        """Executed before each test in the class"""
        self.t = Anomaly()

    def test_unrecognized_arg(self):
        """Test unrecognised argument"""
        code, out, err = self.t.runError("--foo")
        self.assertIn("Unrecognized argument '--foo'", out)

    def test_threshold_range_a(self):
        """Test inverted threshold range"""
        code, out, err = self.t.runError("--threshold --max 3.1 --min 3.2")
        self.assertIn("The min value must be lower than the max value.", out)

    def test_threshold_range_b(self):
        """Test inverted threshold range"""
        code, out, err = self.t.runError("--threshold --min 3.2 --max 3.1")
        self.assertIn("The max value must be higher than the min value.", out)

    def test_threshold_no_bounds(self):
        """Test threshold with no range"""
        code, out, err = self.t.runError("--threshold")
        self.assertIn("A min, and max, or both threshold values should be specified.", out)

    def test_stddev_small_sample(self):
        """Test stddev with a too-small sample"""
        code, out, err = self.t.runError("--stddev --sample 1")
        self.assertIn("Sample size must be greater than 1.", out)

    def test_execute_nothing(self):
        """Test execute with no path"""
        code, out, err = self.t.runError("--execute ''")
        self.assertIn("A non-trivial path must be specified.", out)

    def test_signal_no_pid(self):
        """Test signal a zero pid"""
        code, out, err = self.t.runError("--pid 0")
        self.assertIn("A non-zero PID must be specified.", out)

    def test_nothing(self):
        """Test no reaction"""
        code, out, err = self.t.runError("--quiet")
        self.assertIn("A reaction must be specified.", out)

    def test_nothing(self):
        """Test no reaction"""
        code, out, err = self.t.runError("--coefficient 0.0000001")
        self.assertIn("A non-trivial coefficient should be specified.", out)

if __name__ == "__main__":
    from simpletap import TAPTestRunner
    unittest.main(testRunner=TAPTestRunner())

# vim: ai sts=4 et sw=4 ft=python
