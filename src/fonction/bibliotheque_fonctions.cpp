/** \file bibliotheque_fonctions.cpp
 * \brief Fichier d'implémentation de la classe bibliotheque_fonctions.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/bibliotheque_fonctions.h"

// include des fonctions source
#include "entete/fonction/fonction_source/fonction_source_booleen.h"
#include "entete/fonction/fonction_source/fonction_source_caractere.h"
#include "entete/fonction/fonction_source/fonction_source_choix.h"
#include "entete/fonction/fonction_source/fonction_source_dictionnaire.h"
#include "entete/fonction/fonction_source/fonction_source_entier.h"
#include "entete/fonction/fonction_source/fonction_source_fichier_texte.h"
#include "entete/fonction/fonction_source/fonction_source_permutation.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"

// include des fonctions de sortie
#include "entete/fonction/fonction_sortie/fonction_sortie_analyse_ligne.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_frequence.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_indice_coincidence.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

// include des fonctions de conversion
#include "entete/fonction/fonction_conversion/fonction_ajout_espace_selon_dictionnaire.h"
#include "entete/fonction/fonction_conversion/fonction_anagramme.h"
#include "entete/fonction/fonction_conversion/fonction_cesar.h"
#include "entete/fonction/fonction_conversion/fonction_choisir_separateur.h"
#include "entete/fonction/fonction_conversion/fonction_ecriture_morse.h"
#include "entete/fonction/fonction_conversion/fonction_entier_en_chiffre_romain.h"
#include "entete/fonction/fonction_conversion/fonction_formatage.h"
#include "entete/fonction/fonction_conversion/fonction_fusion.h"
#include "entete/fonction/fonction_conversion/fonction_lecture_morse.h"
#include "entete/fonction/fonction_conversion/fonction_selection_selon_dictionnaire.h"
#include "entete/fonction/fonction_conversion/fonction_substitution.h"
#include "entete/fonction/fonction_conversion/fonction_transposition.h"

std::map<type_id_fonction, QString> bibliotheque_fonctions::s_fonctions_nom =
{
    { f_source_booleen, "Oui ou Non" },
    { f_source_entier, "Entier" },
    { f_source_texte, "Texte" },
    { f_source_fichier_texte, "Fichier texte" },
    { f_source_caractere, "Caractères" },
    { f_source_choix, "Choix" },
    { f_source_generateur_permutation, "Générateur de permutations" },
    { f_source_dictionnaire, "Dictionnaire" },

    { f_conversion_cesar, "Chiffrement par Code César" },
    { f_conversion_formatage, "Formatage du texte" },
    { f_conversion_selection_selon_dictionnaire, "Sélection selon dictionnaire" },
    { f_conversion_anagramme, "Anagramme" },
    { f_conversion_entier_en_chiffre_romain, "Ecriture en chiffre romain" },
    { f_conversion_ajout_espace_selon_dictionnaire, "Ajout d'espaces selon dictionnaire" },
    { f_conversion_fusion, "Fusion du texte" },
    { f_conversion_substitution, "Substitution de caractères" },
    { f_conversion_ecriture_morse, "Écriture en morse" },
    { f_conversion_lecture_morse, "Lecture du morse" },
    { f_conversion_choisir_separateur, "Choix des séparateurs" },
    { f_conversion_transposition, "Transposition du texte" },

    { f_sortie_texte, "Textes" },
    { f_sortie_frequence, "Fréquences des éléments" },
    { f_sortie_indice_coincidence, "Indice de coincidence" },
    { f_sortie_analyse_ligne, "Analyse des lignes" }
};

std::map<type_id_fonction, QString> bibliotheque_fonctions::s_fonctions_aide =
{
    { f_source_booleen, "Source de type Oui ou Non" },
    { f_source_entier, "Source de type entier" },
    { f_source_texte, "Source textuelle" },
    { f_source_fichier_texte, "Source fichier textuel" },
    { f_source_caractere, "Source de type un caractère" },
    { f_source_choix, "Source de type choix" },
    { f_source_generateur_permutation, "Générateur de permutations" },
    { f_source_dictionnaire, "Ajoute un dictionnaire" },

    { f_conversion_cesar, "Outil pour décoder/encoder avec César.\nLe code César (ou chiffre de César) est un chiffrement par décalage parmi les plus simples et les plus connu, il utilise la substitution d'une lettre par une autre plus loin dans l'alphabet." },
    { f_conversion_formatage, "Formate le texte, i.e. mise en majuscule, retrait des accents et éventuellement de la ponctuation." },
    { f_conversion_selection_selon_dictionnaire, "Sélectionne les textes selon un dictionnaire donné. Cela permet de filtrer par exemple les textes écrits en français." },
    { f_conversion_anagramme, "Affiche les anagrammes de chaque mot." },
    { f_conversion_entier_en_chiffre_romain, "Convertit les entiers en chiffres romains." },
    { f_conversion_ajout_espace_selon_dictionnaire, "Ajoute les espaces entre mot selon un dictionnaire donné." },
    { f_conversion_formatage, "Fusion des caractères, des mots, des lignes ou des textes." },
    { f_conversion_substitution, "Substitution de caractères." },
    { f_conversion_ecriture_morse, "Écriture en morse" },
    { f_conversion_lecture_morse, "Lecture du morse" },
    { f_conversion_choisir_separateur, "Choix des séparateurs (de caractères, de mots et de lignes)" },
    { f_conversion_transposition, "Transposition du texte (des mots ou des caractères)" },

    { f_sortie_texte, "Sortie textuelle : la liste de tous les textes obtenus." },
    { f_sortie_frequence, "Sortie affichant la fréquence des éléments." },
    { f_sortie_indice_coincidence, "Sortie affichant l'indice de coincidence.\nEn français, l'indice vaut environ 0,0778. Si l'indice de coincidence est grand (proche de 0.070), c'est à dire similaire à celui d'un message non chiffré, alors le message a probablement subit une substitution monoalphabetiquehref (une même lettre ne peut être remplacée que par une seule autre). Si l'indice de coincidence est faible (proche de 0.0385), c'est à dire similaire à une répartition aléatoire, alors le message a probablement subit un chiffrement polyalphabétique (une même lettre peut être remplacée par plusieurs autres). Plus l'indice est faible, plus le nombre d'alphabets utilisé est grand." },
    { f_sortie_analyse_ligne, "Sortie affichant l'analyse de chaque ligne, i.e. son nombre de mots et de caractères." }
};

std::map<type_id_fonction, std::set<QString> > bibliotheque_fonctions::s_categories =
{
    { f_source_booleen,
      { "booléen", "booleen" }
    },
    { f_source_caractere,
      { "caracteres" }
    }
};

/** --------------------------------------------------------------------------------------
 * \brief Crée et retourne une fonction pour un type donné.
 * \param id Le type de fonction à créer.
 * \return Un pointeur sur la fonction créée.
 */
