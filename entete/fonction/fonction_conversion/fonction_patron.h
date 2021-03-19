#ifndef FONCTION_PATRON_H
#define FONCTION_PATRON_H

/** \file fonction_patron.h
 * \brief Fichier de déclaration de la classe fonction_patron.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_patron
 * \brief Classe décrivant une fonction filtrant selon un patron donné.
 * \author Sébastien Angibaud
 */
class fonction_patron : public base_fonction
{
    public:
        fonction_patron(fonctions_conteneur * conteneur);

        void initialisation_par_defaut();
        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_PATRON_H
