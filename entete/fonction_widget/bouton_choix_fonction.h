#ifndef BOUTON_CHOIX_FONCTION_H
#define BOUTON_CHOIX_FONCTION_H

#include "entete/projet/base_fonction.h"
#include "entete/define.h"
#include <QPushButton>

class bouton_choix_fonction : public QPushButton
{
    public:
        bouton_choix_fonction(type_id_fonction id, QWidget *parent = 0);

        base_fonction* get_fonction();

        type_id_fonction get_id_fonction() const;
        void mettre_a_jour_visibilite( const QString & cle );

    private:
        type_id_fonction m_id_fonction;
};

#endif // BOUTON_CHOIX_FONCTION_H
