#ifndef FONCTION_ORDONNANCEMENT_H
#define FONCTION_ORDONNANCEMENT_H

/** \file fonction_ordonnancement.h
 * \brief Fichier de déclaration de la classe fonction_ordonnancement.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;
class liste_choix;

/**
 * \class fonction_ordonnancement
 * \brief Classe décrivant une fonction réalisant un ordonnancement des caractères ou des mots.
 * \author Sébastien Angibaud
 */
class fonction_ordonnancement : public base_fonction
{
    public:
        fonction_ordonnancement(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);

    private:
        /** \brief Les choix des éléments tournables (les mot ou les caractères). */
        liste_choix m_choix_elements;
};

#endif // FONCTION_ORDONNANCEMENT_H
