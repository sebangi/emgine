#include "indice_lettre.hpp"

/*----------------------------------------------------------------------------*/
template<typename T>
alpha_vector<T>::alpha_vector( const T& init )
  : m_alphabet( indice_lettre::count, init )
{

} // alpha_vector::alpha_vector()

/*----------------------------------------------------------------------------*/
template<typename T>
typename alpha_vector<T>::value_type& alpha_vector<T>::operator[]( char c )
{
  indice_lettre ind;

  if ( ind(c) == indice_lettre::hors_bornes )
    return m_extra[c];
  else
    return m_alphabet[ind(c)];
} // alpha_vector::alpha_vector()

/*----------------------------------------------------------------------------*/
template<typename T>
bool alpha_vector<T>::operator<( const alpha_vector& that ) const
{
  bool result;

  if ( m_alphabet == that.m_alphabet )
    {
      bool stop = false;
      typename std::map<char, value_type>::const_iterator it_e, it_te;

      it_e=m_extra.begin();
      it_te=that.m_extra.begin();

      while ( (it_e!=m_extra.end()) && (it_te!=that.m_extra.end()) && !stop )
	if ( *it_e == *it_te )
	  {
	    ++it_e;
	    ++it_te;
	  }
	else
	  stop = true;

      if ( stop )
	{
	  if ( it_e->first == it_te->first )
	    result = (it_e->second < it_te->second);
	  else
	    result = (it_e->first < it_te->first);
	}
      else
	result = (it_e == m_extra.end()) && (it_te != that.m_extra.end());
    }
  else
    result = std::lexicographical_compare
      ( m_alphabet.begin(), m_alphabet.end(),
	that.m_alphabet.begin(), that.m_alphabet.end() );

  return result;
} // alpha_vector::operator<()
