//////////////////////////////////////////////////////////////////////
/// @file base_matrix.hpp
/// @author Connor McBride
/// @brief Contains the BaseMatrix class implementation information
//////////////////////////////////////////////////////////////////////

#ifndef BASE_MATRIX_HPP
#define BASE_MATRIX_HPP

template <typename T>
ostream& operator <<(ostream& out, const BaseMatrix<T>& rhs)
{
  out << setprecision(5);
  for(uint32_t i = 0; i < rhs.getNumRows(); i++)
  {
    for (uint32_t j = 0; j < rhs.getNumColumns(); j++)
    {
      out << setw(12) << rhs(i, j);
    }
    out << endl;
  }
  return out;
}

#endif //BASE_MATRIX_HPP
