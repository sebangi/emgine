#ifndef FONCTION_SOURCE_ENTIER_H
#define FONCTION_SOURCE_ENTIER_H

#include "fonction/fonction_source/fonction_base_source.h"

class fonction_source_entier : public fonction_base_source
{
    public:
        fonction_source_entier(fonctions_conteneur * conteneur, int valeur = 0);
        ~fonction_source_entier();

        QString get_aide() const;
        QString get_valeur_courte() const;
        void executer( compilateur & compil, const texte & texte_in, texte & texte_out );

        int get_valeur() const;
        void set_valeur(int valeur);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);

    private:
        bool est_valide() const;

    private:
        int m_valeur;
};

#endif // FONCTION_SOURCE_ENTIER_H
