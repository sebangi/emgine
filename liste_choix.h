#ifndef LISTE_CHOIX_H
#define LISTE_CHOIX_H

#include "choix.h"
#include <vector>

class liste_choix
{
public:
    /*!
     \brief Type décrivant un tableau de fonctions choisies.
    */
    typedef std::vector< choix > type_tableau_choix;

public:
    liste_choix();

    static void appliquer(const old_texte & source, old_texte & resultat);
    static unsigned int get_nb_choix();
    static const choix& get_choix(unsigned int index);
    static bool supprimer(unsigned int index);
    static bool monter(unsigned int index);
    static bool descendre(unsigned int index);
    static void clear();
    static void ajout_choix(const choix& c);

private:
    /*!
     \brief Tableau des fonctions choisies.
    */
    static type_tableau_choix s_choix;
};

#endif // LISTE_CHOIX_H
