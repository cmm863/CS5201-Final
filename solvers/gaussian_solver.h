#pragma once

#include "../matrices/dense_matrix.h"

class GaussianSolver
{
public:
	template <typename T>
  MathVector<T> operator()(const DenseMatrix<T>& m, const MathVector<T>& s);
};

#include "gaussian_solver.hpp"
