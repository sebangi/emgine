#ifndef LISTE_CHOIX_H
#define LISTE_CHOIX_H

/** \file liste_choix.h
 * \brief Fichier de déclaration de la classe liste_choix.
 * \author Sébastien Angibaud
 */

#include <QStringList>

/** \brief Le type choix. */
typedef QString choix;

/**
 * \class liste_choix
 * \brief Classe décrivant une liste de choix.
 * \author Sébastien Angibaud
 */
class liste_choix
{
    public:
            /** \brief Un choix non valide. */
            static const QString choix_invalide;

            /** \brief Une rotation de 0 degré. */
            static const QString rotation_0;

            /** \brief Une rotation de 90 degré. */
            static const QString rotation_90;

            /** \brief Une rotation de 180 degré. */
            static const QString rotation_180;

            /** \brief Une rotation de 270 degré. */
            static const QString rotation_270;

            /** \brief Le choix porte sur les caractère. */
            static const QString appliquer_sur_caracteres;

            /** \brief Le choix porte sur les caractère. */
            static const QString appliquer_sur_mots;

    public:
        liste_choix(const QStringList & liste_choix_possibles, const QStringList & liste_choix_par_defaut);

        bool est_valide( const QStringList& c ) const;
        bool est_valide( const QString& c ) const;

        const QStringList& liste_choix_possibles() const;
        const QStringList& liste_choix_par_defaut() const;

    private:
        /** \brief La liste des liste_choix possibles. */
        QStringList m_liste_choix_possibles;

        /** \brief La liste des liste_choix par défaut. */
        QStringList m_liste_choix_par_defaut;
};

#endif // LISTE_CHOIX_H
