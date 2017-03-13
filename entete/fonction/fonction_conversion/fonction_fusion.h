#ifndef FONCTION_FUSION_H
#define FONCTION_FUSION_H

/** \file fonction_fusion.h
 * \brief Fichier de déclaration de la classe fonction_fusion.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_fusion
 * \brief Classe décrivant une fonction réalisant la fusion des caractères, des mots, des lignes ou des textes.
 * \author Sébastien Angibaud
 */
class fonction_fusion : public base_fonction
{
    public:
        fonction_fusion(fonctions_conteneur * conteneur);

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

#endif // FONCTION_FUSION_H
