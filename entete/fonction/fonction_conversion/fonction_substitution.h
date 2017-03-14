#ifndef FONCTION_SUBSTITUTION_H
#define FONCTION_SUBSTITUTION_H

/** \file fonction_substitution.h
 * \brief Fichier de déclaration de la classe fonction_substitution.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class base_element;

/**
 * \class fonction_substitution
 * \brief Classe décrivant une fonction réalisant une substitution des caractères.
 * \author Sébastien Angibaud
 */
class fonction_substitution : public base_fonction
{
    private:
        typedef std::vector< base_element > type_vector_element;
        typedef std::map< base_element, type_vector_element> type_map_substitution;

    public:
        fonction_substitution(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);
        void construire_map_substitution();

    private:
        type_map_substitution m_substitution;
};

#endif // FONCTION_SUBSTITUTION_H
