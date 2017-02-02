#include "entete/fonction/fonction_source/fonction_source_permutation.h"

#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/compilation/compilateur.h"
#include "entete/element/type_element.h"
#include <iostream>

fonction_source_permutation::fonction_source_permutation(fonctions_conteneur * conteneur)
    : fonction_base_source(conteneur, "Générateur de permutations")
{
    set_id(f_source_generateur_permutation);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_ELEMENTS,
                       new base_parametre( this,
                                           "Éléments",
                                           "Les éléments utilisés pour générer les permutations.\nÉviter de dépasser 9 éléments car trop long.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_LIPL) );
}

fonction_source_permutation::~fonction_source_permutation()
{

}

void fonction_source_permutation::initialisation_par_defaut()
{
    initialisation_par_defaut("2 1 3");
}

void fonction_source_permutation::initialisation_par_defaut(QString elements)
{
    m_parametres[PARAM_ELEMENTS]->set_texte_par_defaut(elements);
}

base_fonction_widget *fonction_source_permutation::generer_fonction_widget()
{
    return new base_fonction_widget(this);
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_source_permutation::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    algo_LIPL_iteration_premier_mot_par_ligne
        ( PARAM_ELEMENTS, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction spécifique : fonction_source_permutation.
*/
void fonction_source_permutation::execution_specifique( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    texte t("", "\n" );

    ligne l(* m_map_LIPL[PARAM_ELEMENTS].ligne_courante);
    std::sort(l.begin(), l.end());

    do
    {
        t.ajouter_ligne(l);
    } while ( std::next_permutation( l.begin(), l.end() ) );

    textes_out.ajouter_texte(compil.get_configuration(), t);
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_source_permutation::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

QString fonction_source_permutation::get_valeur_courte() const
{
    return "généré lors de l'exécution";
}

QString fonction_source_permutation::get_string_valeur() const
{
    return "";
}

void fonction_source_permutation::set_string_valeur(const QString &valeur)
{
    // rien à faire
}
