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

template <typename T>
void bm_swap(BaseMatrix<T>& lhs, BaseMatrix<T>& rhs)
{
  swap(lhs.m_num_rows, rhs.m_num_rows);
  swap(lhs.m_num_columns, rhs.m_num_columns);
  swap(lhs.m_vectors, rhs.m_vectors);
}

#endif //BASE_MATRIX_HPP
