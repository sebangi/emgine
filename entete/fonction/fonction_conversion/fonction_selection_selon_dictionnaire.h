#ifndef FONCTION_SELECTION_SELON_DICTIONNAIRE_H
#define FONCTION_SELECTION_SELON_DICTIONNAIRE_H

/** \file fonction_selection_selon_dictionnaire.h
 * \brief Fichier de déclaration de la classe fonction_selection_selon_dictionnaire.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_selection_selon_dictionnaire
 * \brief Classe décrivant une fonction filtrant les textes selon un dictionnaire.
 * \author Sébastien Angibaud
 */
class fonction_selection_selon_dictionnaire : public base_fonction
{
    public:
        fonction_selection_selon_dictionnaire(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_SELECTION_SELON_DICTIONNAIRE_H
