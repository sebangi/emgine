#ifndef FONCTION_CONCATENATION_H
#define FONCTION_CONCATENATION_H

/** \file fonction_concatenation.h
 * \brief Fichier de déclaration de la classe fonction_concatenation.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_concatenation
 * \brief Classe décrivant une fonction réalisant la concatenation de textes.
 * \author Sébastien Angibaud
 */
class fonction_concatenation : public base_fonction
{
    public:
        fonction_concatenation(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_CONCATENATION_H
