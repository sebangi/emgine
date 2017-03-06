#ifndef FONCTION_SORTIE_FREQUENCE_H
#define FONCTION_SORTIE_FREQUENCE_H

/** \file fonction_sortie_frequence.h
 * \brief Fichier de déclaration de la classe fonction_sortie_frequence.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"

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
        fonction_sortie_frequence(fonctions_conteneur * conteneur);
        ~fonction_sortie_frequence();

        base_fonction_widget *generer_fonction_widget();
        QString get_valeur_courte() const;

    protected:
        void executer_sortie_specifique( compilateur & compil, textes & textes_in, textes & textes_out );

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_SORTIE_FREQUENCE_H
