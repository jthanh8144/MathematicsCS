import numpy as np

def get_norm(A):
    return np.sqrt(np.sum(np.square(A)))

def qr(A):
    m, n = A.shape
    Q = np.eye(m)
    for i in range(n - (m == n)):
        H = np.eye(m)
        #calculate Householder matrix i: rows and i: columns from A i: rows and ith column
        H[i:, i:] = make_householder(A[i:, i])
        Q = Q@H
        A = H@A
    return Q, A
 
def make_householder(A):
    u = A / (A[0] + np.copysign(get_norm(A), A[0]))
    u[0] = 1
    H = np.eye(A.shape[0])
    #finding Householder 
    H -= (2 / np.dot(u, u)) * u[:, None] @ u[None, :]
    return H

def find_eig_qr(A):
    pQ = np.eye(A.shape[0])
    X=A.copy()
    for i in range(20):
            Q,R = qr(X)
            pQ = pQ @ Q
            X = R @ Q
    return np.diag(X), pQ

def svd(A):
    _A = A.transpose() # transpose matrix
    # find left eigvectors and eigvalues
    B = A @ _A
    _,U = find_eig_qr(B)
    d = np.linalg.eig(B)
    # find right eigvectors
    _B = _A @ A
    eig, V = find_eig_qr(_B)
    # find singular values
    eig = np.sqrt(np.sort(eig)[::-1])
    D = np.zeros(A.shape)
    if D.shape[0] <= D.shape[1]:
        n = D.shape[0]
    else:
        n = D.shape[1]
    for i in range(n):
        D[i,i] = eig[i]
    return U,V,D

if __name__ == '__main__':

    # create matrix
    A = np.array([[3,4,3,4],[1,2,3,1],[4,2,1,5]])

    out = svd(A)
    print('u:', out[0])
    print('D:', out[2])
    print('V^T:', out[1].transpose())