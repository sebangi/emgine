#ifndef FONCTION_TRANSPOSITION_H
#define FONCTION_TRANSPOSITION_H

/** \file fonction_transposition.h
 * \brief Fichier de déclaration de la classe fonction_transposition.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_transposition
 * \brief Classe décrivant une fonction réalisant la transposition des caractères ou des mots.
 * \author Sébastien Angibaud
 */
class fonction_transposition : public base_fonction
{
    public:
        fonction_transposition(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_TRANSPOSITION_H
