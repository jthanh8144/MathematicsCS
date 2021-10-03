#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

vector<vector<double>> matrix_i; 

// Sinh ma tran
void generate_matrix(vector<vector<double>>& matrix, int rows, int cols) {
	srand((unsigned int)time(nullptr)); matrix.resize(rows);
	for (int row = 0; row < matrix.size(); row++)
	{
		matrix[row].resize(cols);
		for (int col = 0; col < matrix[row].size(); col++)
			matrix[row][col] = rand() % 10;
	}
}

// In ma tran
void print_matrix(vector<vector<double>>	matrix) {
	for (int row = 0; row < matrix.size(); row++) {
		for (int col = 0; col < matrix[row].size(); col++)
			cout << setprecision(8) << fixed << matrix[row][col] << " ";

		cout << "\n";
	}
	cout << "\n";
}

// 
void jordan_gaussian_transform(vector<vector<double>> matrix, vector<double>& eigenvector) {
	const double eps = 10e-6; bool eigenv_found = false;
	for (int s = 0; s < matrix.size() - 1 && !eigenv_found; s++) {
		int col = s; double alpha = matrix[s][s];
		while (col < matrix[s].size() && alpha != 0 && alpha != 1)
			matrix[s][col++] /= alpha;

		for (int col = s; col < matrix[s].size() && !alpha; col++)
			swap(matrix[s][col], matrix[s + 1][col]);

		for (int row = 0; row < matrix.size(); row++) {
			double gamma = matrix[row][s];
			for (int col = s; col < matrix[row].size() && row != s; col++)
				matrix[row][col] = matrix[row][col] - matrix[s][col] * gamma;
		}
	}

	int row = 0;
	while (row < matrix.size())
		eigenvector.push_back(-matrix[row++][matrix.size() - 1]);

	eigenvector[eigenvector.size() - 1] = 1;
}


void get_hermitian_matrix(vector<double> eigenvector, vector<vector<double>>& h_matrix) {
	h_matrix.resize(eigenvector.size());
	for (int row = 0; row < eigenvector.size(); row++)
		h_matrix[row].resize(eigenvector.size());

	h_matrix[0][0] = 1.0 / eigenvector[0];
	for (int row = 1; row < eigenvector.size(); row++)
		h_matrix[row][0] = -eigenvector[row] / eigenvector[0];

	for (int row = 1; row < eigenvector.size(); row++)
		h_matrix[row][row] = 1;
    cout << endl << "Hermitian" << endl;
    print_matrix(h_matrix);
    cout << endl;
}

// Ma tran 3 = Mt1 x Mt2
void matrix_by_matrix(vector<vector<double>> matrix1,
	vector<vector<double>>& matrix2, vector<vector<double>>& matrix3)
{
	matrix3.resize(matrix1.size());
	for (int row = 0; row < matrix1.size(); row++)
	{
		matrix3[row].resize(matrix1[row].size());
		for (int col = 0; col < matrix1[row].size(); col++)
		{
			matrix3[row][col] = 0.00;
			for (int k = 0; k < matrix1[row].size(); k++)
				matrix3[row][col] += matrix1[row][k] * matrix2[k][col];
		}
	}
}

// Lay ma tran nghich dao cua hermitian
void get_hermitian_matrix_inverse(vector<vector<double>> hermitian, vector<vector<double>>& ih_matrix) {
	int n = hermitian.size();
    ih_matrix.resize(n);
	for (int row = 0; row < n; row++)
		ih_matrix[row].resize(n);

	// ih_matrix[0][0] = eigenvector[0];
	// for (int row = 1; row < eigenvector.size(); row++)
	// 	ih_matrix[row][0] = -eigenvector[row];

	// for (int row = 1; row < eigenvector.size(); row++)
	// 	ih_matrix[row][row] = 1;
    
    MatrixXd t(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t(i, j) = hermitian[i][j];
        }
    }
    t = t.inverse();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ih_matrix[i][j] = t(i, j);
        }
    }
    cout << endl << "Nghich dao hermitian" << endl;
    print_matrix(ih_matrix);
    cout << endl;
}


