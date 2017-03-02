#ifndef FREQUENCE_H
#define FREQUENCE_H

/**
 * \file frequence.h
 * \brief Fichier de déclaration de la classe frequence.
 * \author Sébastien Angibaud
 */

#include "entete/element/base_element.h"

/**
 * \class frequence
 * \brief Classe décrivant la fréquence d'un élément.
 * \author Sébastien Angibaud
 */
class frequence
{
    public:
        frequence(base_element e, bool force_upper_case);

        bool operator<( const frequence& f ) const;
        base_element get_element() const;
        int get_occurrence() const;
        void ajouter_occurrence();

    private:
        /** \brief Le nombre d'occurrence de l'élément. */
        int m_occurrence;

        /** \brief L'élément compté. */
        base_element m_element;
};

#endif // FREQUENCE_H

