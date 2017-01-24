#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"

#include "entete/element/texte.h"

liste_texte_widget::liste_texte_widget()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setObjectName("ListeTexte");
    setWrapping(false);
    setMinimumHeight(20);
    setMaximumHeight(400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

QSize liste_texte_widget::sizeHint() const
{
    return minimumSizeHint();
}

QSize liste_texte_widget::minimumSizeHint() const
{
    int height = 0;
    for ( int i = 0; i != count(); ++i )
        height += item(i)->sizeHint().height();

    return QSize(maximumWidth(), height);
}