void get_reduced_matrix(vector<vector<double>> matrix,
	vector<vector<double>>& r_matrix, int new_size)
{
    cout << endl << "new_size = " << new_size << endl << "Matrix: " << endl;
    print_matrix(matrix);
    
	if (new_size > 1)
	{
		r_matrix.resize(new_size);
		int index_d = matrix.size() - new_size;
		int row = index_d, row_n = 0;
		while (row < matrix.size())
		{
			r_matrix[row_n].resize(new_size);
			int col = index_d, col_n = 0;
			while (col < matrix.size())
				r_matrix[row_n][col_n++] = matrix[row][col++];

			row++; row_n++;
		}
	}

	else if (new_size == 1)
	{
		r_matrix.resize(new_size);
		r_matrix[0].resize(new_size);
		r_matrix[0][0] = matrix[1][1];
	}
    cout << "Reduced matrix: " << endl;
    print_matrix(r_matrix);
}


void compute_evd(vector<vector<double>> matrix,
	vector<double>& eigenvalues, vector<vector<double>>& eigenvectors, int eig_count)
{
	int m_size = matrix.size();
	vector<double> vec; vec.resize(m_size);
	generate(vec.begin(), vec.end(), []() {
		return rand() % 100;
	});

	if (eigenvalues.size() == 0 && eigenvectors.size() == 0)
	{
		eigenvalues.resize(m_size);
		eigenvectors.resize(eigenvalues.size());
		matrix_i = matrix;
	}

	vector<vector<double>> m; m.resize(m_size);
	for (int row = 0; row < m_size; row++)
		m[row].resize(100);

	double lambda_old = 0;

	int index = 0; bool is_eval = false;
	while (is_eval == false)
	{
		for (int row = 0; row < m_size && (index % 100) == 0; row++)
			m[row].resize(m[row].size() + 100);

		for (int row = 0; row < m_size; row++)
		{
			m[row][index] = 0;
			for (int col = 0; col < m_size; col++)
				m[row][index] += matrix[row][col] * vec[col];
		}

		for (int col = 0; col < m_size; col++)
			vec[col] = m[col][index];

		if (index > 0)
		{
			double lambda = ((index - 1) > 0) ? \
				(m[0][index] / m[0][index - 1]) : m[0][index];
			is_eval = (fabs(lambda - lambda_old) < /*10e-15*/10e-10) ? true : false;

			eigenvalues[eig_count] = lambda; lambda_old = lambda;
		}

		index++;
	}

	vector<vector<double>> matrix_new;

	if (m_size > 1)
	{
		vector<vector<double>> matrix_target;
		matrix_target.resize(m_size);

		for (int row = 0; row < m_size; row++)
		{
			matrix_target[row].resize(m_size);
			for (int col = 0; col < m_size; col++)
				matrix_target[row][col] = (row == col) ? \
				(matrix[row][col] - eigenvalues[eig_count]) : matrix[row][col];
		}

		vector<double> eigenvector;
		jordan_gaussian_transform(matrix_target, eigenvector);

        cout << endl << "matrix_target 1:" << endl;
        print_matrix(matrix_target);
        cout << endl;

        cout << endl << "Eig" << endl;
        for (int i = 0; i < eigenvector.size(); i++) {
            cout << eigenvector[i] << " ";
        }
        cout << endl;
        

		vector<vector<double>> hermitian_matrix;
		get_hermitian_matrix(eigenvector, hermitian_matrix);

		vector<vector<double>> ha_matrix_product;
		matrix_by_matrix(hermitian_matrix, matrix, ha_matrix_product);

		vector<vector<double>> inverse_hermitian_matrix;
		get_hermitian_matrix_inverse(hermitian_matrix, inverse_hermitian_matrix);

		vector<vector<double>> iha_matrix_product;
		matrix_by_matrix(ha_matrix_product, inverse_hermitian_matrix, iha_matrix_product);

		get_reduced_matrix(iha_matrix_product, matrix_new, m_size - 1);
	}

	if (m_size <= 1)
	{
		for (int index = 0; index < eigenvalues.size(); index++)
		{
			double lambda = eigenvalues[index];
			vector<vector<double>> matrix_target;
			matrix_target.resize(matrix_i.size());

			for (int row = 0; row < matrix_i.size(); row++)
			{
				matrix_target[row].resize(matrix_i.size());
				for (int col = 0; col < matrix_i.size(); col++)
					matrix_target[row][col] = (row == col) ? \
					(matrix_i[row][col] - lambda) : matrix_i[row][col];
			}

			eigenvectors.resize(matrix_i.size());
			jordan_gaussian_transform(matrix_target, eigenvectors[index]);

            cout << endl << "matrix_target 2:" << endl;
            print_matrix(matrix_target);
            cout << endl;

            cout << endl << "Eigvectors" << endl;
            for (int i = 0; i < eigenvectors[index].size(); i++) {
                cout << eigenvectors[index][i] << " ";
            }
            cout << endl;

			double eigsum_sq = 0;
			for (int v = 0; v < eigenvectors[index].size(); v++)
				eigsum_sq += pow(eigenvectors[index][v], 2.0);

			for (int v = 0; v < eigenvectors[index].size(); v++)
				eigenvectors[index][v] /= sqrt(eigsum_sq);

			eigenvalues[index] = sqrt(eigenvalues[index]);
		}

		return;
	}

	compute_evd(matrix_new, eigenvalues, eigenvectors, eig_count + 1);

	return;
}

