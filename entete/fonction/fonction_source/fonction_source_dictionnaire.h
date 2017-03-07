#ifndef FONCTION_SOURCE_DICTIONNAIRE_H
#define FONCTION_SOURCE_DICTIONNAIRE_H

/** \file fonction_source_dictionnaire.h
 * \brief Fichier de déclaration de la classe fonction_source_dictionnaire.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_base_source.h"

/**
 * \class fonction_source_dictionnaire
 * \brief Classe décrivant une fonction source ajoutant un dictionnaire.
 * \author Sébastien Angibaud
 */
class fonction_source_dictionnaire : public fonction_base_source
{
    public:
        fonction_source_dictionnaire(fonctions_conteneur * conteneur);
        ~fonction_source_dictionnaire();

        base_fonction_widget *generer_fonction_widget();
        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        QString get_nom_fichier() const;
        void set_nom_fichier(QString nom_fichier);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & nom_fichier);

    private:
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief Le nom du fichier. */
        QString m_nom_fichier;
};

#endif // FONCTION_SOURCE_DICTIONNAIRE_H
