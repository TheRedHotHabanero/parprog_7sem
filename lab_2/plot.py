#!/usr/bin/python3
import numpy  as np
import matplotlib
#matplotlib.use('Agg')
import matplotlib.pyplot as plt
import sys

def my_print(filename):
    data = np.loadtxt(filename)
    x = data[:, 0]
    y = data[:, 1]
    line = plt.plot(x, y)

    plt.ylim(bottom = 0)
    plt.setp(line, linewidth = 1)
    return

my_print(sys.argv[1])

plt.title("Решение задачи на плоскости")
plt.xlabel("x")
plt.ylabel("y")
plt.grid()
plt.tight_layout()
plt.savefig('Solution.png')
plt.show()

