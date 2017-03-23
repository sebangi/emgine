#ifndef BASE_PARAMETRE_H
#define BASE_PARAMETRE_H

/** \file base_parametre.h
 * \brief Fichier de déclaration de la classe base_parametre.
 * \author Sébastien Angibaud
 */

#include "entete/element/base_element.h"
#include "entete/element/textes.h"
#include "entete/element/type_element.h"
#include "entete/fonction/define_parametre.h"
#include "entete/projet/fonctions_conteneur.h"

#include <QString>
#include <QXmlStreamWriter>

class base_fonction;
class logs_compilation_widget;
class noeud_parametre;

/**
 * \class base_parametre
 * \brief Classe décrivant un parametre d'une fonction.
 * \author Sébastien Angibaud
*/
class base_parametre : public fonctions_conteneur
{
        Q_OBJECT

    public:

        /** \enum type_mode_configuration_visibilite
         *  \author Sébastien Angibaud
         *  \brief Enumération représentant les différents mode de visibilité des paramètres.
         */
        enum type_mode_configuration_visibilite
        {
            /** \brief La configuration du paramètre est cachée. */
            CONFIGURATION_INVISIBLE = 0,

            /** \brief La configuration est visible. */
            CONFIGURATION_VISIBLE
        };

        /** \enum type_mode_contenu_parametre
         *  \author Sébastien Angibaud
         *  \brief Enumération représentant les différents mode de contenu des paramètres.
         */
        enum type_mode_contenu_parametre
        {
            /** \brief Le paramètre ne peut pas être vide. */
            CONTENU_PARAM_VIDE_IMPOSSIBLE = 0,

            /** \brief Le paramètre peut être vide. */
            CONTENU_PARAM_VIDE_POSSIBLE
        };

        /** \enum type_algorithme
         *  \author Sébastien Angibaud
         *  \brief Enumération décrivant les différents algorithmes pour l'excution des paramètres.
         */
        enum type_algorithme{
            /** \brief Tout le texte est considéré d'un coup. Aucune itération. */
            ALGO_AUCUN = 0,

            /** \brief Algorithme IPL, i.e. <b>Itération Par Ligne</b>. */
            ALGO_IPL
        };

    public:
        base_parametre( objet_selectionnable * parent, QString nom, QString aide,
                        type_mode_contenu_parametre mode_contenu_parametre,
                        type_mode_configuration_visibilite mode_configuration_visibilite, type_algorithme algorithme);
        ~base_parametre();

        void sauvegarder( QXmlStreamWriter & stream ) const;
        void charger( QXmlStreamReader & xml );

        QString get_nom() const;        
        QString get_titre() const;
        QString get_valeur_courte() const;
        QString get_aide() const;
        QString get_aide_algorithme() const;
        const textes& get_textes_out() const;
        base_fonction *get_fonction_parent() const;
        type_type_parametre get_type() const;

        bool est_valide(logs_compilation_widget * vue_logs);
        bool est_parametre() const;
        bool est_requis() const;

        void set_booleen_par_defaut( bool valeur );
        void set_texte_par_defaut( QString texte, QString separ_caractere = "", QString separ_mot = " ", QString separ_ligne = "\n" );
        void set_caractere_par_defaut(QString s);
        void set_dictionnaire_par_defaut(QString dico);
        void set_choix_par_defaut(const QStringList & selection);
        void set_textes_out(const textes &textes_out);
        void set_id(const type_id_parametre &id);
        void set_mode_configuration_visibilite(type_mode_configuration_visibilite mode_configuration_visibilite);

        bool configuration_visible() const;
        void inverser_configuration_visibilite();
        bool peut_etre_vide() const;

    protected:
        /** \brief Le nom du paramètre. */
        QString m_nom;

        /** \brief L'aide utilisateur du paramètre. */
        QString m_aide;

        /** \brief Indique si le mode du contenu du paramètre. */
        type_mode_contenu_parametre m_mode_contenu_parametre;

        /** \brief Un pointeur sur la fonction parent. */
        base_fonction * m_fonction_parent;

        /** \brief La valeur du paramètre. */
        textes m_textes_out;

        /** \brief L'identifiant du paramètre. */
        type_id_parametre m_id;

        /** \brief Indique si le paramètre est visible dans la configuration. */
        type_mode_configuration_visibilite m_mode_configuration_visibilite;

        /** \brief Le type d'algorithme utilisé. */
        type_algorithme m_algorithme;

        /** \brief Le type du paramètre. */
        type_type_parametre m_type;
};

#endif // BASE_PARAMETRE_H
