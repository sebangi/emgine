#include "texte_edit.h"
#include "texte_edition_dialog.h"
#include "old_texte.h"
#include "utils.h"
#include <QFocusEvent>


/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe texte_edit.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
*/
texte_edit::texte_edit()
{
}

/*! --------------------------------------------------------------------------------------
 \brief Redéfinition de la gestion de l'événement mouseRelease.
*/
void texte_edit::mouseReleaseEvent(QMouseEvent *event)
{
   old_texte t;
   utils::charger_texte( t, this );

   texte_edition_dialog *dialog = new texte_edition_dialog(this, t);

   if ( dialog->exec() == QDialog::Accepted )
    utils::charger_edittext(dialog->get_texte(), this);
}
