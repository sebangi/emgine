#ifndef base_fonction_widget_avec_text_edit_H
#define base_fonction_widget_avec_text_edit_H

/** \file base_fonction_widget_avec_text_edit.h
 * \brief Fichier de déclaration de la classe base_fonction_widget_avec_text_edit.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/fonction_widget/text_edit.h"

/**
 * \class base_fonction_widget_avec_text_edit
 * \brief Classe décrivant un widget affichant une fonction et nécessitant un text_edit.
 * \author Sébastien Angibaud
 */
class base_fonction_widget_avec_text_edit : public base_fonction_widget
{
        Q_OBJECT

    public:
        base_fonction_widget_avec_text_edit( base_fonction* fonction, QWidget *parent = 0 );

    protected:
        void init();
        /** --------------------------------------------------------------------------------------
         * \brief Fonction retournant la valeur du texte.
         * \return La valeur du texte au format QString.
         */
        QString get_valeur() const { return m_text_edit->toPlainText(); }

        void informer_verrouillage_change();

    private:
        /** --------------------------------------------------------------------------------------
         * \brief Fonction virtuelle pure appelée lorsque le texte est modifié.
         */
        virtual void on_nouveau_texte() = 0;

        /** --------------------------------------------------------------------------------------
         * \brief Fonction virtuelle pure retournant la valeur de la fonction associée.
         * \return La valeur de la fonction associée au format QString.
         */
         virtual QString chercher_valeur() const = 0;

    private slots :
        void on_textChanged();

    protected:
        /** \brief Un pointeur sur le widget text_edit. */
        text_edit * m_text_edit;
};

#endif // base_fonction_widget_avec_text_edit_H
