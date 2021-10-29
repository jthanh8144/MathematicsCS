import numpy as np
np.random.seed(2)

def cost(w):
	return .5/Xbar.shape[0]*np.linalg.norm(y - Xbar.dot(w), 2)**2;

def grad(w):
	return 1/Xbar.shape[0] * Xbar.T.dot(Xbar.dot(w) - y)

def sgrad(w, i, rd_id, n = 50):
    true_i = rd_id[i]
    xi = Xbar[true_i, : i+n]
    yi = y[true_i, :i + n]
    a = np.dot(xi, w) - yi
    return (xi*a).reshape(2, 1)

def MiniGD(w_init, grad, eta):
    w = [w_init]
    w_last_check = w_init
    iter_check_w = 10
    N = X.shape[0]
    count = 0
    for it in range(10):
        # shuffle data 
        rd_id = np.random.permutation(N)
        for i in range(N):
            count += 1 
            g = sgrad(w[-1], i, rd_id)
            w_new = w[-1] - eta*g
            w.append(w_new)
            if count%iter_check_w == 0:
                w_this_check = w_new                 
                if np.linalg.norm(w_this_check - w_last_check)/len(w_init) < 1e-3:
                    return w
                w_last_check = w_this_check
    return w

X = np.random.rand(1000, 1)
y = 4 + 3 * X + .2*np.random.randn(1000, 1)

one = np.ones((X.shape[0],1))
Xbar = np.concatenate((one, X), axis = 1)

w_init = np.array([[2], [1]])
w = MiniGD(w_init, grad, .1)

print(w[-1])