#include "entete/fonction_widget/fonction_sortie_texte_widget.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include <iostream>
#include <QHBoxLayout>

fonction_sortie_texte_widget::fonction_sortie_texte_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    init();
}

void fonction_sortie_texte_widget::set_texte(const texte &texte_in)
{
    m_text_edit->setPlainText( texte_in.to_string_lisible() );
}

void fonction_sortie_texte_widget::on_externe_fst_texte_modifie()
{
    m_text_edit->setPlainText( ((fonction_sortie_texte*)m_fonction)->get_texte().to_string_lisible() );
}

void fonction_sortie_texte_widget::init()
{
    QHBoxLayout * lay = new QHBoxLayout();

    m_text_edit = new QPlainTextEdit();
    m_text_edit->setReadOnly(true);
    m_text_edit->setPlainText( ((fonction_sortie_texte*)m_fonction)->get_texte().to_string_lisible() );
    m_text_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lay->addWidget(m_text_edit);

    m_specialisation_layout->addLayout(lay);

    connect((fonction_sortie_texte*)m_fonction, SIGNAL(signal_fst_texte_modifie()), this, SLOT(on_externe_fst_texte_modifie()));
}


