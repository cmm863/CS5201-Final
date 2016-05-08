#pragma once

#include "../matrices/dense_matrix.h"
#include "gaussian_solver.h"
#include "../utilities/qr_decomp.h"

template <typename T, class SOLVER>
class DirichletSolver
{
private:
  int32_t n;

public:
  DirichletSolver(int32_t n) : n(n) {};
  MathVector<T> operator()(const DenseMatrix<T>& A, const MathVector<T>& B);

  template <long double fnXL (long double), long double fnXU (long double), long double fnYL (long double), long double fnYU (long double)>
  void makeMatrix(DenseMatrix<T>& A, MathVector<T>& B);
  uint32_t pointIndex(long double i, long double j);
};

#include "dirichlet_solver.hpp"