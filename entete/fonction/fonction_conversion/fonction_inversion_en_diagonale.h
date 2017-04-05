#ifndef FONCTION_inversion_EN_DIAGONALE_H
#define FONCTION_inversion_EN_DIAGONALE_H

/** \file fonction_inversion_en_diagonale.h
 * \brief Fichier de déclaration de la classe fonction_inversion_en_diagonale.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_inversion_en_diagonale
 * \brief Classe décrivant une fonction réalisant suivant une diagonale l'inversion des caractères ou des mots
 * (différent de la transposition qui ne garantit pas de garder le même nombre de lignes).
 * \author Sébastien Angibaud
 */
class fonction_inversion_en_diagonale : public base_fonction
{
    public:
        fonction_inversion_en_diagonale(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief Les choix des éléments à traiter (les mots ou les caractères). */
        liste_choix m_choix_elements;

        /** \brief Les choix de l'orientation de l'écriture (de haut en bas ou de bas en haut). */
        liste_choix m_choix_orientation;
};

#endif // FONCTION_inversion_EN_DIAGONALE_H
