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

class TestThreshold(TestCase):
    def setUp(self):
        """Executed before each test in the class"""
        self.t = Anomaly()

    def test_threshold_max_unexceeded_1(self):
        """Test threshold max unexceeded, 1 data point"""
        code, out, err = self.t("--threshold --max 3.14", input="1\n")
        self.assertEqual(out, '')

    def test_threshold_max_unexceeded_2(self):
        """Test threshold max unexceeded, 2 data points"""
        code, out, err = self.t("--threshold --max 3.14", input="1 2\n")
        self.assertEqual(out, '')

    def test_threshold_max_unexceeded_3(self):
        """Test threshold max unexceeded, 3 data points"""
        code, out, err = self.t("--threshold --max 3.14", input="1 2 3\n")
        self.assertEqual(out, '')

    def test_threshold_max_unexceeded_4(self):
        """Test threshold max exceeded, 4 data points"""
        code, out, err = self.t("--threshold --max 3.14", input="1 2 3 4\n")
        self.assertIn('Anomalous data detected.  The value 4 is above the maximum of 3.14.', out)

    def test_threshold_min_unexceeded_1(self):
        """Test threshold min unexceeded, 1 data point"""
        code, out, err = self.t("--threshold --min 3.14", input="4\n")
        self.assertEqual(out, '')

    def test_threshold_min_unexceeded_2(self):
        """Test threshold min exceeded, 2 data points"""
        code, out, err = self.t("--threshold --min 3.14", input="4 3\n")
        self.assertIn('Anomalous data detected.  The value 3 is below the minimum of 3.14.', out)

    def test_execute_no_output(self):
        """Test execute, no output generated"""
        code, out, err = self.t("--threshold --max 2 --execute 'echo hello' --quiet", input="1\n")
        self.assertEqual(out, '')

    def test_execute_output(self):
        """Test execute, output generated"""
        code, out, err = self.t("--threshold --max 2 --execute 'echo hello' --quiet", input="3\n")
        self.assertIn('hello', out)

if __name__ == "__main__":
    from simpletap import TAPTestRunner
    unittest.main(testRunner=TAPTestRunner())

# vim: ai sts=4 et sw=4 ft=python
