//////////////////////////////////////////////////////////////////////
/// @file qr_decomp.hpp
/// @author Connor McBride
/// @brief Contains the declaration information for the QRDecomp class
//////////////////////////////////////////////////////////////////////

#ifndef QR_DECOMP_HPP
#define QR_DECOMP_HPP

template <typename T>
MathVector<T> QRDecomp::operator()(const unique_ptr<BaseMatrix<T>> A, int iterations) const
{
  unique_ptr<BaseMatrix<T>> Ak, Q, R;

  // Eigenvalues to check for termination
  MathVector<T> pastEigen(A->getNumRows());
  MathVector<T> currentEigen(A->getNumRows());

  // For each iteration
  for(int it = 0; it < iterations; it++)
  {
    // Reset current eigenvalues
    currentEigen.setToZeroVector();

    // If first round, Ak = A. else it is equal to previously factored R * Q
    if(it == 0)
      Ak = A->clone();
    else
      Ak = ((*R) * (*Q)).clone();

    // Load current eigenvalues
    for(uint32_t i = 0; i < Ak->getNumRows(); i++)
      currentEigen.push((*Ak)(i, i));

    // If it's past the first iteration check to end
    if(it > 0)
    {
      if (currentEigen == pastEigen)
      {
        cout << "=== Count iterations: " << it << " ===" << endl;
        break;
      }
    }

    // Factor Ak into Q and R
    (*this)(Ak, Q, R);

    // Set past eigenvalues
    pastEigen = currentEigen;
  }

  // Output things
  cout << Ak;

  return currentEigen;
}

template <typename T>
void QRDecomp::operator ()(const BaseMatrix<T>& A, DenseMatrix<T>& Q, UpperTriMatrix<T>& R) const
{
  DenseMatrix<T> Qt, X;
  double top, bottom;
  MathVector<T> temp;

  Qt = DenseMatrix<T>(A.clone()->transpose());
  X = DenseMatrix<T>(Qt.clone());
  for (uint32_t i = 0; i < A.getNumColumns(); i++)
  {
    // Subtract projections
    for (int32_t j = i - 1; j >= 0; j--)
    {
      temp = Qt[j];
      top = X[i] * temp;
      bottom = (temp * temp);
      Qt[i] -= (top / bottom) * Qt[j];
    }

    // Make Q columns orthonormal
    Qt[i] = (1.0 / Qt[i].magnitude()) * Qt[i];
  }

  // Change values of passed in Q and R
  Q = DenseMatrix<T>(Qt.transpose());
  R = UpperTriMatrix<T>((Qt * A).clone());
}

#endif //QR_DECOMP_HPP
