//////////////////////////////////////////////////////////////////////
/// @file upper_tri_matrix.h
/// @author Connor McBride
/// @brief Contains the UpperTriMatrix class implementation information.
///        All functions work as expected and listed in base_matrix.h.
///        Go there for documentation. Documentation here will list differences
///        in implementation only if they exist.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class UpperTriMatrix
/// @brief Is a template class that is derived from BaseMatrix. It contains
///        speed optimizations in so much that it only checks values
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn UpperTriMatrix()
/// @brief Explicit definition of the default constructor.
/// @pre None.
/// @post A UpperTriMatrix object of type T is created of size 0x0. m_vectors points to nullptr.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn UpperTriMatrix(uint32_t n)
/// @brief Overload of the constructor which creates an nxn matrix.
/// @pre Size must be > 0.
/// @post A DiagMatrix object of type T is created that is nxn but only requires storage
///         space of at most nxn/2.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual ~UpperTriMatrix()
/// @brief Overload of the destructor
/// @pre None.
/// @post All m_vectors of the calling object are cleared.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual MathVector<T>& operator [](uint32_t index)
/// @optimization Returns at on average an n/2 MathVector reference.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual MathVector<T>& operator [](uint32_t index) const
/// @optimization Returns at on average an n/2 MathVector reference that cannot change the object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual T operator ()(uint32_t row_index, uint32_t column_index)
/// @optimization Returns 0 if row_index > column_index
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual unique_ptr<BaseMatrix<T>> transpose() const
/// @optimization Returns a LowerTriMatrix.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual unique_ptr<BaseMatrix<T>> operator +(const BaseMatrix<T>& rhs) const
/// @optimization Makes at most nxn/2 operations.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual unique_ptr<BaseMatrix<T>> operator -(const BaseMatrix<T>& rhs) const
/// @optimization Makes at most nxn/2 operations.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual unique_ptr<BaseMatrix<T>> operator *(double c) const
/// @optimization Makes at most nxn/2 operations.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual unique_ptr<BaseMatrix<T>> operator *(const BaseMatrix<T>& rhs) const
/// @optimization Makes on average n/2 calculations per index of returned matrix.
/// @return A DenseMatrix pointer is returned.
//////////////////////////////////////////////////////////////////////

#ifndef UPPER_TRI_MATRIX_H
#define UPPER_TRI_MATRIX_H

#include "../interfaces/base_matrix.h"

template <typename T>
class UpperTriMatrix: public BaseMatrix<T>
{
public:
  // Constructor information
  UpperTriMatrix();
  UpperTriMatrix(const unique_ptr<BaseMatrix<T>> rhs);
  UpperTriMatrix(uint32_t n);
  UpperTriMatrix(UpperTriMatrix&& other);
  virtual ~UpperTriMatrix();

  // Getters
  virtual MatrixType type() const;

  // Index operators
  virtual MathVector<T>& operator [](uint32_t index);
  virtual MathVector<T>& operator [](uint32_t index) const;
  virtual T operator ()(uint32_t row_index, uint32_t column_index) const;
  virtual void operator ()(uint32_t row_index, uint32_t column_index, T element);

  // Matrix operations
  virtual unique_ptr<BaseMatrix<T>> transpose() const;

  // Operators
  UpperTriMatrix<T>& operator =(UpperTriMatrix<T> other);
  UpperTriMatrix<T> operator *(double c) const;
  UpperTriMatrix<T> operator +(const UpperTriMatrix<T>& rhs) const;
  UpperTriMatrix<T> operator -(const UpperTriMatrix<T>& rhs) const;
  UpperTriMatrix<T> operator *(const UpperTriMatrix<T>& rhs) const;

  // Replacements
  virtual unique_ptr<BaseMatrix<T>> clone() const;
};

#include "upper_tri_matrix.hpp"

#endif //UPPER_TRI_MATRIX_H
