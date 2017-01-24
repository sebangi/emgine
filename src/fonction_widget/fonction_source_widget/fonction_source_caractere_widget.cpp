#include "entete/fonction_widget/fonction_source_widget/fonction_source_caractere_widget.h"
#include "entete/fonction/fonction_source/fonction_source_caractere.h"
#include <iostream>
#include <QHBoxLayout>

fonction_source_caractere_widget::fonction_source_caractere_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget_avec_text_edit(fonction, parent)
{
    init();
}

void fonction_source_caractere_widget::on_nouveau_texte()
{
    ((fonction_source_caractere*)m_fonction)->set_valeur( get_valeur() );
}

QString fonction_source_caractere_widget::chercher_valeur() const
{
    return ((fonction_source_caractere*)m_fonction)->get_valeur();
}

