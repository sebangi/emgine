#include "entete/fonction/bibliotheque_fonctions.h"

#include "entete/fonction/fonction_source/fonction_source_booleen.h"
#include "entete/fonction/fonction_source/fonction_source_entier.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/fonction/fonction_source/fonction_source_caractere.h"
#include "entete/fonction/fonction_source/fonction_source_choix.h"
#include "entete/fonction/fonction_source/fonction_source_permutation.h"

#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include "entete/fonction/fonction_conversion/fonction_cesar.h"

std::map<type_id_fonction, QString> bibliotheque_fonctions::s_fonctions_aide =
{
    { f_source_booleen, "Source de type Oui ou Non" },
    { f_source_entier, "Source de type entier" },
    { f_source_texte, "Source textuelle" },
    { f_source_caractere, "Source de type un caractère" },
    { f_source_choix, "Source de type choix" },
    { f_source_generateur_permutation, "Générateur de permutations" },
    { f_conversion_cesar, "Outil pour décoder/encoder avec César.\nLe code César (ou chiffre de César) est un chiffrement par décalage parmi les plus simples et les plus connu, il utilise la substitution d'une lettre par une autre plus loin dans l'alphabet." },
    { f_sortie_texte, "Sortie textuelle" }
};

QString bibliotheque_fonctions::nom_to_string(type_id_fonction id)
{
    switch ( id ) {
        // SOURCES
        case f_source_booleen : return "Source de type booléen";
        case f_source_entier : return "Source de type entier";
        case f_source_texte : return "Source textuelle";
        case f_source_caractere : return "Source de type caractères";
        case f_source_choix : return "Source de type choix";
        case f_source_generateur_permutation : return "Source générateur de permutations";

            // CONVERSIONS
        case f_conversion_cesar : return "Chiffrement par Code César"; break;

            // SORTIES
        case f_sortie_texte : return "Sortie textuelle";

        default:
            return "Fonction inconnue";
    }
}

base_fonction *bibliotheque_fonctions::get_fonction(type_id_fonction id)
{
    switch ( id ) {
        // SOURCES
        case f_source_booleen : return new fonction_source_booleen(NULL);
        case f_source_entier : return new fonction_source_entier(NULL);
        case f_source_texte : return new fonction_source_texte(NULL);
        case f_source_caractere : return new fonction_source_caractere(NULL);
        case f_source_choix : return new fonction_source_choix(NULL);
        case f_source_generateur_permutation : return new fonction_source_permutation(NULL);

            // CONVERSIONS
        case f_conversion_cesar : return new fonction_cesar(NULL);
            // SORTIES
        case f_sortie_texte : return new fonction_sortie_texte(NULL);

        default:
            return NULL;
    }
}

QString bibliotheque_fonctions::get_aide(type_id_fonction id)
{
    std::map<type_id_fonction, QString>::iterator it = s_fonctions_aide.find(id);

    if( it == s_fonctions_aide.end() )
        return QString();
    else
        return it->second;
}

