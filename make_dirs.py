import numpy as np

mfpt = 1
R0 = 49.99
Dt = 1./30
a = 10
R = 50
N = 5
seed = 123456789
d = 0.
dt = 0.01
DrList = [1./2,1./10,1./50]
cList = [0.,50.,100.,150.,200.,250.,300.]


avg = 0
#avg = 3*c*(R-a)/(b*b*b-a*a*a)

if_names = open("if_names.txt",'w')
for Dr in DrList:
	for c in cList:
		avg_ = 0
		if avg>0.: avg_ = 1 
		name = "mftp_"+str(mfpt)+"_avg_"+str(avg_) +"_Dr_" + str(int(100*Dr))+"_c_"+str(int(c))
		if_names.write(name+"\n")
		infile = open(name+".txt",'w')
		infile.write("mfpt=\n%i\n" % mfpt)
		infile.write("r0=\n%f\n" % R0)
		infile.write("Dr=\n%f\n" % Dr)
		infile.write("Dt=\n%f\n" % Dt)
		infile.write("c=\n%f\n" % c)
		infile.write("avg=\n%f\n" % avg)
		infile.write("d=\n%f\n" % d)
		infile.write("a=\n%f\n" % a)
		infile.write("R=\n%f\n" % R)
		infile.write("dt=\n%f\n" % dt)
		infile.write("N=\n%i\n" % N)
		infile.write("seed=\n%i\n" % seed)
		infile.write("name=\n" + name)

		infile.close()






