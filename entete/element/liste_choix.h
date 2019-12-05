#ifndef LISTE_CHOIX_H
#define LISTE_CHOIX_H

/** \file liste_choix.h
 * \brief Fichier de déclaration de la classe liste_choix.
 * \author Sébastien Angibaud
 */

#include <QStringList>
#include <QObject>

/** \brief Le type choix. */
typedef QString choix;

/**
 * \class liste_choix
 * \brief Classe décrivant une liste de choix.
 * \author Sébastien Angibaud
 */
class liste_choix : public QObject
{
        Q_OBJECT

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

            /** \brief Le choix porte sur les caractères. */
            static const QString appliquer_sur_caracteres;

            /** \brief Le choix porte sur les mots. */
            static const QString appliquer_sur_mots;

            /** \brief Le choix porte sur les lignes. */
            static const QString appliquer_sur_lignes;

            /** \brief Le choix porte sur les textes. */
            static const QString appliquer_sur_textes;

            /** \brief Le choix de l'orentation de haut en bas. */
            static const QString de_haut_en_bas;

            /** \brief Le choix de l'orentation de bas en haut. */
            static const QString de_bas_en_haut;

            /** \brief Le choix de l'orentation de gauche à droite. */
            static const QString de_gauche_a_droite;

            /** \brief Le choix de l'orentation de droite_a_gauche. */
            static const QString de_droite_a_gauche;

            /** \brief Le choix de la diagonale haut_gauche_bas_droit. */
            static const QString diagonale_haut_gauche_bas_droit;

            /** \brief Le choix de la diagonale bas_gauche_haut_droit. */
            static const QString diagonale_bas_gauche_haut_droit;

    public:
        liste_choix();
        liste_choix(const liste_choix & l_choix);
        liste_choix(const QStringList & liste_choix_possibles, const QStringList & liste_choix_par_defaut);
        ~liste_choix();

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
