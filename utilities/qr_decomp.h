//////////////////////////////////////////////////////////////////////
/// @file qr_decomp.h
/// @author Connor McBride
/// @brief Contains the declaration information for the QRDecomp class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class QRDecomp
/// @brief Is a function class to implement a QR decomposition that
///    derives eigenvalues
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn void operator ()(const shared_ptr<BaseMatrix<T>> A, int iterations) const
/// @brief Overloads the () operator to act as a function class.
/// @pre Matrix A passed should be representable as a square dense matrix
/// @post Prints A, Q, R, and the eigenvalues derived after all iterations
/// @param A is a shared pointer of type BaseMatrix and is the matrix to be decomposed
/// @param iterations is an int representing the amount of times for A to be decoposed and recomposed
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn void operator ()(const shared_ptr<BaseMatrix<T>>& A, shared_ptr<BaseMatrix<T>>& Q, shared_ptr<BaseMatrix<T>>& R) const
/// @brief Overloads the () operator to act as a function class.
/// @pre Matrix A passed should be representable as a square dense matrix
/// @post Q and R are returned as the Q and R factored from A
/// @param A is a shared pointer of type BaseMatrix and is the matrix to be decomposed
/// @param Q the Q factor of A
/// @param R the R factor of A
//////////////////////////////////////////////////////////////////////

#ifndef QR_DECOMP_H
#define QR_DECOMP_H

#include "../matrices/dense_matrix.h"

class QRDecomp
{
public:
  template <typename T>
  MathVector<T> operator ()(const shared_ptr<BaseMatrix<T>> A, int iterations) const;

  template <typename T>
  void operator ()(const shared_ptr<BaseMatrix<T>>& A, shared_ptr<BaseMatrix<T>>& Q, shared_ptr<BaseMatrix<T>>& R) const;

  string termination_reason() { return "Eigenvalues did not differ in two consecutive runs by a margin of 7 decimal points."; }
};

#include "qr_decomp.hpp"

#endif //QR_DECOMP_H
