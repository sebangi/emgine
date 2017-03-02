#ifndef FONCTION_SOURCE_CHOIX_H
#define FONCTION_SOURCE_CHOIX_H

/** \file fonction_source_choix.h
 * \brief Fichier de déclaration de la classe fonction_source_choix.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_base_source.h"

/**
 * \class fonction_source_choix
 * \brief Classe décrivant une fonction source de type choix.
 * \author Sébastien Angibaud
 */
class fonction_source_choix : public fonction_base_source
{
    public:
        fonction_source_choix(fonctions_conteneur * conteneur, const QStringList& selection = QStringList());
        ~fonction_source_choix();

        base_fonction_widget *generer_fonction_widget();
        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        const QStringList & get_selection() const;
        void set_selection(const QStringList & selection);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);
        bool get_multiple_selection() const;
        const QStringList& get_choix() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief La liste des choix courants. */
        QStringList m_selection;

        /** \brief Booléen indiquant si les choix sont à écrire sur une seule ligne. */
        bool m_sur_une_seule_ligne;

        /** \brief Booléen indiquant si la sélection peut être multiple. */
        bool m_multiple_selection;

        /** \brief La liste des choix possibles. */
        QStringList m_choix;
};

#endif // FONCTION_SOURCE_CHOIX_H
