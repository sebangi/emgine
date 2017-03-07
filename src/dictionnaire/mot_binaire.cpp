#include "entete/dictionnaire/mot_binaire.h"
#include "entete/dictionnaire/indice_lettre.h"

/*----------------------------------------------------------------------------*/
mot_binaire::mot_binaire( const QString& s )
  : m_bits(0), m_nb_bits(0)
{
  indice_lettre ind;
  QString::const_iterator it;

  for (it = s.constBegin(); it != s.constEnd(); ++it)
    {
      unsigned int masque = ((unsigned int)1 << ind(it->toLatin1()));
      if ( !(m_bits & masque) )
	{
	  ++m_nb_bits;
	  m_bits |= masque;
	}
    }
} // mot_binaire::mot_binaire()
