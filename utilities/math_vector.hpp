//////////////////////////////////////////////////////////////////////
/// @file mathvector.hpp
/// @author Connor McBride
/// @brief Contains the Vector class implementation information
//////////////////////////////////////////////////////////////////////

#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
MathVector<T>::MathVector()
{
  this->m_size = 0;
  this->m_capacity = 1;
  this->m_elements = new T[this->m_capacity]();

  setToZeroVector();
}

template <typename T>
MathVector<T>::MathVector(unsigned long capacity)
{
  this->m_size = 0;
  this->m_capacity = capacity;
  this->m_elements = new T[this->m_capacity];

  setToZeroVector();
}

template <typename T>
MathVector<T>::MathVector(const MathVector& other)
{
  // Standard sets
  this->m_size = other.m_size;
  this->m_capacity = other.m_capacity;

  // Set arrays equal
  this->m_elements = new T[this->m_capacity]();
  for(unsigned long i = 0; i < this->m_size; i++)
  {
    this->m_elements[i] = other.m_elements[i];
  }
}

template <typename T>
MathVector<T>::MathVector(MathVector<T>&& other)
{
  this->m_size = other.m_size;
  this->m_capacity = other.m_capacity;
  this->m_elements = other.m_elements;
  other.m_elements = nullptr;
}

template <typename T>
MathVector<T>::~MathVector()
{
  delete[] this->m_elements;
}

template <typename T>
unsigned long MathVector<T>::size() const
{
  return this->m_size;
}

template <typename T>
unsigned long MathVector<T>::capacity() const
{
  return this->m_capacity;
}

template <typename T>
bool MathVector<T>::push(T element)
{
  try
  {
    if (this->m_size == this->m_capacity)
    {
      // Create temp ptr
      T *temp = nullptr;

      // Increase capacity
      this->m_capacity *= 2;

      // Allocate new size & old data to temp ptr
      temp = new T[this->m_capacity]();
      for (unsigned long i = 0; i < this->m_size; i++)
      {
        temp[i] = this->m_elements[i];
      }

      // Delete old data
      delete[] this->m_elements;

      // Swap ptr
      this->m_elements = nullptr;
      swap(this->m_elements, temp);
    }

    // Add element
    this->m_elements[this->m_size] = element;
    this->m_size++;

    return true;
  }
  catch(...)
  {
    return false;
  }
}

template <typename T>
void MathVector<T>::setToZeroVector()
{
  for(unsigned long i = 0; i < m_capacity; i++)
    m_elements[i] = 0;
  m_size = 0;
  return;
}

template <typename T>
T MathVector<T>::magnitude()
{
  T sumOfSquares = 0;
  for(unsigned long i = 0; i < m_size; i++)
    sumOfSquares += pow(m_elements[i], 2);
  return sqrt(sumOfSquares);
}

template <typename T>
T& MathVector<T>::operator[](unsigned long index)
{
  if(index < 0 || index >= this->m_size)
  {
    cout << index << endl;
    throw out_of_range("Out of Range: MathVector");
  }
  return this->m_elements[index];
}

template <typename T>
MathVector<T>& MathVector<T>::operator =(MathVector<T> other)
{
  mv_swap(*this, other);

  return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator +=(const MathVector<T>& rhs)
{
  if(this->m_size != rhs.m_size)
  {
    cerr << "Sizes not equal + operator" << endl;
  }
  for(unsigned long i = 0; i < this->m_size; i++)
  {
    this->m_elements[i] += rhs.m_elements[i];
  }

  return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator-=(const MathVector <T>& rhs)
{
  if(this->m_size != rhs.m_size)
  {
    cerr << "Sizes not equal - operator" << endl;
  }
  for(unsigned long i = 0; i < this->m_size; i++)
  {
    this->m_elements[i] -= rhs.m_elements[i];
  }

  return *this;
}

template <typename T>
bool MathVector<T>::operator==(const MathVector<T>& rhs)
{
  int x, y;
  for(unsigned long i = 0; i < this->m_size; i++)
  {
    x = (int) (rhs.m_elements[i] * 1000000);
    y = (int) (this->m_elements[i] * 1000000);
    if(x != y)
    {
      return false;
    }
  }
  return true;
}

template <typename T>
MathVector<T> operator +(const MathVector<T>& lhs, const MathVector<T>& rhs)
{
  MathVector<T> ret(lhs);
  return ret += rhs;
}

template <typename T>
MathVector<T> operator -(const MathVector<T>& lhs, const MathVector<T>& rhs)
{
  MathVector<T> ret(lhs);
  return ret -= rhs;
}

template <typename T>
MathVector<T> operator *(double c, const MathVector<T>& rhs)
{
  MathVector<T> ret(rhs);
  for(unsigned long i = 0; i < ret.m_size; i++)
  {
    ret.m_elements[i] *= c;
  }

  return ret;
}

template <typename T>
T operator *(const MathVector<T>& lhs, const MathVector<T>& rhs)
{
  if(lhs.m_size != rhs.m_size)
  {
    cerr << "Size error with * operator (dot product)" << endl;
  }

  T ret = 0;
  for(unsigned long i = 0; i < lhs.m_size; i++)
  {
    ret += lhs.m_elements[i] * rhs.m_elements[i];
  }

  return ret;
}

template <typename T>
ostream& operator <<(ostream& out, const MathVector<T>& rhs)
{
  for(unsigned long i = 0; i < rhs.m_size; i++)
  {
    if(i == rhs.m_size - 1)
    {
      out << rhs.m_elements[i];
    }
    else
    {
      out << rhs.m_elements[i] << ", ";
    }
  }

  return out;
}

template <typename T>
void mv_swap(MathVector<T>& lhs, MathVector<T>& rhs)
{
  swap(lhs.m_size, rhs.m_size);
  swap(lhs.m_capacity, rhs.m_capacity);
  swap(lhs.m_elements, rhs.m_elements);
}

#endif //MATHVECTOR_HPP
