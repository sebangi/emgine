/**
 * \file fonction_lecture_braille.cpp
 * \brief Fichier d'implémentation de la classe fonction_lecture_braille.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_lecture_braille.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>


fonction_lecture_braille::type_braille_conversion fonction_lecture_braille::s_braille_conversion =
{
    { "100000", "A" },
    { "110000", "B" },
    { "100100", "C" },
    { "100110", "D" },
    { "100010", "E" },
    { "110100", "F" },
    { "110110", "G" },
    { "110010", "H" },
    { "010100", "I" },
    { "010110", "J" },
    { "101000", "K" },
    { "111000", "L" },
    { "101100", "M" },
    { "101110", "N" },
    { "101010", "O" },
    { "111100", "P" },
    { "111110", "Q" },
    { "111010", "R" },
    { "011100", "S" },
    { "011110", "T" },
    { "101001", "U" },
    { "111001", "V" },
    { "010111", "W" },
    { "101101", "X" },
    { "101111", "Y" },
    { "101011", "Z" },
    { "001111", "0" },
    { "100001", "1" },
    { "110001", "2" },
    { "100101", "3" },
    { "100111", "4" },
    { "100011", "5" },
    { "110101", "6" },
    { "110111", "7" },
    { "110011", "8" },
    { "010101", "9" },
    { "010000", "," },
    { "000000", " " },
    { "010011", "." },
    { "010001", "?" }
};

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_lecture_braille.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_lecture_braille::fonction_lecture_braille( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_lecture_braille);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_CARACTERES,
                       new base_parametre( this,
                                           "Caractère plein",
                                           "Le caractère plein à considérer.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_lecture_braille::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la lettre d'un élément en braille donné.
 * \param type_element_braille e L'élément braille à considérer.
 * \return La lettre correspondante.
 */
QString fonction_lecture_braille::calcul_lettre(const type_element_braille & e) const
{
    type_braille_conversion::iterator it = s_braille_conversion.find( e );

    if ( it != s_braille_conversion.end() )
        return it->second;
    else
        return "*";
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_lecture_braille::get_valeur_courte() const
{
    return "[lecture_braille]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_lecture_braille::initialisation_par_defaut()
{
    m_parametres[PARAM_CARACTERES]->set_texte_par_defaut("#");
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_lecture_braille::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_CARACTERES, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>lecture_braille</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_lecture_braille::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    QString caractere_plein = m_map_IPL[PARAM_CARACTERES].it_caractere_courant->to_string();
    textes t_in = textes(textes_in);

    for ( textes::iterator it_t = t_in.begin(); it_t != t_in.end(); ++it_t )
    {
        it_t->fusionner(false, true, false);

        if ( it_t->est_multiple(2,3) )
        {
            texte t( it_t->get_configuration(), it_t->get_separateur_ligne() );
            for ( texte::const_iterator it_l1 = it_t->begin(); it_l1 !=  it_t->end(); it_l1 = it_l1 + 3 )
            {
                texte::const_iterator it_l2 = it_l1 + 1;
                texte::const_iterator it_l3 = it_l1 + 2;

                ligne l;
                l.set_separateur_mot( it_l1->get_separateur_mot() );
                type_element_braille element_braille;

                ligne::const_iterator it_m1 = it_l1->begin();
                ligne::const_iterator it_m2 = it_l2->begin();
                ligne::const_iterator it_m3 = it_l3->begin();
                mot m;
                m.set_separateur_caractere( it_m1->get_separateur_caractere() );

                mot::const_iterator it_c1 = it_m1->begin();
                mot::const_iterator it_c2 = it_m2->begin();
                mot::const_iterator it_c3 = it_m3->begin();

                for ( ; it_c1 != it_m1->end(); ++it_c1, ++it_c2, ++it_c3 )
                {
                    element_braille = "";
                    element_braille += (int)(it_c1->to_string() == caractere_plein) + '0';
                    element_braille += (int)(it_c2->to_string() == caractere_plein) + '0';
                    element_braille += (int)(it_c3->to_string() == caractere_plein) + '0';
                    ++it_c1;
                    ++it_c2;
                    ++it_c3;
                    element_braille += (int)(it_c1->to_string() == caractere_plein) + '0';
                    element_braille += (int)(it_c2->to_string() == caractere_plein) + '0';
                    element_braille += (int)(it_c3->to_string() == caractere_plein) + '0';

                    base_element elem( calcul_lettre(element_braille) );
                    if ( ! elem.est_vide() )
                        m.push_back(elem);
                }

                if ( ! m.empty() )
                {
                    l.ajouter_mot(m);
                    t.ajouter_ligne(l);
                }
            }

            textes_out.ajouter_texte(compil.get_configuration(), t);
        }
        else
            compil.get_vue_logs()->ajouter_log
                    ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                       "Un texte n'a pas été lu en braille. Sa taille n'est pas un multiple de 2 sur 3.") );
    }
}
