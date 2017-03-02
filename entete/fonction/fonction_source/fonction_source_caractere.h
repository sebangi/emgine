#ifndef FONCTION_SOURCE_CARACTERE_H
#define FONCTION_SOURCE_CARACTERE_H

/** \file fonction_source_caractere.h
 * \brief Fichier de déclaration de la classe fonction_source_caractere.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_base_source.h"

/**
 * \class fonction_source_caractere
 * \brief Classe décrivant une fonction source de type caractères.
 * \author Sébastien Angibaud
 */
class fonction_source_caractere : public fonction_base_source
{
    public:
        fonction_source_caractere(fonctions_conteneur * conteneur, QString valeur = "");
        ~fonction_source_caractere();

        base_fonction_widget *generer_fonction_widget();        
        void executer( compilateur & compil, textes & textes_in, textes & texte_sout );
        QString get_valeur_courte() const;
        QString get_valeur() const;
        void set_valeur(QString valeur);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);

    private:
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief La valeur de la fonction. */
        QString m_valeur;
};

#endif // FONCTION_SOURCE_CARACTERE_H
