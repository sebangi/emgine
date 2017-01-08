#ifndef FONCTION_BASE_SORTIE_H
#define FONCTION_BASE_SORTIE_H

#include "fonction/base_fonction.h"

class texte;

class fonction_base_sortie : public base_fonction
{
    public:
        fonction_base_sortie(fonctions_conteneur * conteneur, const QString & nom);
        ~fonction_base_sortie();

        void set_texte(const texte &texte);

    private:
        texte m_texte;
};

#endif // FONCTION_BASE_SORTIE_H
