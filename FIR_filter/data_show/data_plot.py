# -*- coding: utf-8 -*-
"""
Created on Mon May 17 23:22:57 2021

@author: fbasatemur
"""

import matplotlib.pyplot as plt
import numpy as np

f = open("1000HzSin.txt", "r")

arry = f.readlines()
arry = np.array(arry)
arry = arry.astype("float64")

f.close()

f1 = open("400HzSin.txt", "r")

arry1 = f1.readlines()
arry1 = np.array(arry1)
arry1 = arry1.astype("float64")

f1.close()

f2 = open("1KHz_400HzSin.txt", "r")

arry2 = f2.readlines()
arry2 = np.array(arry2)
arry2 = arry2.astype("float64")

f2.close()

f3 = open("result.txt", "r")

arry3 = f3.readlines()
arry3 = np.array(arry3)
arry3 = arry3.astype("float64")

f3.close()


size = range(100)
size = np.array(size)

fig, axs = plt.subplots(4)

axs[0].plot(size, arry, "tab:blue")
axs[0].set_title("1000Hz Sin")

axs[1].plot(size, arry1, "tab:blue")
axs[1].set_title("400Hz Sin")

axs[2].plot(size, arry2, "tab:green")
axs[2].set_title("1000Hz + 400 Hz Sin")

axs[3].plot(size, arry3, "tab:red")
axs[3].set_title("Filtering result")

fig.tight_layout()

plt.show()
