import numpy as np

A = np.array([[10, 0, 0, 0, -2, 0],[3,9,0,0,0,3],[0,7,8,7,0,0],[3,0,8,7,5,0],[0,8,0,9,9,13],[0,4,0,0,2,-1]])
x = np.array([1,2,3,4,5,6])
y = A.dot(x)
print(A)
print(x)
print(y)

A_pow = np.linalg.matrix_power(A,1000)
y2 = A_pow.dot(x)
print(y2)
