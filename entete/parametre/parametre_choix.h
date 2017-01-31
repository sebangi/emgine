#ifndef PARAMETRE_CHOIX_H
#define PARAMETRE_CHOIX_H

#include "entete/projet/base_parametre.h"
#include <QStringList>

/**
 \brief Classe décrivant un parametre de type choix.
 \author Sébastien Angibaud
*/
class parametre_choix : public base_parametre
{
        Q_OBJECT

    public:
        parametre_choix( objet_selectionnable * parent, QString nom, QString aide, bool peut_etre_vide,
                         bool dans_configuration, type_algorithme algorithme,
                         const QStringList & choix, bool multiple_selection);
        ~parametre_choix();

        QStringList choix() const;
        bool multiple_selection() const;

    private:
        QStringList m_choix;
        bool m_multiple_selection;
};

#endif // PARAMETRE_CHOIX_H
