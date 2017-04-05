#ifndef PARAMETRE_CHOIX_H
#define PARAMETRE_CHOIX_H

/** \file parametre_choix.h
 * \brief Fichier de déclaration de la classe parametre_choix.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_parametre.h"

#include <QStringList>

class liste_choix;

/**
 \class parametre_choix
 \brief Classe décrivant un parametre de type choix.
 \author Sébastien Angibaud
*/
class parametre_choix : public base_parametre
{
        Q_OBJECT

    public:
        parametre_choix( objet_selectionnable * parent, QString nom, QString aide,
                         type_mode_contenu_parametre mode_contenu_parametre,
                         type_mode_configuration_visibilite mode_configuration_visibilite,
                         type_algorithme algorithme,
                         const liste_choix & choix, bool multiple_selection);
        ~parametre_choix();

        QStringList get_choix() const;
        bool multiple_selection() const;

    private:
        /** \brief La liste des choix. */
        liste_choix m_choix;

        /** \brief Booléen indiquant si la sélection peut être multiple. */
        bool m_multiple_selection;
};

#endif // PARAMETRE_CHOIX_H
