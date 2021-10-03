#include <iostream>
#include <algorithm>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

template <class T>
inline void push_back(Matrix<T, Dynamic, 1> &v, const T d) {
    Matrix<T, Dynamic, 1> tmp = v;
    v.resize(tmp.size() + 1);
    v.head(tmp.size()) = tmp;
    v[v.size() - 1] = d;
}

MatrixXd Nhap() {
    int m, n;
    cout << "Nhap m = "; cin >> m;
    cout << "Nhap n = "; cin >> n;
    MatrixXd A(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A(" << i << ", " << j << ") = "; cin >> A(i, j);
        }
    }
    return A;
}

void jordan_gaussian_transform(MatrixXd matrix, VectorXd& eigenvector) {
	const double eps = 10e-6; bool eigenv_found = false;
	for (int s = 0; s < matrix.rows() - 1 && !eigenv_found; s++) {
		int col = s; double alpha = matrix(s, s);
		while (col < matrix.cols() && alpha != 0 && alpha != 1)
			matrix(s, col++) /= alpha;

		for (int col = s; col < matrix.cols() && !alpha; col++)
			swap(matrix(s, col), matrix(s + 1, col));

		for (int row = 0; row < matrix.rows(); row++) {
			double gamma = matrix(row, s);
			for (int col = s; col < matrix.cols() && row != s; col++)
				matrix(row, col) = matrix(row, col) - matrix(s, col) * gamma;
		}
	}

	int row = 0;
	while (row < matrix.rows())
        push_back<double>(eigenvector, -matrix(row++, matrix.rows() - 1));

	eigenvector[eigenvector.size() - 1] = 1;
}


MatrixXd hermitian_matrix(VectorXd eigenvector) {
    int n = eigenvector.size();
    MatrixXd h_matrix(n, n);
	h_matrix(0, 0) = 1.0 / eigenvector[0];
	for (int row = 1; row < n; row++)
		h_matrix(row, 0) = -eigenvector[row] / eigenvector[0];

	for (int row = 1; row < n; row++)
		h_matrix(row, row) = 1;

    return h_matrix;
}

// MatrixXd hermitian_matrix_inverse(VectorXd eigenvector) {
//     int n = eigenvector.size();
//     MatrixXd ih_matrix(n, n);
// 	ih_matrix(0, 0) = eigenvector[0];
// 	for (int row = 1; row < n; row++)
// 		ih_matrix(row, 0) = -eigenvector[row];
// 	for (int row = 1; row < n; row++)
// 		ih_matrix(row, row) = 1;
//     return ih_matrix;
// }

MatrixXd reduced_matrix(MatrixXd matrix, int new_size) {
    MatrixXd r_matrix(new_size, new_size);
    int n = matrix.rows();
    int delta = n - new_size;
	for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            r_matrix(i, j) = matrix(i + delta, j + delta);
        }
    }
    return r_matrix;
}

MatrixXd matrix_i;

