#include "entete/fonction/fonction_source/fonction_source_choix.h"

#include "entete/fonction_widget/fonction_source_widget/fonction_source_choix_widget.h"
#include "entete/compilation/compilateur.h"
#include "entete/parametre/parametre_choix.h"

#include <iostream>

fonction_source_choix::fonction_source_choix( fonctions_conteneur * conteneur, const QStringList & selection )
    : fonction_base_source(conteneur, "Choix"), m_selection(selection), m_sur_une_seule_ligne(false),
      m_multiple_selection(false)
{
    set_id(f_source_choix);
    augmenter_max_niveau_visibilite(1);

    if ( conteneur != NULL )
        if ( conteneur->est_parametre() )
            if ( ((base_parametre *)conteneur)->get_type() == TYPE_PARAM_CHOIX )
            {
                m_multiple_selection = ((parametre_choix *)conteneur)->multiple_selection();
                m_choix = ((parametre_choix *)conteneur)->get_choix();
            }
}

fonction_source_choix::~fonction_source_choix()
{

}

base_fonction_widget *fonction_source_choix::generer_fonction_widget()
{
    return new fonction_source_choix_widget(this);
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_source_choix::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    texte t;

    if ( m_sur_une_seule_ligne )
    {
        ligne l;

        for ( QStringList::iterator it = m_selection.begin(); it != m_selection.end(); ++it )
        {
            mot m( *it );
            l.ajouter_mot(m);
        }

        t.ajouter_ligne(l);
    }
    else
    {
        for ( QStringList::iterator it = m_selection.begin(); it != m_selection.end(); ++it )
        {
            mot m( *it );
            ligne l;
            l.ajouter_mot(m);
            t.ajouter_ligne(l);
        }
    }

    textes_out.push_back(t);
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_source_choix::est_valide(logs_compilation_widget * vue_logs) const
{
    return true;
}

const QStringList & fonction_source_choix::get_choix() const
{
    return m_choix;
}

bool fonction_source_choix::get_multiple_selection() const
{
    return m_multiple_selection;
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_source_choix::get_aide() const
{
    return QString("Source de type choix");
}

QString fonction_source_choix::get_valeur_courte() const
{
    QString resultat;

    if ( ! m_selection.empty() )
    {
        QStringList::const_iterator it = m_selection.constBegin();
        resultat += *it;

        for ( ++it; it != m_selection.constEnd(); ++it )
            if ( m_sur_une_seule_ligne )
                resultat += " et " + *it;
            else
                resultat += "\n" + *it;
    }

    return resultat;
}

const QStringList& fonction_source_choix::get_selection() const
{
    return m_selection;
}

void fonction_source_choix::set_selection(const QStringList & selection)
{
    m_selection = selection;
}

QString fonction_source_choix::get_string_valeur() const
{
    QString resultat;

    if ( ! m_selection.empty() )
    {
        QStringList::const_iterator it = m_selection.constBegin();
        resultat += *it;

        for ( ++it; it != m_selection.constEnd(); ++it )
            if ( m_sur_une_seule_ligne )
                resultat += " " + *it;
            else
                resultat += "\n" + *it;
    }

    return resultat;
}

void fonction_source_choix::set_string_valeur(const QString &valeur)
{
    m_selection = valeur.split( "\n" );
}
