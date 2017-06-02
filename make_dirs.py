import numpy as np


R0 = 49.99
Dt = 1./30
a = 10
R = 50
N = 100
seed = 123456789

DrList = [1./10,1./20,1./30,1./40]
dList = [0.,0.01,0.05,0.25]
cList = [0.,50.,100.,150.,200.,250.,300.]

infofile = open("simulation_parameters.txt",'w')
infofile.write("DrList = [1./10,1./20,1./30,1./40]")
infofile.write("dList = [0.,0.01,0.05,0.25]")
infofile.write("cList = [0.,50.,100.,150.,200.,250.,300.]")
infofile.close()

for Dr in DrList:
	for d in dList:
		for c in cList:
			name = 
			of = open("file.txt",'w')

			of.write("R0=\n49.99")
			of.write("Dr=\n%2f" % Dr)

			of.close()






