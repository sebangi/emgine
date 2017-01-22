#include "entete/fonction/fonction_source/fonction_source_caractere.h"

#include "entete/fonction_widget/fonction_source_widget/fonction_source_caractere_widget.h"
#include "entete/compilation/compilateur.h"

fonction_source_caractere::fonction_source_caractere( fonctions_conteneur * conteneur, QString valeur )
    : fonction_base_source(conteneur, "Source caractère"), m_valeur(valeur)
{    
    set_id(f_source_caractere);
    augmenter_max_niveau_visibilite(1);
}

fonction_source_caractere::~fonction_source_caractere()
{

}

base_fonction_widget *fonction_source_caractere::generer_fonction_widget()
{
    return new fonction_source_caractere_widget(this);
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_source_caractere::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    mot m;

    for ( int i = 0 ; i != m_valeur.size(); ++i )
    {
        base_element e(m_valeur[i]);
        m.push_back(e);
    }

    ligne l;
    l.push_back(m);
    texte t;
    t.push_back(l);
    textes_out.push_back(t);
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_source_caractere::est_valide(logs_compilation_widget * vue_logs) const
{
    return true;
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_source_caractere::get_aide() const
{
    return QString("Source de type un caractère");
}

QString fonction_source_caractere::get_valeur_courte() const
{
    QString resultat;

    resultat += m_valeur;

    return resultat;
}

QString fonction_source_caractere::get_valeur() const
{
    return m_valeur;
}

void fonction_source_caractere::set_valeur(QString valeur)
{
    m_valeur = valeur;
}

QString fonction_source_caractere::get_string_valeur() const
{
    return m_valeur;
}

void fonction_source_caractere::set_string_valeur(const QString &valeur)
{
    m_valeur = valeur;
}
