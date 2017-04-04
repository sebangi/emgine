#ifndef FONCTION_ROTATION_H
#define FONCTION_ROTATION_H

/** \file fonction_rotation.h
 * \brief Fichier de déclaration de la classe fonction_rotation.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_rotation
 * \brief Classe décrivant une fonction réalisant la rotation des caractères ou des mots.
 * \author Sébastien Angibaud
 */
class fonction_rotation : public base_fonction
{
    public:
        fonction_rotation(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_ROTATION_H
