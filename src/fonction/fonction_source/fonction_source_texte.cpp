#include "entete/fonction/fonction_source/fonction_source_texte.h"

#include "entete/fonction_widget/fonction_source_texte_widget.h"
#include "entete/compilation/compilateur.h"
#include "entete/element/type_element.h"
#include <iostream>

fonction_source_texte::fonction_source_texte(fonctions_conteneur * conteneur, QString texte)
    : fonction_base_source(conteneur, "Texte"), m_texte(texte)
{
    set_id(f_source_texte);
    augmenter_max_niveau_visibilite(2);

    ajouter_parametre( PARAM_CARACTERE_SEPARATEUR,
                       new base_parametre( this, "Séparateur d'élément", "Les séparateurs d'éléments.", false,
                                            type_element_caractere) );

    ajouter_parametre( PARAM_MOT_SEPARATEUR,
                       new base_parametre( this, "Séparateur de mot", "Les séparateurs de mot.", false,
                                            type_element_caractere) );

    ajouter_parametre( PARAM_LIGNE_SEPARATEUR,
                       new base_parametre( this, "Séparateur de ligne", "Les séparateurs de ligne.", false,
                                            type_element_caractere) );
}

fonction_source_texte::~fonction_source_texte()
{

}

void fonction_source_texte::initialisation_par_defaut()
{
    initialisation_par_defaut("", " ","\n");
}

void fonction_source_texte::initialisation_par_defaut(QString separ_caractere, QString separ_mot, QString separ_ligne )
{
    m_parametres[PARAM_CARACTERE_SEPARATEUR]->set_caractere_par_defaut(separ_caractere);
    m_parametres[PARAM_MOT_SEPARATEUR]->set_caractere_par_defaut(separ_mot);
    m_parametres[PARAM_LIGNE_SEPARATEUR]->set_caractere_par_defaut(separ_ligne);
}

base_fonction_widget *fonction_source_texte::generer_fonction_widget()
{
    return new fonction_source_texte_widget(this);
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_source_texte::executer( compilateur &compil, const texte & texte_in, texte & texte_out )
{
    const texte& t_caractere = get_texte_parametre(PARAM_CARACTERE_SEPARATEUR);
    const texte& t_mot = get_texte_parametre(PARAM_MOT_SEPARATEUR);
    const texte& t_ligne = get_texte_parametre(PARAM_LIGNE_SEPARATEUR);

    QStringList lignes = m_texte.split( t_ligne.to_string() );
    for ( QStringList::const_iterator it_l = lignes.constBegin(); it_l != lignes.constEnd(); ++it_l )
    {
        ligne l;
        QStringList mots = it_l->split( t_mot.to_string() );
        for ( QStringList::const_iterator it_m = mots.constBegin(); it_m != mots.constEnd(); ++it_m )
        {
            mot m;
            QStringList caracteres = it_m->split( t_caractere.to_string() );
            for ( QStringList::const_iterator it_c = caracteres.constBegin(); it_c != caracteres.constEnd(); ++it_c )
            {
                if ( it_c->size() != 0 )
                {
                    base_element e(*it_c);
                    m.push_back(e);
                }
            }
            if ( ! m.empty() )
                l.push_back(m);
        }
        if ( ! l.empty() )
            texte_out.push_back(l);
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_source_texte::est_valide() const
{
    return true;
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_source_texte::get_aide() const
{
    return QString("Source textuelle");
}

QString fonction_source_texte::get_valeur_courte() const
{
    return m_texte;
}

QString fonction_source_texte::get_valeur() const
{
    return m_texte;
}

void fonction_source_texte::set_valeur(QString texte)
{
    m_texte = texte;
}

QString fonction_source_texte::get_string_valeur() const
{
    return m_texte;
}

void fonction_source_texte::set_string_valeur(const QString &valeur)
{
    m_texte = valeur;
}
