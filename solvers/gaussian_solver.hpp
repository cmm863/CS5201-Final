#pragma once

template<typename T>
MathVector<T> GaussianSolver::operator()(unique_ptr<BaseMatrix<T>> m, unique_ptr<BaseMatrix<T>> s)
{
  DenseMatrix<T> test = DenseMatrix<T>(m);
  cout << test << endl;

  return MathVector<T>();
}