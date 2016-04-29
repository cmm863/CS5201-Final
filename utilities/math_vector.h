//////////////////////////////////////////////////////////////////////
/// @file mathvector.h
/// @author Connor McBride
/// @brief Contains the declaration information for the MathVector class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @class MathVector
/// @brief Is a template class that is a container.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn MathVector<T>::MathVector()
/// @brief Explicit definition of the default constructor.
/// @pre None
/// @post A MathVector class of type T is created with m_size 0
/// @return Returns MathVector object instantiated
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn MathVector<T>::MathVector(unsigned long size)
/// @brief Overload of constructor which takes an int for size
/// @pre None
/// @post A MathVector class of type T is created with m_size size
/// @return Returns MathVector object instantiated
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn MathVector<T>::~MathVector()
/// @brief Overload of the destructor
/// @pre None.
/// @post All m_elements of the calling object are cleared.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn unsigned long T::size() const
/// @brief Get function for m_size.
/// @pre None.
/// @post Returns size of MathVector.
/// @return Returns m_size of the called object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn unsigned long T::capacity() const
/// @brief Get function for m_capacity.
/// @pre None.
/// @post Returns capacity of MathVector.
/// @return Returns m_capacity of the called object.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn T MathVector<T>::operator [](int index) const
/// @brief Returns a returns element at passed index.
/// @pre Index needs to be less than the number of elements.
/// @post Returns a returns element at passed index.
/// @param1 Index of the term to be returned.
/// @return Returns a returns element at passed index.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn friend MathVector<T> operator +(const MathVector<T>& lhs, const MathVector<T>& rhs)
/// @brief Adds two MathVectors together.
/// @pre MathVectors need to be of the same size. T type must have += operator.
/// @post Returns sum of lhs and rhs
/// @param1 MathVector 1 to be added
/// @param2 MathVector 2 to be added
/// @return Sum of lhs and rhs
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn friend MathVector<T> operator -(const MathVector<T>& lhs, const MathVector<T>& rhs)
/// @brief Subtracts rhs MathVector from lhs.
/// @pre MathVectors need to be of the same size. T type must have -= operator.
/// @post Returns difference of lhs and rhs
/// @param1 MathVector 1 to be subracted from
/// @param2 MathVector 2 to be subracted
/// @return Difference of lhs and rhs
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn friend T operator *(const MathVector<T>& lhs, const MathVector<T>& rhs)
/// @brief Dot product of rhs and lhs.
/// @pre T needs to have += operator and * operator.
/// @post Return dot product of rhs & lhs.
/// @param1 MathVector 1
/// @param2 MathVector 2
/// @return Dot of rhs from lhs
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn friend MathVector<T> operator *(double c, const MathVector<T>& rhs)
/// @brief Multiplication c by each element of rhs.
/// @pre T type must have *= operator.
/// @post Returns rhs with each element multiplied by c
/// @param1 constant c to be multiplied
/// @param2 MathVector to be scaled
/// @return Rhs with each element multiplied by c
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn ostream& operator <<(ostream& out, const MathVector<T>& rhs)
/// @brief Outputs rhs to ostream.
/// @pre None.
/// @post ostream is appended with information on rhs.
/// @param1 ostream operator to be changed.
/// @param2 MathVector whose info is to be output.
/// @return ostream& with debug string for MathVector information added to the stream.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/// @fn istream& operator <<(istream& in, MathVector<T>& rhs)
/// @brief Takes in istream and fills MathVector.
/// @pre None.
/// @post Rhs is filled with appropriate information. istream in gets returned.
/// @param1 istream operator to be returned.
/// @param2 MathVector whose info is to be input.
/// @return istream& in.
//////////////////////////////////////////////////////////////////////
#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <iostream>

using namespace std;

template <typename T>
class MathVector;

template <typename T>
MathVector<T> operator +(const MathVector<T>& lhs, const MathVector<T>& rhs);

template <typename T>
MathVector<T> operator -(const MathVector<T>& lhs, const MathVector<T>& rhs);

template <typename T>
MathVector<T> operator *(double c, const MathVector<T>& rhs);

template <typename T>
T operator *(const MathVector<T>& lhs, const MathVector<T>& rhs);

template <typename T>
ostream& operator <<(ostream& out, const MathVector<T>& rhs);

template <typename T>
void mv_swap(MathVector<T>& lhs, MathVector<T>& rhs);


template <typename T>
class MathVector
{
private:
  T * m_elements;
  unsigned long m_size;
  unsigned long m_capacity;
public:
  // Constructors
  MathVector();
  MathVector(unsigned long capacity);
  MathVector(const MathVector& other); // Rule of 3
  MathVector(MathVector&& other); // Rule of 4 1/2
  ~MathVector(); // Rule of 3

  // Getters
  unsigned long size() const;
  unsigned long capacity() const;

  // Functions
  bool push(T element);
  void setToZeroVector();
  T magnitude();

  // Operators
  T& operator [](unsigned long index);
  MathVector& operator =(MathVector other); // Rule of 3
  MathVector& operator +=(const MathVector& rhs);
  MathVector& operator -=(const MathVector& rhs);
  bool operator ==(const MathVector& rhs);
  friend MathVector operator + <>(const MathVector& lhs, const MathVector& rhs);
  friend MathVector operator - <>(const MathVector& lhs, const MathVector& rhs);
  friend MathVector operator * <>(double c, const MathVector& rhs);
  friend T operator * <>(const MathVector& lhs, const MathVector& rhs);
  friend ostream& operator << <>(ostream& out, const MathVector& rhs);

  // Friends
  friend void mv_swap <>(MathVector& lhs, MathVector& rhs); // Rule of 3 1/2
};

#include "math_vector.hpp"

#endif // MATH_VECTOR_H