void compute_evd(MatrixXd matrix, VectorXd& eigenvalues, MatrixXd& eigenvectors, int eig_count) {
	int m_size = matrix.rows();
	VectorXd vec(m_size);
	std::generate(vec.begin(), vec.end(), []() {
		return rand() % 100;
	});

	if (eigenvalues.size() == 0 && eigenvectors.rows() == 0) {
		eigenvalues.resize(m_size);
		eigenvectors.resize(eigenvalues.rows(), eigenvalues.rows());
		matrix_i = matrix;
	}

	MatrixXd m(m_size, m_size);

	double lambda_old = 0;

	int index = 0; bool is_eval = false;
	while (is_eval == false) {
		for (int row = 0; row < m_size && (index % 100) == 0; row++)
			m.resize(m.cols() + 100, m.cols() + 100);

		for (int row = 0; row < m_size; row++) {
			m(row, index) = 0;
			for (int col = 0; col < m_size; col++)
				m(row, index) += matrix(row, col) * vec[col];
		}

		for (int col = 0; col < m_size; col++)
			vec[col] = m(col, index);

		if (index > 0)
		{
			double lambda = ((index - 1) > 0) ? (m(0, index) / m(0, index - 1)) : m(0, index);
			is_eval = (fabs(lambda - lambda_old) < /*10e-15*/10e-10) ? true : false;

			eigenvalues[eig_count] = lambda; lambda_old = lambda;
		}

		index++;
	}

	MatrixXd matrix_new;

	if (m_size > 1) {
		MatrixXd matrix_target(m_size, m_size);

		for (int row = 0; row < m_size; row++) {
			for (int col = 0; col < m_size; col++)
				matrix_target(row, col) = (row == col) ? (matrix(row, col) - eigenvalues[eig_count]) : matrix(row, col);
		}

		VectorXd eigenvector;
		jordan_gaussian_transform(matrix_target, eigenvector);

        cout << endl << "matrix_target 1:" << endl;
        cout << matrix_target;
        cout << endl;

        cout << endl << "Eig" << endl;
        for (int i = 0; i < eigenvector.size(); i++) {
            cout << eigenvector[i] << " ";
        }
        cout << endl;
        

		MatrixXd hermitian_matrix = hermitian_matrix(eigenvector);

		MatrixXd ha_matrix_product = hermitian_matrix * matrix;

		MatrixXd inverse_hermitian_matrix = hermitian_matrix.inverse();

		MatrixXd iha_matrix_product = ha_matrix_product * inverse_hermitian_matrix;

		matrix_new = reduced_matrix(iha_matrix_product, m_size - 1);
	}

	if (m_size <= 1) {
		for (int index = 0; index < eigenvalues.size(); index++) {
			double lambda = eigenvalues[index];
			MatrixXd matrix_target(matrix_i.rows(), matrix_i.rows());

			for (int row = 0; row < matrix_i.rows(); row++) {
				for (int col = 0; col < matrix_i.rows(); col++)
					matrix_target(row, col) = (row == col) ? (matrix_i(row, col) - lambda) : matrix_i(row, col);
			}

			eigenvectors.resize(matrix_i.rows(), matrix_i.rows());

            // 
            VectorXd temp;
			jordan_gaussian_transform(matrix_target, temp);
            for (int i = 0; i < temp.size(); i++) {
                eigenvectors(index, i) = temp[i];
            }

            cout << endl << "matrix_target 2:" << endl;
            cout << matrix_target;
            cout << endl;

            cout << endl << "Eigvectors" << endl;
            for (int i = 0; i < eigenvectors.cols(); i++) {
                cout << eigenvectors(index, i)<< " ";
            }
            cout << endl;

			double eigsum_sq = 0;
			for (int v = 0; v < eigenvectors.cols(); v++)
				eigsum_sq += pow(eigenvectors(index, v), 2.0);

			for (int v = 0; v < eigenvectors.cols(); v++)
				eigenvectors(index, v) /= sqrt(eigsum_sq);

			eigenvalues[index] = sqrt(eigenvalues[index]);
		}

		return;
	}

	compute_evd(matrix_new, eigenvalues, eigenvectors, eig_count + 1);

	return;
}

// Chuyển vị a.transpose()
// Ma tran nghich dao a.inverse()

void svd(MatrixXd matrix, MatrixXd& s, MatrixXd& u, MatrixXd& v) {
	MatrixXd matrix_t = matrix.transpose();

	MatrixXd matrix_product1 = matrix * matrix_t;

	MatrixXd matrix_product2 = matrix_t * matrix;

	MatrixXd u_1;
	MatrixXd v_1;

	VectorXd eigenvalues;
	compute_evd(matrix_product2, eigenvalues, v_1, 0);

    v = v_1.transpose();

	s.resize(matrix.size(), matrix.size());
	for (int index = 0; index < eigenvalues.size(); index++) {
		s(index, index) = eigenvalues[index];
	}

	MatrixXd s_inverse = s.inverse();

	MatrixXd av_matrix = matrix * v;
    u = av_matrix * s_inverse;
}


int main() {
	MatrixXd u, v;
	MatrixXd s;
	cout << "Singular Value Decomposition (SVD):\n\n";

    MatrixXd matrix = Nhap();
    cout << matrix << endl;
	svd(matrix, s, u, v);
    cout << "\nS = \n";
    cout << s;
    cout << "\nU = \n";
    cout << u;
    cout << "\nV = \n";
    cout << v;
    return 0;
}