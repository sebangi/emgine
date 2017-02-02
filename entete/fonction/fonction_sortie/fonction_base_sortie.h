#ifndef FONCTION_BASE_SORTIE_H
#define FONCTION_BASE_SORTIE_H

#include "entete/projet/base_fonction.h"

class textes;

class fonction_base_sortie : public base_fonction
{
    public:
        fonction_base_sortie(fonctions_conteneur * conteneur);
        ~fonction_base_sortie();

        void set_textes(const textes &textes);

    private:
        textes m_textes;
};

#endif // FONCTION_BASE_SORTIE_H
