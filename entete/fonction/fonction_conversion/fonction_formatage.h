#ifndef FONCTION_FORMATAGE_H
#define FONCTION_FORMATAGE_H

/** \file fonction_formatage.h
 * \brief Fichier de déclaration de la classe fonction_formatage.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_formatage
 * \brief Classe décrivant une fonction réalisant le formatage du texte, i.e. mise en majuscule et retrait des accents.
 * \author Sébastien Angibaud
 */
class fonction_formatage : public base_fonction
{
    public:
        fonction_formatage(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_FORMATAGE_H
