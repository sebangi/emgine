#ifndef FONCTION_SOURCE_CARACTERE_H
#define FONCTION_SOURCE_CARACTERE_H

#include "entete/fonction/fonction_source/fonction_base_source.h"

class base_fonction_widget;

class fonction_source_caractere : public fonction_base_source
{
    public:
        fonction_source_caractere(fonctions_conteneur * conteneur, QString valeur = "");
        ~fonction_source_caractere();

        base_fonction_widget *generer_fonction_widget();        
        void executer( compilateur & compil, const texte & texte_in, texte & texte_out );
        QString get_aide() const;
        QString get_valeur_courte() const;

        QString get_valeur() const;
        void set_valeur(QString valeur);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);

    private:
        bool est_valide() const;

    private:
        QString m_valeur;
};

#endif // FONCTION_SOURCE_CARACTERE_H