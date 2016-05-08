#pragma once

#include "../matrices/dense_matrix.h"
#include "../utilities/qr_decomp.h"
#include "gaussian_solver.h"

class QRSolver
{
public:
  template <typename T>
  MathVector<T> operator()(const DenseMatrix<T>& m, const MathVector<T>& s);
};

#include "qr_solver.hpp"