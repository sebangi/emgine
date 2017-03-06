#ifndef FONCTION_ANALYSE_LIGNE_H
#define FONCTION_ANALYSE_LIGNE_H

/** \file fonction_sortie_analyse_ligne.h
 * \brief Fichier de déclaration de la classe fonction_sortie_analyse_ligne.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"

#include <list>

/**
 * \class fonction_sortie_analyse_ligne
 * \brief Classe décrivant une fonction de sortie affichant l'analyse de chaque ligne.
 * \author Sébastien Angibaud
 */
class fonction_sortie_analyse_ligne : public fonction_base_sortie
{
        Q_OBJECT

    public:
        fonction_sortie_analyse_ligne(fonctions_conteneur * conteneur);
        ~fonction_sortie_analyse_ligne();

        base_fonction_widget *generer_fonction_widget();
        QString get_valeur_courte() const;

    protected:
        void executer_sortie_specifique( compilateur & compil, textes & textes_in, textes & textes_out );

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_ANALYSE_LIGNE_H
