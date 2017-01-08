#ifndef COMPILATEUR_H
#define COMPILATEUR_H

#include "compilation/log_compilation.h"
#include "element/texte.h"

#include <list>
#include <QStack>

class projet;
class fonction;
class parametre;
class log_compilation;

class compilateur
{
    public:
        compilateur();

        void compiler(projet* p);

    private:
        bool est_valide(projet *p);
        void reset();
        void executer_projet(projet *p);
        void executer_fonction(base_fonction* f);
        void executer_parametre(base_parametre* p);
        void afficher_resultat();

    private:
        bool m_en_cours;
        QStack< texte > m_pile_textes;
};

#endif // COMPILATEUR_H