base_fonction * bibliotheque_fonctions::get_fonction(type_id_fonction id)
{
    switch ( id ) {
        // SOURCES
        case f_source_booleen : return new fonction_source_booleen(NULL);
        case f_source_entier : return new fonction_source_entier(NULL);
        case f_source_texte : return new fonction_source_texte(NULL);
        case f_source_fichier_texte : return new fonction_source_fichier_texte(NULL);
        case f_source_caractere : return new fonction_source_caractere(NULL);
        case f_source_choix : return new fonction_source_choix(NULL);
        case f_source_generateur_permutation : return new fonction_source_permutation(NULL);
        case f_source_dictionnaire : return new fonction_source_dictionnaire(NULL);

            // CONVERSIONS
        case f_conversion_cesar : return new fonction_cesar(NULL);
        case f_conversion_formatage : return new fonction_formatage(NULL);            
        case f_conversion_selection_selon_dictionnaire : return new fonction_selection_selon_dictionnaire(NULL);
        case f_conversion_anagramme : return new fonction_anagramme(NULL);
        case f_conversion_entier_en_chiffre_romain : return new fonction_entier_en_chiffre_romain(NULL);
        case f_conversion_ajout_espace_selon_dictionnaire : return new fonction_ajout_espace_selon_dictionnaire(NULL);
        case f_conversion_fusion : return new fonction_fusion(NULL);
        case f_conversion_substitution : return new fonction_substitution(NULL);
        case f_conversion_ecriture_morse : return new fonction_ecriture_morse(NULL);
        case f_conversion_lecture_morse : return new fonction_lecture_morse(NULL);
        case f_conversion_choisir_separateur : return new fonction_choisir_separateur(NULL);
        case f_conversion_transposition : return new fonction_transposition(NULL);

            // SORTIES
        case f_sortie_texte : return new fonction_sortie_texte(NULL);
        case f_sortie_frequence : return new fonction_sortie_frequence(NULL);
        case f_sortie_indice_coincidence : return new fonction_sortie_indice_coincidence(NULL);
        case f_sortie_analyse_ligne : return new fonction_sortie_analyse_ligne(NULL);

        default:
            return NULL;
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le texte d'aide pour un type de fonction donné.
 * \param id Le type de la fonction à considérer.
 * \return Le texte d'aide.
 */
QString bibliotheque_fonctions::get_aide(type_id_fonction id)
{
    std::map<type_id_fonction, QString>::iterator it = s_fonctions_aide.find(id);

    if( it == s_fonctions_aide.end() )
        return "Fonction non documentée";
    else
        return it->second;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nom pour un type de fonction donné.
 * \param id Le type de la fonction à considérer.
 * \return Le nom de la fonction.
 */
QString bibliotheque_fonctions::get_nom(type_id_fonction id)
{
    std::map<type_id_fonction, QString>::iterator it = s_fonctions_nom.find(id);

    if( it == s_fonctions_nom.end() )
        return "fonction inconnue";
    else
        return it->second;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si une fonction d'un type donné contient un mot clé spécifié.
 * \param id Le type de la fonction à considérer.
 * \param cle Le mot clé à chercher.
 * \return \b True si le mot clé a été trouvé, \b False sinon.
 */
bool bibliotheque_fonctions::contient_mot_cle(type_id_fonction id, const QString &cle)
{
    if ( cle.isEmpty() )
        return true;
    else
    {
        // recherche dans les noms
        std::map<type_id_fonction, QString>::iterator it_nom = s_fonctions_nom.find(id);
        if( it_nom != s_fonctions_nom.end() )
            if ( it_nom->second.contains( cle, Qt::CaseInsensitive ) )
                return true;

        // recherche dans l'aide
        std::map<type_id_fonction, QString>::iterator it_aide = s_fonctions_aide.find(id);
        if( it_aide != s_fonctions_aide.end() )
            if ( it_aide->second.contains( cle, Qt::CaseInsensitive ) )
                return true;

        // recherche dans les catégories
        std::map<type_id_fonction, std::set<QString> >::iterator it = s_categories.find(id);

        if( it != s_categories.end() )
            for ( std::set<QString>::iterator it_m = it->second.begin(); it_m != it->second.end(); ++it_m )
                if ( it_m->contains( cle, Qt::CaseInsensitive ) )
                    return true;
    }

    return false;
}

