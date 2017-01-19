#ifndef COMPILATEUR_H
#define COMPILATEUR_H

#include "entete/compilation/log_compilation.h"
#include "entete/element/texte.h"

#include <list>
#include <QStack>

class projet;
class fonction;
class parametre;
class log_compilation;
class logs_compilation_widget;

class compilateur
{
    public:
        compilateur(logs_compilation_widget * get_vue_logs);
        void compiler(projet* p);

        logs_compilation_widget * get_vue_logs() const;

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
        logs_compilation_widget * m_vue_logs;
};

#endif // COMPILATEUR_H
