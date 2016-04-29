//////////////////////////////////////////////////////////////////////
/// @file dense_matrix.h
/// @author Connor McBride
/// @brief Contains the DenseMatrix class implementation information.
///        All functions work as expected and listed in base_matrix.h.
///        Go there for documentation.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class DenseMatrix
/// @brief Is a template class that is derived from BaseMatrix. It contains
///        no speed optimizations and checks every index.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn DenseMatrix()
/// @brief Explicit definition of the default constructor.
/// @pre None.
/// @post A DenseMatrix object of type T is created of size 0x0. m_vectors points to nullptr.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn DenseMatrix(uint32_t m, uint32_t n)
/// @brief Overload of the constructor which creates an mxn matrix.
/// @pre None.
/// @post A DenseMatrix object of type T is created of size mxn. m_vectors points to
///        an array of m MathVectors.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual ~DenseMatrix()
/// @brief Overload of the destructor
/// @pre None.
/// @post All m_vectors of the calling object are cleared.
//////////////////////////////////////////////////////////////////////

#include "../interfaces/base_matrix.h"

#ifndef DENSE_MATRIX_H
#define DENSE_MATRIX_H


template <typename T>
class DenseMatrix : public BaseMatrix<T>
{
public:
  // Constructor information
  DenseMatrix();
  DenseMatrix(const shared_ptr<BaseMatrix<T>> rhs);
  DenseMatrix(uint32_t m, uint32_t n);
  DenseMatrix(DenseMatrix&& other);
  virtual ~DenseMatrix();

  // Getter
  virtual MatrixType type() const;

  // Index operators
  virtual MathVector<T>& operator [](uint32_t index);
  virtual MathVector<T>& operator [](uint32_t index) const;
  virtual T operator ()(uint32_t row_index, uint32_t column_index) const;
  virtual void operator ()(uint32_t row_index, uint32_t column_index, T element);

  // Matrix operations
  virtual shared_ptr<BaseMatrix<T>> transpose() const;

  // Operators
  DenseMatrix<T>& operator =(DenseMatrix<T> other);
  DenseMatrix<T> operator *(double c) const;
  DenseMatrix<T> operator +(const BaseMatrix<T>& rhs) const;
  DenseMatrix<T> operator -(const BaseMatrix<T>& rhs) const;
  DenseMatrix<T> operator *(const BaseMatrix<T>& rhs) const;

  // Replacements
  virtual shared_ptr<BaseMatrix<T>> clone() const;

};

#include "dense_matrix.hpp"

#endif //DENSE_MATRIX_H
