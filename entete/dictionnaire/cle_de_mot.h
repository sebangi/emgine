#ifndef __CLE_DE_MOT_HPP__
#define __CLE_DE_MOT_HPP__

#include <QString>

#include "entete/dictionnaire/mot_binaire.h"
#include "entete/dictionnaire/comptage_mot.h"

class cle_de_mot
{
public:
    cle_de_mot( const QString& mot );

    unsigned int taille() const { return m_bits.taille(); }
    unsigned int code_binaire() const { return m_bits.code(); }

    const mot_binaire& le_mot_binaire() const { return m_bits; }
    const comptage_mot& comptage() const { return m_comptage; }

private:
    mot_binaire m_bits;

    comptage_mot m_comptage;

}; // class cle_de_mot

#endif // __CLE_DE_MOT_HPP__
