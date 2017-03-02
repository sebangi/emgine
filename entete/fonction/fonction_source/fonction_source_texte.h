#ifndef FONCTION_SOURCE_TEXTE_H
#define FONCTION_SOURCE_TEXTE_H

/** \file fonction_source_texte.h
 * \brief Fichier de déclaration de la classe fonction_source_texte.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_base_source.h"

/**
 * \class fonction_source_texte
 * \brief Classe décrivant une fonction source de type texte.
 * \author Sébastien Angibaud
 */
class fonction_source_texte : public fonction_base_source
{
    public:
        fonction_source_texte(fonctions_conteneur * conteneur, QString texte = "");
        ~fonction_source_texte();

        void initialisation_par_defaut();
        void initialisation_par_defaut(QString separ_caractere = "", QString separ_mot = " ", QString separ_ligne = "\n");
        base_fonction_widget *generer_fonction_widget();
        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        QString get_valeur() const;
        void set_valeur(QString valeur);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
        void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        void callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );

    private:
        /** \brief La valeur de la fonction. */
        QString m_texte;
};

#endif // FONCTION_SOURCE_TEXTE_H
