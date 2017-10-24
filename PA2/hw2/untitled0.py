#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct 24 16:49:28 2017

@author: luxihan
"""

import numpy as np
import matplotlib.pyplot as plt

file_name = "results.txt"
max_iter = 10000

np_map_raw = np.loadtxt("results.txt")
np_map = np.zeros((1000, 1000))
np_map[np_map_raw >= max_iter] = 1
np_map *= 0.5
plt.imshow(np_map, cmap='Greys')
plt.savefig('mset_plot.png')