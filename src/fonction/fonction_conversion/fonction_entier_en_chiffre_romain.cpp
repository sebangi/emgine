/**
 * \file fonction_entier_en_chiffre_romain.cpp
 * \brief Fichier d'implémentation de la classe fonction_entier_en_chiffre_romain.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_entier_en_chiffre_romain.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_entier_en_chiffre_romain.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_entier_en_chiffre_romain::fonction_entier_en_chiffre_romain( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_entier_en_chiffre_romain);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_entier_en_chiffre_romain::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_entier_en_chiffre_romain::get_valeur_courte() const
{
    return base_fonction::tr("[Entier en chiffre romain]");
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_entier_en_chiffre_romain::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    int I = 1, IV = 4, V = 5, IX = 9;
    int X = 10, XL = 40, L = 50, XC = 90;
    int C = 100, CD = 400, D = 500, CM = 900;
    int M = 1000;

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t ) {
        texte t( it_t->get_configuration(), it_t->get_separateur_ligne() );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l ) {
            ligne l;
            l.set_separateur_mot( it_l->get_separateur_mot() );
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            {
                mot m;
                m.set_separateur_caractere( it_m->get_separateur_caractere() );
                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
                {
                    if ( it_c->est_entier() )
                    {
                        int valeur = it_c->to_string().toInt();

                        while(valeur - M >= 0) {
                            valeur -= M;
                            m.push_back( base_element("M", false) );
                        }
                        while(valeur - CM >= 0) {
                            valeur -= CM;
                            m.push_back( base_element("C", false) );
                            m.push_back( base_element("M", false) );
                        }
                        while(valeur - D >= 0) {
                            valeur -= D;
                            m.push_back( base_element("D", false) );
                        }
                        while(valeur - CD >= 0) {
                            valeur -= CD;
                            m.push_back( base_element("C", false) );
                            m.push_back( base_element("D", false) );
                        }
                        while(valeur - C >= 0) {
                            valeur -= C;
                            m.push_back( base_element("C", false) );
                        }
                        while(valeur - XC >= 0) {
                            valeur -= XC;
                            m.push_back( base_element("X", false) );
                            m.push_back( base_element("C", false) );
                        }
                        while(valeur - L >= 0) {
                            valeur -= L;
                            m.push_back( base_element("L", false) );
                        }
                        while(valeur - XL >= 0) {
                            valeur -= XL;
                            m.push_back( base_element("X", false) );
                            m.push_back( base_element("L", false) );
                        }
                        while(valeur - X >= 0) {
                            valeur -= X;
                            m.push_back( base_element("X", false) );
                        }
                        while(valeur - IX >= 0) {
                            valeur -= IX;
                            m.push_back( base_element("I", false) );
                            m.push_back( base_element("X", false) );
                        }
                        while(valeur - V >= 0) {
                            valeur -= V;
                            m.push_back( base_element("V", false) );
                        }
                        while(valeur - IV >= 0) {
                            valeur -= IV;
                            m.push_back( base_element("I", false) );
                            m.push_back( base_element("V", false) );
                        }
                        while(valeur - I >= 0) {
                            valeur -= I;
                            m.push_back( base_element("I", false) );
                        }
                    }
                    else
                        m.push_back(*it_c);
                }
                l.ajouter_mot(m);
            }
            t.ajouter_ligne(l);
        }
        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
}
