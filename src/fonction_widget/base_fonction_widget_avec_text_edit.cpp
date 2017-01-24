#include "entete/fonction_widget/base_fonction_widget_avec_text_edit.h"

#include "entete/fonction_widget/text_edit.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include <iostream>
#include <QHBoxLayout>

base_fonction_widget_avec_text_edit::base_fonction_widget_avec_text_edit(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    // Le init doit être appelé depuis les classes filles
}

void base_fonction_widget_avec_text_edit::init()
{
    QVBoxLayout * lay = new QVBoxLayout();
    lay->setSizeConstraint(QLayout::SetFixedSize);
    m_text_edit = new text_edit();
    m_text_edit->setPlainText( chercher_valeur() );
    lay->addWidget(m_text_edit);

    connect(m_text_edit, SIGNAL(textChanged()), this, SLOT(on_textChanged()));
    m_specialisation_layout->addLayout(lay);
}

void base_fonction_widget_avec_text_edit::on_textChanged()
{
    on_nouveau_texte();

    m_fonction->modifier();

    m_text_edit->updateGeometry();
    int save_width = width();
    adjustSize();
    setFixedWidth(save_width);

    signal_bfw_size_change();
}
