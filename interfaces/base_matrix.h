//////////////////////////////////////////////////////////////////////
/// @file base_matrix.h
/// @author Connor McBride
/// @brief Contains the declaration information for the BaseMatrix class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class BaseMatrix
/// @brief Is a template class that is an abstract base class for a matrix.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual ~BaseMatrix()
/// @brief Virtual destructor
/// @pre None.
/// @post None.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn unsigned long getNumRows() const
/// @brief Get function for m_num_rows.
/// @pre None.
/// @post Returns number of rows for the matrix.
/// @return Returns m_num_rows of the derived object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn unsigned long getNumColumns() const
/// @brief Get function for m_num_columns.
/// @pre None.
/// @post Returns number of columns for the matrix.
/// @return Returns m_num_columns of the derived object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn MatrixType type() const
/// @brief Virtual function to get enum value that represents type of derived class.
/// @pre None.
/// @post Returns enum value of the derived object's matrix type.
/// @return Returns enum value of the derived object's matrix type.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual MathVector<T>& operator [](unsigned long index)
/// @brief Virtual function to return a MathVector reference of the row.
/// @pre Index needs to be less than the number of rows.
/// @post Returns a reference to the MathVector at index.
/// @param1 Index of the term to be returned.
/// @return Returns a reference to the MathVector at index.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual MathVector<T>& operator [](unsigned long index) const
/// @brief Virtual function to return a MathVector reference of the row that cannot change the object.
/// @pre Index needs to be less than the number of rows.
/// @post Returns a reference to the MathVector at index that cannot change the object.
/// @param1 Index of the term to be returned.
/// @return Returns a reference to the MathVector at index that cannot change the object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual T operator ()(unsigned long row_index, unsigned long column_index) const
/// @brief Virtual function to implement a faux double [][] operator
///      that cannot change the object.
/// @pre row_index needs to be less than number of rows.
///      column_index needs to be less than the number of columns.
/// @post Returns a reference to the element that is at [i][j] of the matrix that cannot change the object.
/// @param1 Row index of the element to be returned.
/// @param2 Column index of the element to be returned.
/// @return Returns a reference to the element at [i][j] of the matrix that cannot change the object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual void operator ()(unsigned long row_index, unsigned long column_index, T element)
/// @brief Virtual function to implement a faux double [][] operator that sets matrix[i][j] = to element.
/// @pre row_index needs to be less than number of rows.
///      column_index needs to be less than the number of columns.
/// @post Matrix at [i][j] will be equal to element.
/// @param1 Row index of the element to be returned.
/// @param2 Column index of the element to be returned.
/// @param3 element to set in the matrix.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual shared_ptr<BaseMatrix<T>> transpose() const
/// @brief Virtual function to return a pointer to a new object that is the transpose of
///      the called object.
/// @pre None.
/// @post Returns the pointer to a new object that is the transpose of the called object.
/// @return Returns the pointer to a new object that is the transpose of the called object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual shared_ptr<BaseMatrix<T>> operator *(double c) const
/// @brief Virtual function to implement an overload on the * scalar operator.
/// @pre T needs to have a * operator defined.
/// @post Returns a pointer to a new object that is the old object * a constant c.
/// @param1 The constant that each entry of the matrix is to be multiplied by.
/// @return Returns a pointer to a new object that is the old object * a constant c.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual shared_ptr<BaseMatrix<T>> operator +(const BaseMatrix<T>& rhs) const
/// @brief Virtual function to implement an overload on the + operator.
/// @pre T needs to have a + operator defined.
///      The sizes of the matrices (rows and columns) must be equal.
/// @post Returns a pointer to a new object that is the old object + rhs.
/// @param1 The matrix that the called object is to be added to.
/// @return Returns a pointer to a new object that is the old object + rhs.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual shared_ptr<BaseMatrix<T>> operator -(const BaseMatrix<T>& rhs) const
/// @brief Virtual function to implement an overload on the - operator.
/// @pre T needs to have a - operator defined.
///      The sizes of the matrices (rows and columns) must be equal.
/// @post Returns a pointer to a new object that is the old object - rhs.
/// @param1 The matrix that the called object is to be subtracted from.
/// @return Returns a pointer to a new object that is the old object - rhs.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual shared_ptr<BaseMatrix<T>> operator *(const BaseMatrix<T>& rhs) const
/// @brief Virtual function to implement an overload on the * operator.
/// @pre T needs to have a * operator defined.
///      The number of rows for rhs, must equal the number of columns for the called matrix.
/// @post Returns a pointer to a new object that is the old object * rhs.
/// @param1 The matrix that the called object is to be multiplied against.
/// @return Returns a pointer to a new object that is the old object * rhs.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn virtual shared_ptr<BaseMatrix<T>> clone() const
/// @brief Virtual function to replace a copy constructor. Returns a copy of called object.
/// @pre None.
/// @post Returns a pointer to a new object that is a clone of the called object.
/// @return Returns a pointer to a new object that is a clone of the called object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn ostream& operator <<(ostream& out, const BaseMatrix<T>* rhs)
/// @brief Outputs rhs to ostream.
/// @pre Requires BaseMatrix derived class to have () operator defined from above.
/// @post ostream is appended with information on rhs.
/// @param1 ostream operator to be changed.
/// @param2 BaseMatrix pointer whose object info is to be output.
/// @return ostream& with debug string for BaseMatrix information added to the stream.
//////////////////////////////////////////////////////////////////////

#ifndef BASE_MATRIX_H
#define BASE_MATRIX_H

#include <iostream>
#include <memory>
#include "../utilities/math_vector.h"

enum MatrixType
{
  BASE,
  DENSE,
  TRIDIAGONAL,
  DIAGONAL,
  UPPER_TRIANGULAR,
  LOWER_TRIANGULAR,
  SYMMETRIC_MATRIX
};

template <typename T>
class BaseMatrix;

template <typename T>
ostream& operator <<(ostream& out, const BaseMatrix<T>* rhs);


template <typename T>
class BaseMatrix
{
protected:
  MathVector<T> * m_vectors;
  unsigned long m_num_rows;
  unsigned long m_num_columns;
public:
  virtual ~BaseMatrix() {}

  // Getters
  unsigned long getNumRows() const { return m_num_rows; }
  unsigned long getNumColumns() const { return m_num_columns; }
  virtual MatrixType type() const = 0;

  // Index operators
  virtual MathVector<T>& operator [](unsigned long index) = 0;
  virtual MathVector<T>& operator [](unsigned long index) const = 0;
  virtual T operator ()(unsigned long row_index, unsigned long column_index) const = 0;
  virtual void operator ()(unsigned long row_index, unsigned long column_index, T element) = 0;

  // Matrix operations
  virtual shared_ptr<BaseMatrix<T>> transpose() const = 0;
  virtual shared_ptr<BaseMatrix<T>> operator *(double c) const = 0;
  virtual shared_ptr<BaseMatrix<T>> operator +(const BaseMatrix<T>& rhs) const = 0;
  virtual shared_ptr<BaseMatrix<T>> operator -(const BaseMatrix<T>& rhs) const = 0;
  virtual shared_ptr<BaseMatrix<T>> operator *(const BaseMatrix<T>& rhs) const = 0;

  // Replacements for operations that don't work with inherited classes
  virtual shared_ptr<BaseMatrix<T>> clone() const = 0;


  friend ostream& operator << <>(ostream& out, const BaseMatrix<T>* rhs);
};

#include "base_matrix.hpp"

#endif //BASE_MATRIX_H
