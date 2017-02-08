#include "entete/fonction/bibliotheque_fonctions.h"

#include "entete/fonction/fonction_source/fonction_source_booleen.h"
#include "entete/fonction/fonction_source/fonction_source_entier.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/fonction/fonction_source/fonction_source_fichier_texte.h"
#include "entete/fonction/fonction_source/fonction_source_caractere.h"
#include "entete/fonction/fonction_source/fonction_source_choix.h"
#include "entete/fonction/fonction_source/fonction_source_permutation.h"

#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include "entete/fonction/fonction_conversion/fonction_cesar.h"

std::map<type_id_fonction, QString> bibliotheque_fonctions::s_fonctions_nom =
{
    { f_source_booleen, "Oui ou Non" },
    { f_source_entier, "Entier" },
    { f_source_texte, "Texte" },
    { f_source_fichier_texte, "Fichier texte" },
    { f_source_caractere, "Caractères" },
    { f_source_choix, "Choix" },
    { f_source_generateur_permutation, "Générateur de permutations" },
    { f_conversion_cesar, "Chiffrement par Code César" },
    { f_sortie_texte, "Textes" }
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
    { f_conversion_cesar, "Outil pour décoder/encoder avec César.\nLe code César (ou chiffre de César) est un chiffrement par décalage parmi les plus simples et les plus connu, il utilise la substitution d'une lettre par une autre plus loin dans l'alphabet." },
    { f_sortie_texte, "Sortie textuelle : la liste de tous les textes obtenus." }
};

std::map<type_id_fonction, std::set<QString> > bibliotheque_fonctions::s_categories =
{
    { f_source_booleen,
      { "booléen", "booleen" }
    },
    { f_source_entier,
      {  }
    },
    { f_source_texte,
      { }
    },
    { f_source_fichier_texte,
      { }
    },
    { f_source_caractere,
      { "caracteres" }
    },
    { f_source_choix,
      { }
    },
    { f_source_generateur_permutation,
      { }
    },
    { f_conversion_cesar,
      { }
    },
    { f_sortie_texte,
      { }
    }
};

base_fonction *bibliotheque_fonctions::get_fonction(type_id_fonction id)
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
        return "Fonction non documentée";
    else
        return it->second;
}

QString bibliotheque_fonctions::get_nom(type_id_fonction id)
{
    std::map<type_id_fonction, QString>::iterator it = s_fonctions_nom.find(id);

    if( it == s_fonctions_nom.end() )
        return "fonction inconnue";
    else
        return it->second;
}

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

