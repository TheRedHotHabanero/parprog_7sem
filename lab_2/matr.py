import numpy as np
import sys

size = int(sys.argv[1])

step = 1.0 / size

matrix = np.zeros((size, size))
mid = -2.0 / (step * step)
side = 1.0 / (step * step)
matrix[0, 0] = mid;
matrix[0, 1] = side;
matrix[-1, -1] = mid;
matrix[-1, -2] = side;
for i in range(size - 2):
  matrix[i + 1][i] = side;
  matrix[i + 1][i + 1] = mid;
  matrix[i + 1][i + 2] = side;

inverse_array = np.linalg.inv(matrix)
for vec in inverse_array:
  for elem in vec:
    print(elem)