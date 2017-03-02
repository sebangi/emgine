#ifndef FONCTION_SOURCE_ENTIER_H
#define FONCTION_SOURCE_ENTIER_H

/** \file fonction_source_entier.h
 * \brief Fichier de déclaration de la classe fonction_source_entier.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_base_source.h"

/**
 * \class fonction_source_entier
 * \brief Classe décrivant une fonction source de type entier.
 * \author Sébastien Angibaud
 */
class fonction_source_entier : public fonction_base_source
{
    public:
        fonction_source_entier(fonctions_conteneur * conteneur, int valeur = 0);
        ~fonction_source_entier();

        QString get_valeur_courte() const;
        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        int get_valeur() const;
        void set_valeur(int valeur);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);

    private:
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief La valeur de la fonction. */
        int m_valeur;
};

#endif // FONCTION_SOURCE_ENTIER_H
