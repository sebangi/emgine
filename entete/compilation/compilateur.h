#ifndef COMPILATEUR_H
#define COMPILATEUR_H

/**
 * \file compilateur.h
 * \brief Fichier de déclaration de la classe compilateur.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/configuration.h"
#include "entete/compilation/log_compilation.h"
#include "entete/define.h"
#include "entete/element/textes.h"

#include <QStack>

#include <list>
#include <map>

class base_fonction;
class log_compilation;
class logs_compilation_widget;
class base_parametre;
class projet;

/**
 * \class compilateur
 * \brief Classe décrivant un compilateur. Le compilateur a pour rôle d'exécuter un projet.
 * \author Sébastien Angibaud
 */
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
        /** \brief Booléen indiquant si la compilation est en cours. */
        bool m_en_cours;

        /** \brief La pile de textes des paramètres. */
        QStack< textes > m_pile_textes;

        /** \brief Un pointeur sur le widget de vue des logs de compilation. */
        logs_compilation_widget * m_vue_logs;

        /** \brief La configuration en cours. */
        configuration m_configuration;
};

#endif // COMPILATEUR_H