// Chuyển vị
void matrix_transpose(vector<vector<double>> matrix1,
	vector<vector<double>>& matrix2)
{
	matrix2.resize(matrix1.size());
	for (int row = 0; row < matrix1.size(); row++)
	{
		matrix2[row].resize(matrix1[row].size());
		for (int col = 0; col < matrix1[row].size(); col++)
			matrix2[row][col] = matrix1[col][row];
	}
}

void get_inverse_diagonal_matrix(vector<vector<double>> matrix, vector<vector<double>>& inv_matrix) {
    cout << "diag matrix:" << endl;
    print_matrix(matrix);

	inv_matrix.resize(matrix.size());
	for (int index = 0; index < matrix.size(); index++) {
		inv_matrix[index].resize(matrix[index].size());
		inv_matrix[index][index] = 1.0 / matrix[index][index];
	}

    cout << "inverse diag:" << endl;
    print_matrix(inv_matrix);

}

void svd(vector<vector<double>> matrix, vector<vector<double>>& s, vector<vector<double>>& u, vector<vector<double>>& v) {
	vector<vector<double>> matrix_t;
	matrix_transpose(matrix, matrix_t);

	vector<vector<double>> matrix_product1;
	matrix_by_matrix(matrix, matrix_t, matrix_product1);

	vector<vector<double>> matrix_product2;
	matrix_by_matrix(matrix_t, matrix, matrix_product2);

	vector<vector<double>> u_1;
	vector<vector<double>> v_1;

	vector<double> eigenvalues;
	compute_evd(matrix_product2, eigenvalues, v_1, 0);

	matrix_transpose(v_1, v);

	s.resize(matrix.size());
	for (int index = 0; index < eigenvalues.size(); index++)
	{
		s[index].resize(eigenvalues.size());
		s[index][index] = eigenvalues[index];
	}

	vector<vector<double>> s_inverse;
	get_inverse_diagonal_matrix(s, s_inverse);

	vector<vector<double>> av_matrix;
	matrix_by_matrix(matrix, v, av_matrix);
	matrix_by_matrix(av_matrix, s_inverse, u);
}

void Nhap(vector<vector<double>>& matrix, int rows, int cols) {
    matrix.resize(rows);
    for (int row = 0; row < matrix.size(); row++)
	{
		matrix[row].resize(cols);
		for (int col = 0; col < matrix[row].size(); col++)
			cin >> matrix[row][col];
	}
}

int main(int argc, char* argv[])
{
	int matrix_size = 0;
	vector<vector<double>> u, v;
	vector<vector<double>> matrix, s;
	cout << "Singular Value Decomposition (SVD):\n\n";
	
	cout << "Enter size of matrix N = (50x50 max): "; cin >> matrix_size;

	if (matrix_size <= 50)
	{
		Nhap(matrix, matrix_size, matrix_size);

		cout << "\nA = \n"; print_matrix(matrix);

		svd(matrix, s, u, v);

		cout << "\nS = \n"; print_matrix(s);
		cout << "\nU = \n"; print_matrix(u);
		cout << "\nV = \n"; print_matrix(v);
	}

	else cout << "Wrong matrix size... (matrix decomposition recommended)";

	return 0;
}
