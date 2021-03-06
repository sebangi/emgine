#ifndef FONCTION_SOURCE_PERMUTATION_H
#define FONCTION_SOURCE_PERMUTATION_H

/** \file fonction_source_permutation.h
 * \brief Fichier de déclaration de la classe fonction_source_permutation.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_base_source.h"

/**
 * \class fonction_source_permutation
 * \brief Classe décrivant une fonction source générant toutes les permutations d'une liste d'éléments fournis.
 * \author Sébastien Angibaud
 */
class fonction_source_permutation : public fonction_base_source
{
    public:
        fonction_source_permutation(fonctions_conteneur * conteneur);
        ~fonction_source_permutation();

        void initialisation_par_defaut();
        void initialisation_par_defaut(QString elements = "");
        base_fonction_widget *generer_fonction_widget();
        void executer( compilateur & compil, textes & textes_in, textes & texte_sout );
        QString get_valeur_courte() const;
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
};

#endif // FONCTION_SOURCE_PERMUTATION_H
