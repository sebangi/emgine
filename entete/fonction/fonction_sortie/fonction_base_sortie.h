#ifndef FONCTION_BASE_SORTIE_H
#define FONCTION_BASE_SORTIE_H

/** \file fonction_base_sortie.h
 * \brief Fichier de déclaration de la classe fonction_base_sortie.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class textes;

/**
 * \class fonction_base_sortie
 * \brief Classe commune à toutes les fonctions de type sortie.
 * \author Sébastien Angibaud
 */
class fonction_base_sortie : public base_fonction
{
        Q_OBJECT

    public:
        fonction_base_sortie(fonctions_conteneur * conteneur);
        ~fonction_base_sortie();

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        textes & get_textes();
        void set_textes(const textes &textes);

        textes & get_textes_a_afficher();

    signals:
        /** --------------------------------------------------------------------------------------
         * \brief Signal informant d'une modification du texte.
         */
        void signal_fbs_textes_modifie();

    protected:
        /**
         * \brief Méthode virtuelle pure qui exécute la fonction de sortie.
         * \param compil Le compilateur utilisé.
         * \param textes_in Le texte source en entrée.
         * \param textes_out Le texte de sortie généré.
        */
        virtual void executer_sortie_specifique( compilateur & compil, textes & textes_in, textes & textes_out ) = 0;

    protected:
        /** \brief Les textes de sortie. */
        textes m_textes;

        /** \brief Les textes à afficher. */
        textes m_textes_a_afficher;
};

#endif // FONCTION_BASE_SORTIE_H
