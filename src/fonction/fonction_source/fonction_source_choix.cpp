#include "entete/fonction/fonction_source/fonction_source_choix.h"

#include "entete/fonction_widget/fonction_source_widget/fonction_source_choix_widget.h"
#include "entete/compilation/compilateur.h"

fonction_source_choix::fonction_source_choix( fonctions_conteneur * conteneur, const QStringList & selection )
    : fonction_base_source(conteneur, "Choix"), m_selection(selection)
{
    set_id(f_source_choix);
    augmenter_max_niveau_visibilite(1);
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
    mot m("Additif");

    /*
    for ( int i = 0 ; i != m_valeur.size(); ++i )
    {
        base_element e(m_valeur[i]);
        m.push_back(e);
    }
    */

    ligne l;
    l.ajouter_mot(m);
    texte t;
    t.ajouter_ligne(l);

    textes_out.push_back(t);
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_source_choix::est_valide(logs_compilation_widget * vue_logs) const
{
    return true;
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
            resultat += " " + *it;
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
    return get_valeur_courte();
}

void fonction_source_choix::set_string_valeur(const QString &valeur)
{
    m_selection = valeur.split( " " );
}
