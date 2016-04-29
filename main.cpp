// C++ includes
#include <iostream>
#include <fstream>
#include <iomanip>

// Local includes
#include "matrices/dense_matrix.h"
#include "matrices/upper_tri_matrix.h"
#include "utilities/constants.hpp"

using namespace std;

void run_generic_test(MatrixType mt);
string get_input_file(MatrixType mt);

int main()
{
  run_generic_test(DENSE);

  return 0;
}

void run_generic_test(MatrixType mt)
{
  ifstream file_in;
  int matrix_size;
  double temp;
  DenseMatrix<double> matrix_a, matrix_b;

  file_in.open(get_input_file(mt));

  if(file_in.is_open())
  {
    // Take in size
    file_in >> matrix_size;

    // Create matrix
    matrix_a = DenseMatrix<double>(matrix_size, matrix_size);
    cout << "After made matrix_a" << endl;
    cout << matrix_a << endl;

    for(uint32_t i = 0; i < matrix_a.getNumRows(); i++)
      for(uint32_t j = 0; j < matrix_a.getNumColumns(); j++)
      {
        file_in >> temp;
        matrix_a(i, j, temp);
        cout << matrix_a(i, j) << endl;
      }
  }
  else
  {
    return;
  }
  file_in.close();

  matrix_b = DenseMatrix<double>(matrix_a.clone());

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
