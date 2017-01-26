#ifndef BASE_FONCTION_H
#define BASE_FONCTION_H

#include <string>
#include <QString>
#include <list>
#include <set>
#include <map>
#include <QXmlStreamWriter>

#include "entete/element/textes.h"
#include "entete/define.h"
#include "entete/projet/base_parametre.h"
#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/fonctions_conteneur.h"

class noeud_fonction;
class base_fonction_widget;
class compilateur;
class logs_compilation_widget;

/**
 \brief Classe décrivant une fonction de conversion d'un texte.
 \author Sébastien Angibaud
*/
class base_fonction : public objet_selectionnable
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
        typedef std::map< type_id_parametre, mot::const_iterator > type_map_IPMPL;
        typedef void ( base_fonction::*pf_exec_callback)( compilateur &, const textes &, textes & );

    public:
        base_fonction( fonctions_conteneur * parent, const QString & nom, type_fonction type = fonction_conversion);
        virtual ~base_fonction();
        virtual void initialisation_par_defaut();

        /**
        \brief Méthode virtuelle pure d'application de la fonction.
        */
        virtual void executer( compilateur & compil, const textes & textes_in, textes & textes_out ) = 0;

        /**
        \brief Méthode virtuelle pure d'accès à l'info bulle.
        */
        QString get_info_bulle() const;

        bool est_fonction() const;

        void sauvegarder( QXmlStreamWriter & stream ) const;
        bool est_fonction_valide(logs_compilation_widget * vue_logs) const;
        virtual QString get_aide() const = 0;
        virtual QString get_valeur_courte() const = 0;

        virtual base_fonction_widget *generer_fonction_widget();

        QString get_nom() const;
        type_fonction get_type() const;
        void set_noeud( noeud_fonction * n );
        noeud_fonction * get_noeud();
        void inverser_activation();
        int get_position();

        parametres_iterateur parametres_begin();
        parametres_iterateur parametres_end();
        parametres_const_iterateur parametres_const_begin() const;
        parametres_const_iterateur parametres_const_end() const;

        base_parametre* get_parametre(type_id_parametre id);

        int get_niveau_visibilite() const;
        int get_max_niveau_visibilite() const;
        void set_niveau_visibilite( int niveau_visibilite );
        void change_niveau_visibilite();
        void set_est_active(bool active);
        void set_est_etendu(bool est_etendu);

        bool a_parametre() const;

        void set_id(const type_id_fonction &id);
        type_id_fonction get_id() const;
        void charger(QXmlStreamReader & xm);

        fonctions_conteneur *get_conteneur() const;
        void set_conteneur(fonctions_conteneur *conteneur);


    signals:
        void signal_destruction_fonction(base_fonction* f);
        void signal_activation_fonction_change(base_fonction * f);
        void signal_niveau_visibilite_change(base_fonction * f);
        void signal_etendu_change(base_fonction * f);

    private:
        void charger_parametres(QXmlStreamReader & xm);
        void charger_parametre(QXmlStreamReader & xm);
        virtual bool est_valide(logs_compilation_widget * vue_logs) const = 0;

    protected:
        void ajouter_parametre(type_id_parametre nom, base_parametre* p);
        const textes & get_textes_parametre( type_id_parametre type ) const;
        void augmenter_max_niveau_visibilite( int val );

        // Algorithme d'exécution
        void algo_IPMPL_iteration_premier_mot_par_ligne
        ( type_id_parametre id_param, compilateur &compil, const textes & textes_in, textes & textes_out,
          pf_exec_callback callback );
        void IPMPL_suivant( type_id_parametre id_param );

    public:
        virtual void callback_param_1( compilateur &compil, const textes & textes_in, textes & textes_out );
        virtual void callback_param_2( compilateur &compil, const textes & textes_in, textes & textes_out );
        virtual void callback_param_3( compilateur &compil, const textes & textes_in, textes & textes_out );
        virtual void callback_param_4( compilateur &compil, const textes & textes_in, textes & textes_out );

    protected:
        /** \brief Le nom de la fonction. */
        QString m_nom;

        /** \brief La liste des parametres. */
        type_parametres m_parametres;

        type_map_IPMPL m_map_IPMPL_debut;
        type_map_IPMPL m_map_IPMPL_courant;
        type_map_IPMPL m_map_IPMPL_fin;

    private:
        type_fonction m_type;
        type_id_fonction m_id;
        fonctions_conteneur * m_conteneur;
        int m_niveau_visibilite;
        int m_max_niveau_visibilite;
        int m_niveau_visibilite_avant_desactivation;
};


#endif // BASE_FONCTION_H
