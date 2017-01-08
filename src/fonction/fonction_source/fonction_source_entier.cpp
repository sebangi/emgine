#include "fonction/fonction_source/fonction_source_entier.h"
#include "compilation/compilateur.h"

fonction_source_entier::fonction_source_entier(fonctions_conteneur * conteneur, int valeur)
    : fonction_base_source(conteneur, "Source de type entier"), m_valeur(valeur)
{    
    set_id(f_source_entier);
}

fonction_source_entier::~fonction_source_entier()
{

}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_source_entier::executer( compilateur &compil, const texte & texte_in, texte & texte_out )
{
    base_element e(m_valeur);
    mot m;
    m.push_back(e);
    ligne l;
    l.push_back(m);
    texte_out.push_back(l);
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_source_entier::get_aide() const
{
    return QString("Source de type entier");
}

QString fonction_source_entier::get_valeur_courte() const
{
    return QString::number(m_valeur);
}

int fonction_source_entier::get_valeur() const
{
    return m_valeur;
}

void fonction_source_entier::set_valeur(int valeur)
{
    m_valeur = valeur;
}

QString fonction_source_entier::get_string_valeur() const
{
    return QString::number(m_valeur);
}

void fonction_source_entier::set_string_valeur(const QString &valeur)
{
    m_valeur = valeur.toInt();
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_source_entier::est_valide() const
{
    return true;
}
