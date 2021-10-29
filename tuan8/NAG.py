import numpy as np

def grad(x):
	return 2*x + 10*np.cos(x)

def cost(x):
	return x**2 + 10*np.sin(x)

def NAG(theta_init, alpha = 0.1, beta = 0.9, esilon = 1e-4, loop = 10000):
	theta = [theta_init]
	v_o = np.zeros_like(theta_init)
	for i in range(loop):
		v_n = beta*v_o + alpha*grad(theta[-1] - beta*v_o)
		theta_n = theta[-1] - v_n
		if (abs(theta[-1] - theta_n) < esilon):
		    break
		theta.append(theta_n)
		v_o = v_n
	return (theta, i)

(x, it) = NAG(5)
print('x = %f, cost = %f, i = %d'%(x[-1], cost(x[-1]), it))