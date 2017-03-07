#include "entete/dictionnaire/comptage_mot.h"
#include "entete/dictionnaire/indice_lettre.h"

/*----------------------------------------------------------------------------*/
comptage_mot::comptage_mot( const QString& mot )
  : m_alphabet( indice_lettre::count, 0 )
{
  QString::const_iterator it;
  indice_lettre ind;

  for (it = mot.constBegin(); it!=mot.constEnd(); ++it)
    if ( ind(it->toLatin1()) == indice_lettre::hors_bornes )
      ++m_extra[it->toLatin1()];
    else
      ++m_alphabet[ind(it->toLatin1())];
} // comptage_mot::comptage_mot()

/*----------------------------------------------------------------------------*/
bool comptage_mot::operator<( const comptage_mot& that ) const
{
  bool result;

  if ( m_alphabet == that.m_alphabet )
    {
      bool stop = false;
      std::map<char, unsigned int>::const_iterator it_e, it_te;

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
} // comptage_mot::operator<()

/*----------------------------------------------------------------------------*/
bool comptage_mot::est_inclus_dans( const comptage_mot& that ) const
{
  bool result = true;

  for (unsigned int i=0; (i!=m_alphabet.size()) && result; ++i)
    result = m_alphabet[i] <= that.m_alphabet[i];

  std::map<char, unsigned int>::const_iterator it, it_t;

  for ( it=m_extra.begin(), it_t=that.m_extra.begin();
	(it!=m_extra.end()) && (it_t!=that.m_extra.end()) && result; )
    if ( it->first == it_t->first )
      {
	result = it->second <= it_t->second;
	++it;
	++it_t;
      }
    else if (  it_t->first < it->first )
      ++it_t;
    else
      result = false;

  return result;
} // comptage_mot::est_inclus_dans()
