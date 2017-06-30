import numpy as np
import matplotlib.pyplot as plt
from sys import exit

Nbin = 100

l = np.loadtxt('position.dat')
o = np.loadtxt('orientation.dat')
print 'read'
x_bin = np.linspace(10,50,Nbin);
y_sum = np.zeros(Nbin);
y_N = np.zeros(Nbin);

'''
plt.plot(range(len(l)),l)
plt.show()
exit()
'''

for i in range(len(l)):
	xi = 0;
	while x_bin[xi] < l[i]:
		xi+=1
		if xi >= Nbin:
			xi -= 1
			break
	y_sum[xi] += o[i]
	y_N[xi] += 1.
print 's1'

binsize = x_bin[1] - x_bin[0]
for i in range(Nbin):
	if y_N[i] > 0.:
		y_sum[i] /= y_N[i]
		x_bin[i] += 0.5*binsize
		plt.scatter(x_bin[i],y_sum[i],color='blue')
	else:
		x_bin[i] += 0.5*binsize
		plt.scatter(x_bin[i],0.,color='red')
plt.show()




