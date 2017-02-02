#ifndef FONCTION_CESAR_H
#define FONCTION_CESAR_H

#include "entete/projet/base_fonction.h"
#include <map>
#include <vector>

class base_element;

/*!
 \brief Classe décrivant une fonction permettant de réaliser un décalage de césar.
 \author Sébastien Angibaud
*/
class fonction_cesar : public base_fonction
{
    public:
        fonction_cesar(fonctions_conteneur * conteneur);
        void initialisation_par_defaut();

        void executer( compilateur & compil, const textes & textes_in, textes & textes_out );

        QString get_valeur_courte() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
        void construire_alphabet();
        void callback_param_1( compilateur &compil, const textes & textes_in, textes & textes_out );
        void callback_param_2( compilateur &compil, const textes & textes_in, textes & textes_out );
        void execution_specifique( compilateur &compil, const textes & textes_in, textes & textes_out );

    private:
        std::map<base_element, std::pair<int, int>> m_position_alphabet;
        std::vector< std::vector<base_element> > m_alphabets;

        bool m_additif_courant;

        mot::const_iterator m_it_decalage_debut;
        mot::const_iterator m_it_decalage;
        mot::const_iterator m_it_decalage_fin;

        mot::const_iterator m_it_soustractif_debut;
        mot::const_iterator m_it_soustractif;
        mot::const_iterator m_it_soustractif_fin;

};

#endif // FONCTION_CESAR_H
