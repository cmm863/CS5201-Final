#pragma once

template<typename T>
MathVector<T> GaussianSolver::operator()(const DenseMatrix<T>& m, const MathVector<T>& s)
{
  MathVector<T> b = s;
  DenseMatrix<T> A(m.clone());
  uint32_t n = A.getNumRows();
  // To generate the upper triangular matrix
  long double sum = 0;

  for(uint32_t j = 0; j < n; j++)
    for(uint32_t i = 0; i < n; i++)
      if(i > j)
      {
        long double c = A(i, j) / A(j, j);
        for(uint32_t k = 0; k < n + 1; k++)
          if(k == n)
          {
            b[i] = b[i] - c*b[j];
          } 
          else
          {
            A(i, k, A(i, k) - c*A(j, k));
          }
      }
  b[n-1] = b[n-1] / A(n-1, n-1);
  for(int32_t i = n - 2; i >= 0; i--)
  {
    sum = 0;
    for(uint32_t j = i + 1; j < n; j++)
    {
      sum += A(i, j) * b[j];
    }
    b[i] = (b[i] - sum)/A(i, i);
  }

  return b;
}