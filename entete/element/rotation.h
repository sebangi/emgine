#ifndef ROTATION_H
#define ROTATION_H

/** \file rotation.h
 * \brief Fichier de déclaration de la classe rotation.
 * \author Sébastien Angibaud
 */

#include <QStringList>

/**
 * \class rotation
 * \brief Classe décrivant une rotation.
 * \author Sébastien Angibaud
 */
class rotation
{
    public:
        /** \enum type_rotation
         *  \author Sébastien Angibaud
         *  \brief Enumération représentant les différentes rotations possibles.
         */
        enum type_rotation
        {
            /** \brief Une rotation de 0 degré. */
            rotation_0 = 0,

            /** \brief Une rotation de 90 degré. */
            rotation_90,

            /** \brief Une rotation de 180 degrés. */
            rotation_180,

            /** \brief Une rotation de 270 degrés. */
            rotation_270,

            /** \brief Une rotation non valide. */
            rotation_invalide,
        };

    public:
        rotation(QString s);

        bool est_valide() const;
        type_rotation get_type() const;

        static QStringList liste_rotations_valides();
        static QStringList liste_rotations_par_defaut();

    private:
        /** \brief Le séparateur de caractères. */
        type_rotation m_type;
};




#endif // ROTATION_H
