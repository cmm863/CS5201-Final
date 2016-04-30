//////////////////////////////////////////////////////////////////////
/// @file dense_matrix.hpp
/// @author Connor McBride
/// @brief Contains the DenseMatrix class implementation information.
//////////////////////////////////////////////////////////////////////

#ifndef DENSE_MATRIX_HPP
#define DENSE_MATRIX_HPP

template <typename T>
DenseMatrix<T>::DenseMatrix()
{
  this->m_num_columns = 0;
  this->m_num_rows = 0;
  this->m_vectors = nullptr;
}

template <typename T>
DenseMatrix<T>::DenseMatrix(const shared_ptr<BaseMatrix<T>> rhs)
{
  this->m_num_rows = rhs->getNumRows();
  this->m_num_columns = rhs->getNumColumns();
  this->m_vectors = new MathVector<T>[this->m_num_rows];

  for(uint32_t i = 0; i < this->m_num_rows; i++)
  {
    this->m_vectors[i] = (*rhs)[i];
  }
}

template <typename T>
DenseMatrix<T>::DenseMatrix(uint32_t n)
{
  this->m_num_rows = n;
  this->m_num_columns = n;
  this->m_vectors = new MathVector<T>[this->m_num_rows];
  for(uint32_t i = 0; i < n; i++)
  {
    this->m_vectors[i] = MathVector<T>(n);
    for(uint32_t j = 0; j < this->m_vectors[i].capacity(); j++)
      this->m_vectors[i].push(0);
  }
}

template <typename T>
DenseMatrix<T>::DenseMatrix(uint32_t m, uint32_t n)
{
  this->m_num_rows = m;
  this->m_num_columns = n;
  this->m_vectors = new MathVector<T>[this->m_num_rows];
  for(uint32_t i = 0; i < m; i++)
  {
    this->m_vectors[i] = MathVector<T>(n);
    for(uint32_t j = 0; j < this->m_vectors[i].capacity(); j++)
      this->m_vectors[i].push(0);
  }
}

template <typename T>
DenseMatrix<T>::DenseMatrix(DenseMatrix<T>&& other)
{
  this->m_num_rows = other.m_num_rows;
  this->m_num_columns = other.m_num_columns;
  this->m_vectors = other.m_vectors;
  other.m_vectors = nullptr;
}

template <typename T>
DenseMatrix<T>::~DenseMatrix()
{
  delete [] this->m_vectors;
}

template <typename T>
MatrixType DenseMatrix<T>::type() const
{
  return DENSE;
}

template <typename T>
MathVector<T>& DenseMatrix<T>::operator[](uint32_t index)
{
  if(index < 0 || index >= this->m_num_rows)
    throw out_of_range("Out of Range: DenseMatrix");

  return this->m_vectors[index];
}

template <typename T>
MathVector<T>& DenseMatrix<T>::operator[](uint32_t index) const
{
  if(index < 0 || index >= this->m_num_rows)
    throw out_of_range("Out of Range: DenseMatrix");
  return this->m_vectors[index];
}

template <typename T>
T DenseMatrix<T>::operator()(uint32_t row_index, uint32_t column_index) const
{
  return (*this)[row_index][column_index];
}

template <typename T>
void DenseMatrix<T>::operator()(uint32_t row_index, uint32_t column_index, T element)
{
  (*this)[row_index][column_index] = element;
}

template <typename T>
shared_ptr<BaseMatrix<T>> DenseMatrix<T>::transpose() const
{
  shared_ptr<BaseMatrix<T>> ret = make_shared<DenseMatrix<T>>(this->getNumColumns(), this->getNumRows());
  for(uint32_t i = 0; i < ret->getNumRows(); i++)
    for(uint32_t j = 0; j < ret->getNumColumns(); j++)
      (*ret)[i][j] = (*this)(j, i);
  return ret;
}

template <typename T>
DenseMatrix<T>& DenseMatrix<T>::operator =(DenseMatrix<T> other)
{
  bm_swap(*this, other);

  return *this;
}

template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator*(double c) const
{
  DenseMatrix<T> ret(this->clone());
  for(uint32_t i = 0; i < ret.getNumRows(); i++)
    ret[i] = c * ret[i];
  return ret;
}

template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator+(const BaseMatrix<T>& rhs) const
{
  if(this->m_num_columns != rhs.getNumColumns() || this->m_num_rows != rhs.getNumRows())
    throw domain_error("Sizes not equal. + DenseMatrix");

  DenseMatrix<T> ret(this->clone());
  for(uint32_t i = 0; i < ret.getNumRows(); i++)
    ret[i] += rhs[i];
  return ret;
}


template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator-(const BaseMatrix<T>& rhs) const
{
  if(this->m_num_columns != rhs.getNumColumns() || this->m_num_rows != rhs.getNumRows())
    throw domain_error("Sizes not equal. - DenseMatrix");

  DenseMatrix<T> ret(this->clone());
  for(uint32_t i = 0; i < ret.getNumRows(); i++)
    ret[i] -= rhs[i];
  return ret;
}

template <typename T>
DenseMatrix<T> DenseMatrix<T>::operator*(const BaseMatrix<T>& rhs) const
{
  if(this->getNumColumns() != rhs.getNumRows())
    throw domain_error("Matrix sizes not compatible: * DenseMatrix.");

  DenseMatrix<T> ret(this->getNumRows(), rhs.getNumColumns());
  for(uint32_t i = 0; i < ret.getNumRows(); i++)
    for(uint32_t j = 0; j < ret.getNumColumns(); j++)
      for(uint32_t k = 0; k < this->getNumColumns(); k++)
        ret[i][j] += (*this)(i, k) * rhs(k, j);

  return ret;
}

template <typename T>
shared_ptr<BaseMatrix<T>> DenseMatrix<T>::clone() const
{
  shared_ptr<BaseMatrix<T>> ret = make_shared<DenseMatrix<T>>(this->m_num_rows, this->m_num_columns);
  for (uint32_t i = 0; i < this->m_num_rows; i++)
    (*ret)[i] = this->m_vectors[i];
  return ret;
}


#endif //DENSE_MATRIX_HPP
