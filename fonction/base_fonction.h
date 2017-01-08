#ifndef BASE_FONCTION_H
#define BASE_FONCTION_H

#include <string>
#include <QString>
#include <list>
#include <set>
#include <map>
#include <QXmlStreamWriter>
#include <QObject>

#include "old_texte.h"
#include "element/texte.h"
#include "define.h"
#include "parametre/base_parametre.h"

class noeud_fonction;
class base_fonction_widget;
class compilateur;

/**
 \brief Classe décrivant une fonction de conversion d'un texte.
 \author Sébastien Angibaud
*/
class base_fonction : public QObject
{
        Q_OBJECT

    public:
        enum type_fonction
        {
            fonction_source = 0,
            fonction_conversion,
            fonction_sortie
        };

    public:
        typedef std::map< type_id_parametre, base_parametre *> type_parametres;
        typedef type_parametres::iterator parametres_iterateur;
        typedef type_parametres::const_iterator parametres_const_iterateur;

    protected:
        typedef std::set<base_fonction_widget *> type_set_widgets;

    public:
        base_fonction( fonctions_conteneur * conteneur, const QString & nom, type_fonction type = fonction_conversion);
        virtual ~base_fonction();
        virtual void initialisation_par_defaut();

        /**
        \brief Méthode virtuelle pure d'application de la fonction.
        */
        virtual void executer( compilateur & compil, const texte & texte_in, texte & texte_out ) = 0;

        /**
        \brief Méthode virtuelle pure d'accès à l'info bulle.
        */
        QString get_info_bulle() const;

        void sauvegarder( QXmlStreamWriter & stream ) const;
        bool est_fonction_valide() const;
        virtual QString get_aide() const = 0;
        virtual QString get_valeur_courte() const = 0;

        virtual base_fonction_widget *generer_fonction_widget();

        QString get_nom() const;
        type_fonction get_type() const;
        void set_noeud( noeud_fonction * n );
        noeud_fonction * get_noeud();
        bool est_active() const;
        void set_est_active(bool est_active);
        void inverser_activation();

        void add_widget(base_fonction_widget *widget);
        void remove_widget(base_fonction_widget *widget);
        bool has_widget() const;
        base_fonction_widget *get_first_widget();

        parametres_iterateur parametres_begin();
        parametres_iterateur parametres_end();
        parametres_const_iterateur parametres_const_begin() const;
        parametres_const_iterateur parametres_const_end() const;

        base_parametre* get_parametre(type_id_parametre id);

        bool get_parametre_visible() const;
        void set_parametre_visible(bool parametre_visible);

        void set_id(const type_id_fonction &id);
        void charger(QXmlStreamReader & xm);

    signals:
        void signal_destruction_fonction(base_fonction* f);
        void signal_activation_fonction_change(base_fonction * f);

    private:
        void charger_parametre(QXmlStreamReader & xm);
        virtual bool est_valide() const = 0;

    protected:
        void ajouter_parametre(type_id_parametre nom, base_parametre* p);
        const texte & get_texte_parametre( type_id_parametre type ) const;

    protected:
        /** \brief Le nom de la fonction. */
        QString m_nom;

        /** \brief La liste des parametres. */
        type_parametres m_parametres;

    protected:
        type_set_widgets m_widgets;

    private:
        type_fonction m_type;
        type_id_fonction m_id;
        bool m_est_active;
        bool m_parametre_visible;
        fonctions_conteneur * m_conteneur;
};



#endif // BASE_FONCTION_H
