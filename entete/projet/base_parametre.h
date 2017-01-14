#ifndef BASE_PARAMETRE_H
#define BASE_PARAMETRE_H

#include <QString>
#include <QXmlStreamWriter>
#include "entete/element/base_element.h"
#include "entete/element/type_element.h"
#include "entete/element/texte.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/define.h"

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
        base_parametre(objet_selectionnable * parent, QString nom, QString aide, bool requis);
        ~base_parametre();

        void sauvegarder( QXmlStreamWriter & stream ) const;
        QString get_nom() const;        
        QString get_titre() const;
        QString get_valeur_courte() const;
        QString get_aide() const;
        type_element get_type() const;

        base_fonction *get_fonction_parent() const;
        bool is_requis() const;

        void set_booleen_par_defaut( bool valeur );
        void set_texte_par_defaut( QString texte, QString separ_caractere = "", QString separ_mot = " ", QString separ_ligne = "\n" );
        void set_caractere_par_defaut(QString s);

        const texte& get_texte_out() const;

        void set_texte_out(const texte &texte_out);
        void set_id(const type_id_parametre &value);

        bool est_valide(logs_compilation_widget * vue_logs);

        void charger( QXmlStreamReader & xml );

    private:
        void charger_fonctions(QXmlStreamReader & xml );
        void charger_fonction(QXmlStreamReader & xml );

    protected:
        /** \brief Le nom de la fonction. */
        QString m_nom;

        /** \brief L'aide utilisateur du parametre. */
        QString m_aide;

        /** \brief Indique si le parametre est requis. */
        bool m_requis;

        /** \brief Le type du paramètre. */
        type_element m_type;

        /** \brief La fonction parent. */
        base_fonction * m_fonction_parent;

        /** \brief La valeur réelle du parametre. */
        texte m_texte_out;

        /** \brief L'identifiant du paramètre. */
        type_id_parametre m_id;
};

#endif // BASE_PARAMETRE_H
