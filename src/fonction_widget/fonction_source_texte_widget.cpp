#include "entete/fonction_widget/fonction_source_texte_widget.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include <iostream>
#include <QHBoxLayout>

fonction_source_texte_widget::fonction_source_texte_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    init();
}

void fonction_source_texte_widget::init()
{
    QHBoxLayout * lay = new QHBoxLayout();

    m_text_edit = new QPlainTextEdit();
    m_text_edit->setPlainText( ((fonction_source_texte*)m_fonction)->get_valeur() );
    m_text_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lay->addWidget(m_text_edit);

    connect(m_text_edit, SIGNAL(textChanged()), this, SLOT(on_textChanged()));

    m_parametre_layout->addLayout(lay);
}

void fonction_source_texte_widget::on_textChanged()
{
    ((fonction_source_texte*)m_fonction)->set_valeur( m_text_edit->toPlainText() );
}

