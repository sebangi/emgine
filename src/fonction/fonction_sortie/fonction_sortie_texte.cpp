#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_texte_widget.h"
#include "entete/compilation/compilateur.h"
#include "entete/element/type_element.h"
#include "entete/element/texte.h"

#include <iostream>

fonction_sortie_texte::fonction_sortie_texte(fonctions_conteneur * conteneur)
    : fonction_base_sortie(conteneur,"Sortie texte")
{
    set_id(f_sortie_texte);
    augmenter_max_niveau_visibilite(1);
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
void fonction_sortie_texte::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    m_textes = textes_in;
    textes_out = textes_in;

    emit signal_fst_textes_modifie();
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_sortie_texte::est_valide(logs_compilation_widget * vue_logs)
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
    return m_textes.to_string_lisible();
}

textes & fonction_sortie_texte::get_textes()
{
    return m_textes;
}
