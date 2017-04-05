#ifndef FONCTION_SCISSION_H
#define FONCTION_SCISSION_H

/** \file fonction_scission.h
 * \brief Fichier de déclaration de la classe fonction_scission.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_scission
 * \brief Classe décrivant une fonction réalisant la scission des caractères, des mots, des lignes ou des textes.
 * \author Sébastien Angibaud
 */
class fonction_scission : public base_fonction
{
    public:
        fonction_scission(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        void callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out );
        void callback_param_3( compilateur &compil, textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_SCISSION_H
