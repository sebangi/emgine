#ifndef TEXTES_H
#define TEXTES_H

/** \file textes.h
 * \brief Fichier de déclaration de la classe textes.
 * \author Sébastien Angibaud
 */

#include "entete/element/texte.h"

#include <vector>

/**
 * \class textes
 * \brief Classe décrivant un ensemble de textes.
 * \author Sébastien Angibaud
 */
class textes : public std::vector< texte >
{
    public:
        textes();
        textes( const QString& valeur);
        textes( const textes& t );

        QString to_string() const;
        QString to_string_lisible() const;

        void ajouter_texte(const configuration & config, const texte& t);
        void calculer_frequence( bool force_upper_case );
        void calculer_indice_coincidence();
        void fusionner(bool fusion_caracteres, bool fusion_mots, bool fusion_lignes, bool fusion_textes);        
};

#endif // TEXTES_Hs
