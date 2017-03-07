#ifndef FONCTION_ANAGRAMME_H
#define FONCTION_ANAGRAMME_H

/** \file fonction_anagramme.h
 * \brief Fichier de déclaration de la classe fonction_anagramme.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_anagramme
 * \brief Classe décrivant une fonction recherchant les anagrammes de chaque mot.
 * \author Sébastien Angibaud
 */
class fonction_anagramme : public base_fonction
{
    public:
        fonction_anagramme(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_ANAGRAMME_H
