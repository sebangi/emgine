#ifndef BASE_PARAMETRE_H
#define BASE_PARAMETRE_H

#include <QString>
#include <QXmlStreamWriter>
#include "entete/element/base_element.h"
#include "entete/element/type_element.h"
#include "entete/element/textes.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/fonction/define_parametre.h"

class base_fonction;
class noeud_parametre;
class logs_compilation_widget;

/**
 \brief Classe décrivant un parametre d'une fonction.
 \author Sébastien Angibaud
*/
class base_parametre : public fonctions_conteneur
{
        Q_OBJECT

    public:

        enum type_mode_configuration_visibilite
        {
            CONFIGURATION_INVISIBLE = 0,
            CONFIGURATION_VISIBLE
        };


        enum type_mode_contenu_parametre
        {
            CONTENU_PARAM_VIDE_IMPOSSIBLE = 0,
            CONTENU_PARAM_VIDE_POSSIBLE
        };

        /** \brief Enumération décrivant les différents algorithmes pour l'excution des paramètres. */
        enum type_algorithme{
            ALGO_AUCUN = 0,
            ALGO_PMIPL,
            ALGO_LIPL
        };

    public:
        base_parametre( objet_selectionnable * parent, QString nom, QString aide,
                        type_mode_contenu_parametre mode_contenu_parametre,
                        type_mode_configuration_visibilite dans_configuration, type_algorithme algorithme);
        ~base_parametre();

        void sauvegarder( QXmlStreamWriter & stream ) const;
        QString get_nom() const;        
        QString get_titre() const;
        QString get_valeur_courte() const;
        QString get_aide() const;
        QString get_aide_algorithme() const;

        bool est_parametre() const;

        base_fonction *get_fonction_parent() const;
        bool is_requis() const;

        void set_booleen_par_defaut( bool valeur );
        void set_texte_par_defaut( QString texte, QString separ_caractere = "", QString separ_mot = " ", QString separ_ligne = "\n" );
        void set_caractere_par_defaut(QString s);
        void set_choix_par_defaut(const QStringList & selection);

        const textes& get_textes_out() const;

        void set_textes_out(const textes &textes_out);
        void set_id(const type_id_parametre &value);

        bool est_valide(logs_compilation_widget * vue_logs);

        void charger( QXmlStreamReader & xml );

        bool configuration_visible() const;
        void inverser_configuration_visibilite();
        void set_mode_configuration_visibilite(type_mode_configuration_visibilite visible);

        bool peut_etre_vide() const;

        type_type_parametre get_type() const;

    protected:
        /** \brief Le nom de la fonction. */
        QString m_nom;

        /** \brief L'aide utilisateur du parametre. */
        QString m_aide;

        /** \brief Indique si le parametre est requis. */
        type_mode_contenu_parametre m_mode_contenu_parametre;

        /** \brief La fonction parent. */
        base_fonction * m_fonction_parent;

        /** \brief La valeur réelle du parametre. */
        textes m_textes_out;

        /** \brief L'identifiant du paramètre. */
        type_id_parametre m_id;

        /** \brief Indique si le paramètre doit figurer dans la configuration. */
        type_mode_configuration_visibilite m_mode_configuration_visibilite;

        /** \brief Le type d'algorithme utilisé. */
        type_algorithme m_algorithme;

        type_type_parametre m_type;
};

#endif // BASE_PARAMETRE_H
