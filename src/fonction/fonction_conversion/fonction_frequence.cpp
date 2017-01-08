#include "fonction/fonction_conversion/fonction_frequence.h"

#include <sstream>

fonction_frequence::fonction_frequence(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Texte source.
 \param resultat Texte
 \param parametre Le texte parametre.
*/
void fonction_frequence::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    resultat.effacer();

    type_map_frequence frequences;
    type_map_frequence::const_iterator it_f;
    old_texte::element_iterator it;
    unsigned int nb_lettres = 0;
    unsigned int nb_lettres_differentes = 0;
    unsigned int nb_lignes = 0;
    unsigned int nb_mots = 0;
    bool nouvelle_ligne = true;
    bool nouveau_mot = true;

    // calcul des fréquences
    for ( it = source.begin(); it != source.end(); ++it )
    {
        if ( ! it->est_separateur() )
        {
            if ( nouvelle_ligne )
            {
                nouvelle_ligne = false;
                ++nb_lignes;
            }

            if ( nouveau_mot )
            {
                nouveau_mot = false;
                ++nb_mots;
            }

            std::string s = it->to_string();
            ++nb_lettres;

            it_f = frequences.find(s);
            if ( it_f == frequences.end() )
            {
                frequences[s] = 1;
                ++nb_lettres_differentes;
            }
            else
                frequences[s] = frequences[s] + 1;
        }
        else
        {
            if ( it->get_type() == element::retour_ligne )
                nouvelle_ligne = true;
            nouveau_mot = true;
        }
    }

    // affichage
    std::string str;
    std::stringstream convert1;
    convert1 << "nombre de lettres : " << nb_lettres << " " << std::endl
             << "nombre de lettres differentes : " << nb_lettres_differentes << " " << std::endl
             << "nombre de mots : " << nb_mots << " " << std::endl
             << "nombre de lignes : " << nb_lignes << " " << std::endl;
    str = convert1.str();

    for ( it_f = frequences.begin(); it_f != frequences.end(); ++it_f )
    {
        std::stringstream convert2;
        convert2 << it_f->first << " : " << it_f->second << " " << std::endl;
        str = str + convert2.str();
    }

    resultat = old_texte(str);
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_frequence::get_info_bulle() const
{
    return QString("Calcule les fréquences de lettres\nParamètre : aucun");
}
