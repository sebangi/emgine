#ifndef FONCTION_SOURCE_BOOLEEN_H
#define FONCTION_SOURCE_BOOLEEN_H

/** \file fonction_source_booleen.h
 * \brief Fichier de déclaration de la classe fonction_source_booleen.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_base_source.h"

/**
 * \class fonction_source_booleen
 * \brief Classe décrivant une fonction source de type booléen (Oui ou Non).
 * \author Sébastien Angibaud
 */
class fonction_source_booleen : public fonction_base_source
{
    public:
        fonction_source_booleen(fonctions_conteneur * conteneur, bool valeur = false);
        ~fonction_source_booleen();

        base_fonction_widget *generer_fonction_widget();
        void executer( compilateur & compil, const textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        bool get_valeur() const;
        void set_valeur(bool valeur);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);

    private:
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief La valeur de la fonction. */
        bool m_valeur;
};

#endif // FONCTION_SOURCE_BOOLEEN_H
