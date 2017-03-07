#ifndef __ALPHA_VECTOR_HPP__
#define __ALPHA_VECTOR_HPP__

#include <map>
#include <vector>

template<typename T>
class alpha_vector
{
public:
  typedef T value_type;

public:
  alpha_vector( const T& init );

  value_type& operator[]( char c );

  bool operator<( const alpha_vector& that ) const;

private:
  std::vector<T> m_alphabet;

  std::map<char, T> m_extra;

}; // class alpha_vector

#include "impl/alpha_vector.tpp"

#endif // __ALPHA_VECTOR_HPP__
