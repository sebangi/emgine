#ifndef FONCTION_SOURCE_FICHIER_TEXTE_H
#define FONCTION_SOURCE_FICHIER_TEXTE_H

#include "entete/fonction/fonction_source/fonction_base_source.h"

class fonction_source_fichier_texte : public fonction_base_source
{
    public:
        fonction_source_fichier_texte(fonctions_conteneur * conteneur);
        ~fonction_source_fichier_texte();

        void initialisation_par_defaut();
        void initialisation_par_defaut(QString separ_caractere = "", QString separ_mot = " ", QString separ_ligne = "\n");
        base_fonction_widget *generer_fonction_widget();

        void executer( compilateur & compil, const textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;

        QString get_nom_fichier() const;
        void set_nom_fichier(QString nom_fichier);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & nom_fichier);

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
        void callback_param_1( compilateur &compil, const textes & textes_in, textes & textes_out );
        void callback_param_2( compilateur &compil, const textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, const textes & textes_in, textes & textes_out );

    private:
        QString m_nom_fichier;
        QString m_contenu_fichier;
};

#endif // FONCTION_SOURCE_FICHIER_TEXTE_H
