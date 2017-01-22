#ifndef COMPILATEUR_H
#define COMPILATEUR_H

#include "entete/compilation/log_compilation.h"
#include "entete/compilation/configuration.h"
#include "entete/element/textes.h"
#include "entete/define.h"

#include <list>
#include <map>
#include <QStack>

class projet;
class base_fonction;
class parametre;
class log_compilation;
class logs_compilation_widget;

class compilateur
{
    public:
        compilateur(logs_compilation_widget * get_vue_logs);
        void compiler(projet* p);

        logs_compilation_widget * get_vue_logs() const;
        void ajouter_configuration(base_fonction * f, type_id_parametre param, const QString& config);
        void retirer_configuration(base_fonction * f, type_id_parametre param);

        configuration get_configuration() const;

    private:
        bool est_valide(projet *p);
        void reset();
        void executer_projet(projet *p);
        void executer_fonction(base_fonction* f);
        void executer_parametre(base_parametre* p);
        void afficher_resultat();

    private:
        bool m_en_cours;
        QStack< textes > m_pile_textes;
        logs_compilation_widget * m_vue_logs;
        configuration m_configuration;
};

#endif // COMPILATEUR_H
