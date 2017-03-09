#ifndef FONCTION_ENTIER_EN_CHIFFRE_ROMAIN_H
#define FONCTION_ENTIER_EN_CHIFFRE_ROMAIN_H

/** \file fonction_entier_en_chiffre_romain.h
 * \brief Fichier de déclaration de la classe fonction_entier_en_chiffre_romain.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_entier_en_chiffre_romain
 * \brief Classe décrivant une fonction convertissant les nombres en chiffre romain.
 * \author Sébastien Angibaud
 */
class fonction_entier_en_chiffre_romain : public base_fonction
{
    public:
        fonction_entier_en_chiffre_romain(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_ENTIER_EN_CHIFFRE_ROMAIN_H
