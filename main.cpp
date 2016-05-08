// C++ includes
#include <iostream>
#include <fstream>
#include <iomanip>

// Local includes
#include "matrices/dense_matrix.h"
#include "matrices/upper_tri_matrix.h"
#include "utilities/constants.hpp"
#include "solvers/gaussian_solver.h"
#include "solvers/dirichlet_solver.h"
#include "solvers/qr_solver.h"

using namespace std;

template <typename MT, typename T>
void run_generic_test(MatrixType mt);

string get_input_file(MatrixType mt);


int main()
{
  run_generic_test<DenseMatrix<long double>, long double>(DENSE);

  return 0;
}

template <typename MT, typename T>
void run_generic_test(MatrixType mt)
{
  ifstream file_in;
  int matrix_size;
  T temp;

  file_in.open(get_input_file(mt));
  if(!file_in.is_open())
    return;
  // Take in size
  file_in >> matrix_size;

  // Create matrix
  MT matrix_a(matrix_size);

  for(uint32_t i = 0; i < matrix_a.getNumRows(); i++)
    for(uint32_t j = 0; j < matrix_a.getNumColumns(); j++)
    {
      file_in >> temp;
      matrix_a(i, j, temp);
    }
  file_in.close();

  MT matrix_b(matrix_a.clone());
  MathVector<T> b;

  cout << "=== Matrix A ===" << endl;
  cout << matrix_a << endl;
  cout << "=== Matrix B ===" << endl;
  cout << matrix_b << endl;
  cout << "=== Sum ===" << endl;
  cout << matrix_a + matrix_b << endl;
  cout << "=== Difference ===" << endl;
  cout << matrix_a - matrix_b << endl;
  cout << "=== Product ===" << endl;
  cout << matrix_a * matrix_b << endl;

  cout << "=== QRSolver ===" << endl;
  DirichletSolver<T, QRSolver> qrds(4);
  qrds.template makeMatrix<constants::xLower, constants::xUpper, constants::yLower, constants::yUpper>(matrix_a, b);
  cout << qrds(matrix_a, b) << endl;

  cout << "=== GaussianSolver ===";
  DirichletSolver<T, GaussianSolver> gsds(4);
  gsds.template makeMatrix<constants::xLower, constants::xUpper, constants::yLower, constants::yUpper>(matrix_a, b);
  cout << gsds(matrix_a, b) << endl;
  //QRSolver qrs;
  
  //cout << solution << endl;
  //cout << qrs(matrix_a, solution) << endl;

  
  
  return;
}

string get_input_file(MatrixType mt)
{
  switch(mt)
  {
    case DENSE:
      return constants::DENSE_INPUT_FILE;
    case UPPER_TRIANGULAR:
      return constants::UPPER_TRIANGULAR_INPUT_FILE;
    default:
      return "No matching input file for matrix type.";
  }
}
