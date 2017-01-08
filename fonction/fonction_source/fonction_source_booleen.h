#ifndef FONCTION_SOURCE_BOOLEEN_H
#define FONCTION_SOURCE_BOOLEEN_H

#include "fonction/fonction_source/fonction_base_source.h"

class base_fonction_widget;

class fonction_source_booleen : public fonction_base_source
{
    public:
        fonction_source_booleen(fonctions_conteneur * conteneur, bool valeur = false);
        ~fonction_source_booleen();

        base_fonction_widget *generer_fonction_widget();
        void executer( compilateur & compil, const texte & texte_in, texte & texte_out );
         QString get_aide() const;
        QString get_valeur_courte() const;

        bool get_valeur() const;
        void set_valeur(bool valeur);
        QString get_string_valeur() const;
        void set_string_valeur(const QString & valeur);

    private:
        bool est_valide() const;

    private:
        bool m_valeur;
};

#endif // FONCTION_SOURCE_BOOLEEN_H
