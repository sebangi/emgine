#include "entete/fonction_widget/fonction_source_widget/fonction_source_caractere_widget.h"
#include "entete/fonction/fonction_source/fonction_source_caractere.h"
#include <iostream>
#include <QHBoxLayout>

fonction_source_caractere_widget::fonction_source_caractere_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    init();
}

void fonction_source_caractere_widget::init()
{
    QHBoxLayout * lay = new QHBoxLayout();

    m_text_edit = new QTextEdit();
    m_text_edit->setLineWrapMode(QTextEdit::NoWrap);
    m_text_edit->setText( ((fonction_source_caractere*)m_fonction)->get_valeur() );
    m_text_edit->setMinimumHeight(40);

    m_text_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lay->addWidget(m_text_edit);

    connect(m_text_edit, SIGNAL(textChanged()), this, SLOT(on_textChanged()));

    m_specialisation_layout->addLayout(lay);
}

void fonction_source_caractere_widget::on_textChanged()
{
    ((fonction_source_caractere*)m_fonction)->set_valeur( m_text_edit->toPlainText() );
    m_fonction->modifier();
}

