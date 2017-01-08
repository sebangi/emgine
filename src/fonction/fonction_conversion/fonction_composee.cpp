#include "fonction/fonction_conversion/fonction_composee.h"

#include "old_texte.h"

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_composee.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_composee::fonction_composee(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Destructeur.
*/
fonction_composee::~fonction_composee()
{
    std::list<const base_fonction*>::iterator it;

    for ( it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        delete *it;
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Texte source.
 \param resultat Texte
 \param parametre Le texte parametre.
*/
void fonction_composee::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    std::list<const base_fonction*>::const_iterator it;
    old_texte t_source(source);
    resultat.effacer();

    for ( it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
    {
        //(*it)->appliquer(t_source, resultat, parametre);
        t_source = resultat;
    }
}


/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_composee::get_info_bulle() const
{
    return QString("Fonction composée\nParamètre : \n\tun paramètre commun à chaque fonction");
}

/*! --------------------------------------------------------------------------------------
 \brief Ajoute une fonction donnée à la liste des fonctions.
 \param f La fonction à ajouter.
*/
void fonction_composee::ajouter_fonction(const base_fonction *f)
{
    m_fonctions.push_back(f);
}
