#ifndef FONCTION_filtrage_selon_dictionnaire_H
#define FONCTION_filtrage_selon_dictionnaire_H

/** \file fonction_filtrage_selon_dictionnaire.h
 * \brief Fichier de déclaration de la classe fonction_filtrage_selon_dictionnaire.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_filtrage_selon_dictionnaire
 * \brief Classe décrivant une fonction qui filtre les mots selon un dictionnaire.
 * \author Sébastien Angibaud
 */
class fonction_filtrage_selon_dictionnaire : public base_fonction
{
    public:
        fonction_filtrage_selon_dictionnaire(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_filtrage_selon_dictionnaire_H
