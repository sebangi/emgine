#ifndef FONCTION_SORTIE_TEXTE_H
#define FONCTION_SORTIE_TEXTE_H

#ifndef FONCTION_sortie_TEXTE_H
#define FONCTION_sortie_TEXTE_H

#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"

class base_fonction_widget;

class fonction_sortie_texte : public fonction_base_sortie
{
        Q_OBJECT

    public:
        fonction_sortie_texte(fonctions_conteneur * conteneur);
        ~fonction_sortie_texte();

        base_fonction_widget *generer_fonction_widget();

        void executer( compilateur & compil, const texte & texte_in, texte & texte_out );
        QString get_aide() const;
        QString get_valeur_courte() const;

        texte get_texte() const;

    signals:
        void signal_fst_texte_modifie();

    private:
        bool est_valide() const;

    private:
        texte m_texte;
};

#endif // FONCTION_sortie_TEXTE_H


#endif // FONCTION_SORTIE_TEXTE_H
