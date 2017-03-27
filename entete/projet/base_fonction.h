#ifndef BASE_FONCTION_H
#define BASE_FONCTION_H

/** \file base_fonction.h
 * \brief Déclaration de la classe base_fonction.
 * \author Sébastien Angibaud
 */

#include "entete/element/textes.h"
#include "entete/fonction/algorithme/algo_IPL.h"
#include "entete/fonction/define_fonction.h"
#include "entete/projet/base_parametre.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/projet/objet_selectionnable.h"

#include <QString>
#include <QXmlStreamWriter>

#include <list>
#include <map>
#include <set>

class base_fonction_widget;
class compilateur;
class logs_compilation_widget;
class noeud_fonction;

/**
 \brief Classe décrivant une fonction de conversion d'un texte.
 \author Sébastien Angibaud
*/
class base_fonction : public objet_selectionnable
{
        Q_OBJECT

    public:
        /** \brief Tableau associant à un identifiant le paramètre associé. */
        typedef std::map< type_id_parametre, base_parametre *> type_parametres;

        /** \brief Itérateur sur le tableau de paramètres. */
        typedef type_parametres::iterator parametres_iterateur;

        /** \brief Itérateur constant sur le tableau de paramètres. */
        typedef type_parametres::const_iterator parametres_const_iterateur;

    protected:
        /** \brief Type des fonctions d'exécution. */
        typedef void ( base_fonction::*pf_exec_callback)( compilateur &, textes &, textes & );

    public:
        base_fonction( fonctions_conteneur * parent, type_fonction type = type_fonction::fonction_conversion);
        virtual ~base_fonction();

        /**
         * \brief Méthode virtuelle pure qui exécute la fonction.
         * \param compil Le compilateur utilisé.
         * \param textes_in Le texte source en entrée.
         * \param textes_out Le texte de sortie généré.
        */
        virtual void executer( compilateur & compil, textes & textes_in, textes & textes_out ) = 0;

        /** --------------------------------------------------------------------------------------
         * \brief Méthode virtuelle pure retournant la valeur de la fonction en version raccourci.
         * \return La valeur courte de la fonction.
         */
        virtual QString get_valeur_courte() const = 0;

        virtual void initialisation_par_defaut();
        virtual base_fonction_widget *generer_fonction_widget();
        bool est_fonction() const;
        void set_est_active(bool active);
        void set_est_etendu(bool est_etendu);

        QString get_info_bulle() const;
        void sauvegarder( QXmlStreamWriter & stream ) const;
        void charger(QXmlStreamReader & xm);

        bool est_fonction_valide(logs_compilation_widget * vue_logs);
        QString get_nom() const;
        type_fonction get_type() const;
        int get_position();
        int get_niveau_visibilite() const;
        int get_max_niveau_visibilite() const;
        void set_niveau_visibilite( int niveau_visibilite );
        void change_niveau_visibilite();
        void inverser_activation();
        void set_id(const type_id_fonction &id);
        type_id_fonction get_id() const;
        fonctions_conteneur *get_conteneur() const;
        void set_conteneur(fonctions_conteneur *conteneur);

        // gestion des paramètres
        parametres_iterateur parametres_begin();
        parametres_iterateur parametres_end();
        parametres_const_iterateur parametres_const_begin() const;
        parametres_const_iterateur parametres_const_end() const;

        base_parametre* get_parametre(type_id_parametre id);
        bool a_parametre() const;

    signals:
        /** --------------------------------------------------------------------------------------
         * \brief Signal informant de la destruction d'une fonction.
         * \param f Un pointeur sur la fonction détruite.
         */
        void signal_destruction_fonction(base_fonction* f);

        /** --------------------------------------------------------------------------------------
         * \brief Signal informant d'une modification d'activation d'une fonction.
         * \param f Un pointeur sur la fonction modifiée.
         */
        void signal_activation_fonction_change(base_fonction * f);

        /** --------------------------------------------------------------------------------------
         * \brief Signal informant d'une modification de la visibilité d'une fonction.
         * \param f Un pointeur sur la fonction modifiée.
         */
        void signal_niveau_visibilite_change(base_fonction * f);

        /** --------------------------------------------------------------------------------------
         * \brief Signal informant d'une modification de l'état étendu d'une fonction.
         * \param f Un pointeur sur la fonction modifiée.
         */
        void signal_etendu_change(base_fonction * f);

    private:
        void charger_parametres(QXmlStreamReader & xm);
        void charger_parametre(QXmlStreamReader & xm);

        /** --------------------------------------------------------------------------------------
          \brief Méthode virtuelle pure testant si la fonction est valide.
          \param vue_logs Un pointeur sur le widget de vue des logs.
          \return \b True si la fonction est valide, \b False sinon.
        */
        virtual bool est_valide(logs_compilation_widget * vue_logs) = 0;

    protected:
        void ajouter_parametre(type_id_parametre nom, base_parametre* p);
        const textes & get_textes_parametre( type_id_parametre type ) const;
        void augmenter_max_niveau_visibilite( int val );
        void diminuer_max_niveau_visibilite( int val );

        // Algorithme d'exécution IPL
        void algo_IPL_iteration_par_ligne
        ( type_id_parametre id_param, compilateur &compil, textes & textes_in, textes & textes_out,
          pf_exec_callback callback );
        void IPL_mot_suivant( type_id_parametre id_param );
        void IPL_caractere_suivant_dans_mot( type_id_parametre id_param );
        void IPL_caractere_suivant_dans_ligne( type_id_parametre id_param );
        void IPL_init( type_id_parametre id_param );
        bool IPL_test_vide(type_id_parametre id_param);

    public:
        virtual void callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out );
        virtual void callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out );
        virtual void callback_param_3( compilateur &compil, textes & textes_in, textes & textes_out );
        virtual void callback_param_4( compilateur &compil, textes & textes_in, textes & textes_out );
        virtual void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );

    protected:
        /** \brief Le nom de la fonction. */
        QString m_nom;

        /** \brief La liste des parametres. */
        type_parametres m_parametres;

        /** \brief Les valeurs courantes des paramètres utilisant l'algorithme IPL. */
        algo_IPL::type_map_IPL m_map_IPL;

    private:
        /** \brief Le type de la fonction. */
        type_fonction m_type;

        /** \brief L'identifiant de la fonction. */
        type_id_fonction m_id;

        /** \brief Le conteneur de la fonction. */
        fonctions_conteneur * m_conteneur;

        /** \brief Le niveau de visibilité de la fonction. */
        int m_niveau_visibilite;

        /** \brief Le niveau maximum de visibilité de la fonction. */
        int m_max_niveau_visibilite;

        /** \brief Le niveau de visibilité de la fonction avant sa désactivation. */
        int m_niveau_visibilite_avant_desactivation;
};


#endif // BASE_FONCTION_H
