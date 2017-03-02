#ifndef FONCTION_CESAR_H
#define FONCTION_CESAR_H

/** \file fonction_cesar.h
 * \brief Fichier de déclaration de la classe fonction_cesar.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

#include <map>
#include <vector>

class base_element;

/**
 * \class fonction_cesar
 * \brief Classe décrivant une fonction permettant de réaliser un <b>décalage de césar</b>.
 *  - Le décalage peut être additif ou soustractif ou une séquence de ce choix.
 *  - Le décalage se fait suivant un entier ou une séquence d'entier.
 *  - Chaque mot de la ligne spécifie un alphabet.
 * \author Sébastien Angibaud
 */
class fonction_cesar : public base_fonction
{
    public:
        fonction_cesar(fonctions_conteneur * conteneur);

        void initialisation_par_defaut();
        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
        void construire_alphabet();
        void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        void callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );

    private:
        /** \brief Tableau associant à chaque élément sa position dans l'alphabet. */
        std::map<base_element, std::pair<int, int>> m_position_alphabet;

        /** \brief L'ensemble des alphabets. */
        std::vector< std::vector<base_element> > m_alphabets;
};

#endif // FONCTION_CESAR_H
