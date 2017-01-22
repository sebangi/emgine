#ifndef FONCTION_SORTIE_TEXTE_H
#define FONCTION_SORTIE_TEXTE_H

#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"

class fonction_sortie_texte : public fonction_base_sortie
{
        Q_OBJECT

    public:
        fonction_sortie_texte(fonctions_conteneur * conteneur);
        ~fonction_sortie_texte();

        base_fonction_widget *generer_fonction_widget();

        void executer( compilateur & compil, const textes & textes_in, textes & textes_out );
        QString get_aide() const;
        QString get_valeur_courte() const;

        textes get_textes() const;

    signals:
        void signal_fst_textes_modifie();

    private:
        bool est_valide(logs_compilation_widget * vue_logs) const;

    private:
        textes m_textes;
};

#endif // FONCTION_SORTIE_TEXTE_H
