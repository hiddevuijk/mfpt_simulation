import numpy as np
import matplotlib.pyplot as plt


y = np.loadtxt('y.dat')
yn = np.loadtxt('yn.dat')
x = np.loadtxt('x.dat')
plt.subplot(2,1,1)
plt.scatter(x,y)

plt.subplot(2,1,2)
plt.scatter(x,yn)

plt.show()




