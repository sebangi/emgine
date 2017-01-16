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

        void executer( compilateur & compil, const texte & texte_in, texte & texte_out );

        QString get_aide() const;
        QString get_valeur_courte() const;

    private:
        bool est_valide(logs_compilation_widget * vue_logs) const;
        void construire_alphabet(compilateur &compil);

        void decalage_suivant();
        void soustractif_suivant();
        void executer_selon_soustractif( compilateur & compil, const texte & texte_in, texte & texte_out );
        void executer_selon_decalage( compilateur & compil, const texte & texte_in, texte & texte_out );
        void executer_cesar( compilateur & compil, const texte & texte_in, texte & texte_out );

    private:
        std::map<base_element, int> m_position_alphabet;
        std::vector<base_element> m_alphabet;

        mot::const_iterator m_it_decalage_debut;
        mot::const_iterator m_it_decalage;
        mot::const_iterator m_it_decalage_fin;

        mot::const_iterator m_it_soustractif_debut;
        mot::const_iterator m_it_soustractif;
        mot::const_iterator m_it_soustractif_fin;

};

#endif // FONCTION_CESAR_H
