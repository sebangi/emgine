#ifndef __COMPTAGE_MOT_HPP__
#define __COMPTAGE_MOT_HPP__

#include <QString>
#include <vector>
#include <map>

class comptage_mot
{
public:
  comptage_mot( const QString& mot );

  bool operator<( const comptage_mot& that ) const;

  bool est_inclus_dans( const comptage_mot& that ) const;

private:
  std::vector<unsigned int> m_alphabet;

  std::map<char, unsigned int> m_extra;

}; // class comptage_mot

#endif // __COMPTAGE_MOT_HPP__
