#include "entete/fonction/fonction_source/fonction_source_texte.h"

#include "entete/fonction_widget/fonction_source_widget/fonction_source_texte_widget.h"
#include "entete/compilation/compilateur.h"
#include "entete/element/type_element.h"
#include <iostream>

fonction_source_texte::fonction_source_texte(fonctions_conteneur * conteneur, QString texte)
    : fonction_base_source(conteneur, "Texte"), m_texte(texte)
{
    set_id(f_source_texte);
    augmenter_max_niveau_visibilite(2);
    set_niveau_visibilite(2);

    ajouter_parametre( PARAM_CARACTERE_SEPARATEUR,
                       new base_parametre( this,
                                           "Séparateur d'élément",
                                           "Les séparateurs d'éléments.",
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_PMIPL) );

    ajouter_parametre( PARAM_MOT_SEPARATEUR,
                       new base_parametre( this,
                                           "Séparateur de mot",
                                           "Les séparateurs de mot.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_PMIPL) );

    ajouter_parametre( PARAM_LIGNE_SEPARATEUR,
                       new base_parametre( this,
                                           "Séparateur de ligne",
                                           "Les séparateurs de ligne.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_PMIPL) );
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
void fonction_source_texte::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    algo_PMIPL_iteration_premier_mot_par_ligne
        ( PARAM_LIGNE_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/*! --------------------------------------------------------------------------------------
\brief Exécution de la fonction selon le parametre PARAM_LIGNE_SEPARATEUR.
*/
void fonction_source_texte::callback_param_1( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    algo_PMIPL_iteration_premier_mot_par_ligne
        ( PARAM_MOT_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/*! --------------------------------------------------------------------------------------
\brief Exécution de la fonction selon le parametre PARAM_MOT_SEPARATEUR.
*/
void fonction_source_texte::callback_param_2( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    algo_PMIPL_iteration_premier_mot_par_ligne
        ( PARAM_CARACTERE_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction spécifique : fonction_source_texte.
*/
void fonction_source_texte::execution_specifique( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    QString t_caractere = m_map_PMIPL[PARAM_CARACTERE_SEPARATEUR].mot_courant->to_string();
    QString t_mot = m_map_PMIPL[PARAM_MOT_SEPARATEUR].mot_courant->to_string();
    QString t_ligne = m_map_PMIPL[PARAM_LIGNE_SEPARATEUR].mot_courant->to_string();

    texte t("", t_ligne );
    QStringList lignes = m_texte.split( t_ligne );
    for ( QStringList::const_iterator it_l = lignes.constBegin(); it_l != lignes.constEnd(); ++it_l )
    {
        ligne l("", t_mot );
        QStringList mots = it_l->split( t_mot );
        for ( QStringList::const_iterator it_m = mots.constBegin(); it_m != mots.constEnd(); ++it_m )
        {
            mot m("", t_caractere );
            QStringList caracteres = it_m->split( t_caractere );
            for ( QStringList::const_iterator it_c = caracteres.constBegin(); it_c != caracteres.constEnd(); ++it_c )
            {
                if ( it_c->size() != 0 )
                {
                    base_element e(*it_c);
                    m.push_back(e);
                }
            }
            if ( ! m.empty() )
                l.ajouter_mot(m);
        }
        if ( ! l.empty() )
            t.ajouter_ligne(l);
    }
    textes_out.ajouter_texte(compil.get_configuration(), t);
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_source_texte::est_valide(logs_compilation_widget * vue_logs)
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
