#ifndef FONCTION_SORTIE_TEXTE_H
#define FONCTION_SORTIE_TEXTE_H

/** \file fonction_sortie_texte.h
 * \brief Fichier de déclaration de la classe fonction_sortie_texte.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"

/**
 * \class fonction_sortie_texte
 * \brief Classe décrivant une fonction de sortie affichant simplement les textes.
 * \author Sébastien Angibaud
 */
class fonction_sortie_texte : public fonction_base_sortie
{
        Q_OBJECT

    public:
        fonction_sortie_texte(fonctions_conteneur * conteneur);
        ~fonction_sortie_texte();

        base_fonction_widget *generer_fonction_widget();
        void executer( compilateur & compil, const textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        textes & get_textes();
        void set_textes(const textes &textes);

    signals:
        /** --------------------------------------------------------------------------------------
         * \brief Signal informant d'une modification du texte.
         */
        void signal_fst_textes_modifie();

    private:
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief Les textes de sortie. */
        textes m_textes;
};

#endif // FONCTION_SORTIE_TEXTE_H
