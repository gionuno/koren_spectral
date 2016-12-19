#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Mon Dec 19 14:00:02 2016

@author: gionuno
"""

import numpy as np;
import struct;

name = raw_input("name:");

A = np.load(name+".npy");
np.savetxt(name+".csv",A, delimiter=", ");