#ifndef FONCTION_SORTIE_FREQUENCE_H
#define FONCTION_SORTIE_FREQUENCE_H

/** \file fonction_sortie_frequence.h
 * \brief Fichier de déclaration de la classe fonction_sortie_frequence.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"
#include "entete/fonction/fonction_sortie/frequence.h"

#include <list>

/**
 * \class fonction_sortie_frequence
 * \brief Classe décrivant une fonction de sortie affichant la fréquence des éléments.
 * \author Sébastien Angibaud
 */
class fonction_sortie_frequence : public fonction_base_sortie
{
        Q_OBJECT

    public:
        /** \brief Type représentant un ensemble de fréquence d'un texte. */
        typedef std::vector<frequence> type_frequences_texte;

        /** \brief Type représentant un ensemble de fréquence de textes. */
        typedef std::list<type_frequences_texte> type_frequences_textes;

    public:
        fonction_sortie_frequence(fonctions_conteneur * conteneur);
        ~fonction_sortie_frequence();

        base_fonction_widget *generer_fonction_widget();
        QString get_valeur_courte() const;

        textes & get_frequences_textes();

    protected:
        void executer_sortie_specifique( compilateur & compil, const textes & textes_in, textes & textes_out );

    private:
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
       /** \brief Les fréquences. */
       type_frequences_textes m_frequences;

       /** \brief Les fréquences sous forme de textes. */
       textes m_frequences_textes;
};

#endif // FONCTION_SORTIE_FREQUENCE_H
