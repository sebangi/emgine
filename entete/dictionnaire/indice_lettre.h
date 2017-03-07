#ifndef __INDICE_LETTRE_HPP__
#define __INDICE_LETTRE_HPP__

class indice_lettre
{
public:
  unsigned int operator()( char c ) const
  {
    if ( (c >= 'A') && (c <= 'Z') )
      return c - 'A';
    else
      return hors_bornes;
  }

public:
  static const unsigned int hors_bornes = (sizeof(unsigned int) * 8) - 1;
  static const unsigned int count = 'Z' - 'A' + 1;

}; // class indice_lettre

#endif // __INDICE_LETTRE_HPP__
