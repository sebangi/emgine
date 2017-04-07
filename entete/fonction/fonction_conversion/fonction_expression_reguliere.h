#ifndef FONCTION_expression_reguliere_H
#define FONCTION_expression_reguliere_H

/** \file fonction_expression_reguliere.h
 * \brief Fichier de déclaration de la classe fonction_expression_reguliere.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_expression_reguliere
 * \brief Classe décrivant une fonction qui filtre les mots selon un dictionnaire.
 * \author Sébastien Angibaud
 */
class fonction_expression_reguliere : public base_fonction
{
    public:
        fonction_expression_reguliere(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_expression_reguliere_H
