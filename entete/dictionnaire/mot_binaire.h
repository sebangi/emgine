#ifndef __MOT_BINAIRE_HPP__
#define __MOT_BINAIRE_HPP__

#include <QString>

class mot_binaire
{
public:
  mot_binaire( const QString& s );

  unsigned int code() const { return m_bits; }
  unsigned int taille() const { return m_nb_bits; }

  bool est_inclus_dans( unsigned int b ) const
  {
    return (m_bits & b) == m_bits;
  }

  bool contient( unsigned int b ) const
  {
    return (m_bits & b) == b;
  }

private:
  unsigned int m_bits;

  unsigned int m_nb_bits;

}; // class mot_binaire

#endif // __MOT_BINAIRE_HPP__
