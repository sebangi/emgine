#ifndef FONCTION_CHOISIR_SEPARATEUR_H
#define FONCTION_CHOISIR_SEPARATEUR_H

/** \file fonction_choisir_separateur.h
 * \brief Fichier de déclaration de la classe fonction_choisir_separateur.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

/**
 * \class fonction_choisir_separateur
 * \brief Classe décrivant une fonction permettant de choisir les séparateurs (de cractères, de mots et de lignes).
 * \author Sébastien Angibaud
 */
class fonction_choisir_separateur : public base_fonction
{
    public:
        fonction_choisir_separateur(fonctions_conteneur * conteneur);
        ~fonction_choisir_separateur();

        void initialisation_par_defaut();
        void initialisation_par_defaut(QString separ_caractere = "", QString separ_mot = " ", QString separ_ligne = "\n");
        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
        void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        void callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
};

#endif // FONCTION_CHOISIR_SEPARATEUR_H
