#include "entete/fonction/bibliotheque_fonctions.h"

#include "entete/fonction/fonction_source/fonction_source_booleen.h"
#include "entete/fonction/fonction_source/fonction_source_entier.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/fonction/fonction_source/fonction_source_caractere.h"

#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include "entete/fonction/fonction_conversion/fonction_cesar.h"

QString bibliotheque_fonctions::nom_to_string(type_id_fonction id)
{
    switch ( id ) {
        // SOURCES
        case f_source_booleen : return "Source de type booléen";
        case f_source_entier : return "Source de type entier";
        case f_source_texte : return "Source textuelle";
        case f_source_caractere : return "Source de type caractère";

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

        // CONVERSIONS
        case f_conversion_cesar : return new fonction_cesar(NULL);
        // SORTIES
        case f_sortie_texte : return new fonction_sortie_texte(NULL);

        default:
            return NULL;
    }
}

