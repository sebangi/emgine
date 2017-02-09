#ifndef FONCTION_BASE_SOURCE_H
#define FONCTION_BASE_SOURCE_H

/** \file fonction_base_source.h
 * \brief Fichier de déclaration de la classe fonction_base_source.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class fonctions_conteneur;

/**
 * \class fonction_base_source
 * \brief Classe commune à toutes les fonctions de type sortie.
 * \author Sébastien Angibaud
 */
class fonction_base_source : public base_fonction
{
    public:
        fonction_base_source(fonctions_conteneur * conteneur);
        ~fonction_base_source();        

        /** --------------------------------------------------------------------------------------
         * \brief Fonction virtuelle pure d'accès à la valeur de la fonction au format QString.
         * \return La valeur de la fonction au format QString.
         */
        virtual QString get_string_valeur() const = 0;

        /** --------------------------------------------------------------------------------------
         * \brief Fonction virtuelle pure d'initlisation de la valeur de la fonction au format QString.
         * \param valeur La nouvelle valeur de la fonction.
         */
        virtual void set_string_valeur(const QString & valeur) = 0;
};

#endif // FONCTION_BASE_SOURCE_H
