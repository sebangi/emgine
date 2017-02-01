#include "entete/fonction/fonction_source/fonction_source_booleen.h"

#include "entete/fonction_widget/fonction_source_widget/fonction_source_booleen_widget.h"
#include "entete/compilation/compilateur.h"
#include "entete/element/mot.h"

fonction_source_booleen::fonction_source_booleen(fonctions_conteneur * conteneur,  bool valeur )
    : fonction_base_source(conteneur, "Oui ou Non ?"), m_valeur(valeur)
{
    set_id(f_source_booleen);
    augmenter_max_niveau_visibilite(1);
}

fonction_source_booleen::~fonction_source_booleen()
{

}

base_fonction_widget *fonction_source_booleen::generer_fonction_widget()
{
    return new fonction_source_booleen_widget(this);
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_source_booleen::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_source_booleen::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    base_element e(m_valeur);
    mot m;
    m.push_back(e);
    ligne l;
    l.ajouter_mot(m);
    texte t;
    t.ajouter_ligne(l);

    textes_out.push_back(t);
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_source_booleen::get_aide() const
{
    return QString("Source de type Oui ou Non");
}

QString fonction_source_booleen::get_valeur_courte() const
{
    if ( m_valeur )
        return "oui";
    else
        return "non";
}

bool fonction_source_booleen::get_valeur() const
{
    return m_valeur;
}

void fonction_source_booleen::set_valeur(bool valeur)
{
    m_valeur = valeur;
}

QString fonction_source_booleen::get_string_valeur() const
{
    return QString::number(m_valeur);
}

void fonction_source_booleen::set_string_valeur(const QString &valeur)
{
    m_valeur = valeur != "0";
}
