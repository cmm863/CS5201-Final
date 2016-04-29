//////////////////////////////////////////////////////////////////////
/// @file upper_tri_matrix.hpp
/// @author Connor McBride
/// @brief Contains the UpperTriMatrix class implementation information
//////////////////////////////////////////////////////////////////////

#ifndef UPPER_TRI_MATRIX_HPP
#define UPPER_TRI_MATRIX_HPP

#include "upper_tri_matrix.h"

template <typename T>
UpperTriMatrix<T>::UpperTriMatrix()
{
  this->m_num_columns = 0;
  this->m_num_rows = 0;
  this->m_vectors = nullptr;
}

template <typename T>
UpperTriMatrix<T>::UpperTriMatrix(unsigned long n)
{
  // Set actual size of matrix
  this->m_num_rows = n;
  this->m_num_columns = n;

  // Create m_vectors
  this->m_vectors = new MathVector<T>[this->m_num_rows];

  for(unsigned long i = 0; i < n; i++)
  {
    // Only create the size needed
    this->m_vectors[i] = MathVector<T>(this->m_num_rows - i);
    for(unsigned long j = 0; j < this->m_vectors[i].capacity(); j++)
      this->m_vectors[i].push(0);
  }
}

template <typename T>
UpperTriMatrix<T>::~UpperTriMatrix()
{
  delete [] this->m_vectors;
}

template <typename T>
MatrixType UpperTriMatrix<T>::type() const
{
  return UPPER_TRIANGULAR;
}

template <typename T>
MathVector<T>& UpperTriMatrix<T>::operator[](unsigned long index)
{
  if(index < 0 || index >= this->m_num_rows)
    throw out_of_range("Out of Range : [] UpperTriMatrix.");
  return this->m_vectors[index];
}

template <typename T>
MathVector<T>& UpperTriMatrix<T>::operator[](unsigned long index) const
{
  if(index < 0 || index >= this->m_num_rows)
    throw out_of_range("Out of Range : [] UpperTriMatrix.");
  return this->m_vectors[index];
}

template <typename T>
T UpperTriMatrix<T>::operator()(unsigned long row_index, unsigned long column_index) const
{
  // Check if the indices are within bounds
  if(row_index > this->getNumRows() || row_index < 0 || column_index > this->getNumColumns() || column_index < 0)
    throw out_of_range("Out of Range : () UpperTri const.");

  // If not in the upper triangle
  if(row_index > column_index)
    return 0;

  return (*this)[row_index][column_index - row_index];
}

template <typename T>
void UpperTriMatrix<T>::operator()(unsigned long row_index, unsigned long column_index, T element)
{
  // Check if the indices are within bounds
  if(row_index > this->getNumRows() || row_index < 0 || column_index > this->getNumColumns() || column_index < 0)
    throw out_of_range("Out of Range : () UpperTri");
  // If in upper triangle
  if(row_index > column_index)
  {
    return;
  }
  (*this)[row_index][column_index - row_index] = element;
}

template <typename T>
shared_ptr<BaseMatrix<T>> UpperTriMatrix<T>::transpose() const
{
  return nullptr;
}

template <typename T>
shared_ptr<BaseMatrix<T>> UpperTriMatrix<T>::operator*(double c) const
{
  shared_ptr<BaseMatrix<T>> ret = this->clone();
  for(unsigned long i = 0; i < ret->getNumRows(); i++)
    (*ret)[i] = c * (*ret)[i];
  return ret;
}

template <typename T>
shared_ptr<BaseMatrix<T>> UpperTriMatrix<T>::operator+(const BaseMatrix<T>& rhs) const
{
  if(this->m_num_columns != rhs.getNumColumns() || this->m_num_rows != rhs.getNumRows())
    throw domain_error("Sizes not equal : + UpperTriMatrix.");
  shared_ptr<BaseMatrix<T>> ret = rhs.clone();
  for(unsigned long i = 0; i < ret->getNumRows(); i++)
    for(unsigned long j = i; j < ret->getNumColumns(); j++)
      (*ret)(i, j, (*ret)(i, j) + (*this)(i, j));
  return ret;
}

template <typename T>
shared_ptr<BaseMatrix<T>> UpperTriMatrix<T>::operator-(const BaseMatrix<T>& rhs) const
{
  if(this->m_num_columns != rhs.getNumColumns() || this->m_num_rows != rhs.getNumRows())
    throw domain_error("Sizes not equal : - UpperTriMatrix.");

  shared_ptr<BaseMatrix<T>> ret = rhs.clone();
  for(unsigned long i = 0; i < ret->getNumRows(); i++)
    for(unsigned long j = i; j < ret->getNumColumns(); j++)
      (*ret)(i, j, -1 * (*ret)(i, j) + (*this)(i, j));

  return ret;
}

template <typename T>
shared_ptr<BaseMatrix<T>> UpperTriMatrix<T>::operator*(const BaseMatrix<T>& rhs) const
{
  if(this->getNumColumns() != rhs.getNumColumns())
    throw domain_error("Matrix sizes not compatible: * UpperTriMatrix.");

  shared_ptr<BaseMatrix<T>> ret = make_shared<DenseMatrix<T>>(this->getNumRows(), rhs.getNumColumns());
  for(unsigned long i = 0; i < ret->getNumRows(); i++)
    for(unsigned long j = 0; j < ret->getNumColumns(); j++)
      for(unsigned long k = j; k < this->getNumColumns(); k++)
        (*ret)(i, j, (*ret)(i, j) + (*this)(i, k) * rhs(k, j));
  return ret;
}

template <typename T>
shared_ptr<BaseMatrix<T>> UpperTriMatrix<T>::clone() const
{
  shared_ptr<BaseMatrix<T>> ret = make_shared<UpperTriMatrix>(this->m_num_rows);
  for(unsigned long i = 0; i < this->m_num_rows; i++)
    (*ret)[i] = this->m_vectors[i];

  return ret;
}

#endif //UPPER_TRI_MATRIX_HPP
