#ifndef FONCTION_SORTIE_INDICE_COINCIDENCE_H
#define FONCTION_SORTIE_INDICE_COINCIDENCE_H

/** \file fonction_sortie_indice_coincidence.h
 * \brief Fichier de déclaration de la classe fonction_sortie_indice_coincidence.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"

/**
 * \class fonction_sortie_indice_coincidence
 * \brief Classe décrivant une fonction de sortie affichant l'indice de coincidence.
 * \author Sébastien Angibaud
 */
class fonction_sortie_indice_coincidence : public fonction_base_sortie
{
        Q_OBJECT

    public:
        fonction_sortie_indice_coincidence(fonctions_conteneur * conteneur);
        ~fonction_sortie_indice_coincidence();

        base_fonction_widget *generer_fonction_widget();
        QString get_valeur_courte() const;

        textes & get_indices_textes();

    protected:
        void executer_sortie_specifique( compilateur & compil, textes & textes_in, textes & textes_out );

    private:
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief Les indices de coincidence sous forme de textes. */
        textes m_indices_textes;
};

#endif // FONCTION_SORTIE_INDICE_COINCIDENCE_H
