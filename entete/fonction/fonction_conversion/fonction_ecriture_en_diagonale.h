#ifndef FONCTION_ECRITURE_EN_DIAGONALE_H
#define FONCTION_ECRITURE_EN_DIAGONALE_H

/** \file fonction_ecriture_en_diagonale.h
 * \brief Fichier de déclaration de la classe fonction_ecriture_en_diagonale.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_ecriture_en_diagonale
 * \brief Classe décrivant une fonction réalisant l'écriture en diagonale des caractères ou des mots.
 * \author Sébastien Angibaud
 */
class fonction_ecriture_en_diagonale : public base_fonction
{
    public:
        fonction_ecriture_en_diagonale(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_ECRITURE_EN_DIAGONALE_H
