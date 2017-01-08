#include "fonction/fonction_conversion/fonction_substitution.h"

#include "old_texte.h"
#include <iostream>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_substitution.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_substitution::fonction_substitution(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Texte source.
 \param resultat Texte
 \param parametre Le texte parametre.
*/
void fonction_substitution::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    type_correspondances correspondances;

    calcul_correspondances(parametre, correspondances);
    resultat.effacer();

    old_texte::element_iterator it;
    for ( it = source.begin(); it != source.end(); ++it )
    {
        type_correspondances::iterator it_c = correspondances.find( *it );

        if ( it_c != correspondances.end() )
        {
            if ( it_c->second.size() == 1  )
                resultat.ajout_element( *(it_c->second.begin()) );
            else
            {
                resultat.ajout_element( element('(') );

                std::set< element >::iterator it_l;
                for ( it_l = it_c->second.begin(); it_l != it_c->second.end();  )
                {
                    resultat.ajout_element( *it_l );

                    ++it_l;
                    if ( it_l != it_c->second.end() )
                        resultat.ajout_element( element('|') );
                }

                resultat.ajout_element( element(')') );
            }
        }
        else
            resultat.ajout_element( *it );
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_substitution::get_info_bulle() const
{
    return QString("Substitution d'éléments dans un texte\nParamètre : \n\tles éléments de la première ligne sont substitués par ceux de la seconde");
}

/*! --------------------------------------------------------------------------------------
 \brief Charge les correspondances à partir d'un texte.
*/
void fonction_substitution::calcul_correspondances(const old_texte &source, type_correspondances &correspondances) const
{
    std::vector< element > tab;

    old_texte::element_iterator it;
    bool continuer = true;

    // lecture de la première ligne
    for ( it = source.begin(); continuer && ( it != source.end() ); ++it )
    {
        if ( it->get_type() == element::retour_ligne )
            continuer = false;
        else
            tab.push_back(*it);
    }

    // lecture de la deuxième ligne
    continuer = true;
    unsigned int i = 0;

    for ( ; ( i < tab.size() ) &&  continuer && ( it != source.end() ); ++it, ++i )
    {
        if ( it->get_type() == element::retour_ligne )
            continuer = false;
        else
        {
            type_correspondances::iterator it_c = correspondances.find( tab[i] );
            if ( it_c == correspondances.end() )
            {
                std::set<element> set;
                set.insert(*it);
                correspondances[tab[i]] = set;
            }
            else
                correspondances[tab[i]].insert(*it);
        }
    }
}
