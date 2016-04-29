//////////////////////////////////////////////////////////////////////
/// @file qr_decomp.hpp
/// @author Connor McBride
/// @brief Contains the declaration information for the QRDecomp class
//////////////////////////////////////////////////////////////////////

#ifndef QR_DECOMP_HPP
#define QR_DECOMP_HPP

template <typename T>
MathVector<T> QRDecomp::operator()(const shared_ptr<BaseMatrix<T>> A, int iterations) const
{
  shared_ptr<BaseMatrix<T>> Ak, Q, R;

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
      Ak = (*R) * (*Q);

    // Load current eigenvalues
    for(unsigned long i = 0; i < Ak->getNumRows(); i++)
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
void QRDecomp::operator ()(const shared_ptr<BaseMatrix<T>>& A, shared_ptr<BaseMatrix<T>>& Q, shared_ptr<BaseMatrix<T>>& R) const
{
  shared_ptr<BaseMatrix<T>> Qt, X;
  double top, bottom;
  MathVector<T> temp;

  Qt = A->clone()->transpose();
  X = Qt->clone();

  for (unsigned long i = 0; i < A->getNumColumns(); i++)
  {
    // Subtract projections
    for (long j = i - 1; j >= 0; j--)
    {
      temp = (*Qt)[j];
      top = ((*X)[i] * temp);
      bottom = (temp * temp);
      (*Qt)[i] -= (top / bottom) * (*Qt)[j];
    }

    // Make Q columns orthonormal
    (*Qt)[i] = (1.0 / (*Qt)[i].magnitude()) * (*Qt)[i];
  }

  // Change values of passed in Q and R
  Q = Qt->transpose();
  R = (*Qt) * (*A);
}

#endif //QR_DECOMP_HPP
