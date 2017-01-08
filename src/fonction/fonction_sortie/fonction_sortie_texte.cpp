#include "fonction/fonction_sortie/fonction_sortie_texte.h"

#include "fonction_widget/fonction_sortie_texte_widget.h"
#include "compilation/compilateur.h"
#include "element/type_element.h"
#include "element/texte.h"

#include <iostream>

fonction_sortie_texte::fonction_sortie_texte(fonctions_conteneur * conteneur)
    : fonction_base_sortie(conteneur,"Sortie texte")
{
    set_id(f_sortie_texte);
}

fonction_sortie_texte::~fonction_sortie_texte()
{

}

base_fonction_widget *fonction_sortie_texte::generer_fonction_widget()
{
    return new fonction_sortie_texte_widget(this);
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_sortie_texte::executer( compilateur &compil, const texte & texte_in, texte & texte_out )
{
    m_texte = texte_in;
    texte_out = texte_in;

    for ( type_set_widgets::iterator it = m_widgets.begin(); it != m_widgets.end(); ++it )
        ((fonction_sortie_texte_widget*)(*it))->set_texte( texte_in );
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_sortie_texte::est_valide() const
{
    return true;
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_sortie_texte::get_aide() const
{
    return QString("sortie textuelle");
}

QString fonction_sortie_texte::get_valeur_courte() const
{
    return m_texte.to_string_lisible();
}

texte fonction_sortie_texte::get_texte() const
{
    return m_texte;
}
