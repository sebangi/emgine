#include "entete/dictionnaire/lettre_dictionnaire.h"

#include <iostream>

lettre_dictionnaire::lettre_dictionnaire()
    : m_est_mot(false)
{
    m_suivants.resize(26, NULL);
}

lettre_dictionnaire::~lettre_dictionnaire()
{
    for ( type_tab_lettres::iterator it = m_suivants.begin(); it != m_suivants.end(); ++it )
        if ( *it != NULL )
            delete *it;
}

lettre_dictionnaire *lettre_dictionnaire::get_suivant( int pos )
{
    if ( pos > 25 || pos < 0 )
    {
        std::cout << "erreur : " <<  pos << std::endl;
        return NULL;
    }

    if ( m_suivants[pos] == NULL )
        m_suivants[pos] = new lettre_dictionnaire();

    return m_suivants[pos];
}

lettre_dictionnaire *lettre_dictionnaire::suivant( int pos )
{
    return m_suivants[pos];
}

void lettre_dictionnaire::set_est_mot()
{
    m_est_mot = true;
}

bool lettre_dictionnaire::est_mot()
{
    return m_est_mot;
}
