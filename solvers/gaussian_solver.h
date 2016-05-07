#pragma once

#include "../matrices/dense_matrix.h"

class GaussianSolver
{
public:
	template <typename T>
  MathVector<T> operator()(unique_ptr<BaseMatrix<T>> m, unique_ptr<BaseMatrix<T>> s);
};

#include "gaussian_solver.hpp"
