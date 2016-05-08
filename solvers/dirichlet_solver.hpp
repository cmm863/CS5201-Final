#pragma once

template <typename T, class SOLVER>
MathVector<T> DirichletSolver<T, SOLVER>::operator()(const DenseMatrix<T>& A, const MathVector<T>& B)
{
  SOLVER s;

  return s(A, B);
}

template <typename T, class SOLVER>
template <long double fnXL (long double), long double fnXU (long double), long double fnYL (long double), long double fnYU (long double)>
void DirichletSolver<T, SOLVER>::makeMatrix(DenseMatrix<T>& A, MathVector<T>& B)
{
  uint32_t limit = (n - 1) * (n - 1);
  A = DenseMatrix<T>(limit);
  B = MathVector<T>(limit);
  for(uint32_t i = 0; i < B.capacity(); i++)
    B.push(0);
  MathVector<T> C = B;
  long double diff = 1.0 / n;
  for(int32_t xIndex = 1; xIndex < n; xIndex++)
  {
    for(int32_t yIndex = 1; yIndex < n; yIndex++)
    {
      long double i = diff * xIndex;
      long double j = diff * yIndex;

      // Set 1
      uint32_t centerIndex = pointIndex(i, j);
      A(centerIndex, centerIndex, 1);
      C[centerIndex] = (1 - pow(i, 2)) * (1 + pow(j, 2));

      // For uY
      long double uY = j + diff;
      if(yIndex + 1 == n)
        B[centerIndex] += .25 * fnYU(i);
      else
        A(centerIndex, pointIndex(i, uY), -0.25);

      // For lY
      long double lY = j - diff;
      if(yIndex == 1)
        B[centerIndex] += .25 * fnYL(i);
      else
        A(centerIndex, pointIndex(i, lY), -0.25);

      // For uX
      long double uX = i + diff;
      if(xIndex + 1 == n)
        B[centerIndex] += .25 * fnXU(j);
      else
        A(centerIndex, pointIndex(uX, j), -0.25);

      // For lX
      long double lX = i - diff;
      if(xIndex == 1)
        B[centerIndex] += .25 * fnXL(j);
      else
        A(centerIndex, pointIndex(lX, j), -0.25);

    }
  }
  cout << B << endl;
  cout << C << endl << endl;
  return;
}

template <typename T, class SOLVER>
uint32_t DirichletSolver<T, SOLVER>::pointIndex(long double i, long double j)
{
  long double diff = 1.0 / n;
  return (n - 1) * ((j/diff) - 1) + ((i/diff) - 1);
}