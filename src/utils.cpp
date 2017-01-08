#include "utils.h"
#include <iostream>
#include <sstream>
#include "element.h"

/*! --------------------------------------------------------------------------------------
 \file Implémentation de fonctions diverses.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Découpe un string en un tableau de lignes.
 \param s La chaine à découper.
 \param delim Le caractère délimiteur.
 \param elems Le tableau de lignes.
*/
void mon_split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Découpe un string suivant un délimiteur et retourne ainsi un tableau de string.
 \param s La chaine à découper.
 \param delim Le caractère délimiteur.
*/
std::vector<std::string> utils::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    mon_split(s, delim, elems);
    return elems;
}

/*! --------------------------------------------------------------------------------------
 \brief Charge un texte à partir d'un TextEdit.
 \param t Le texte à initialiser.
 \param edit_text L'EditText source.
*/
void utils::charger_texte(old_texte &t, const QTextEdit * edit_text)
{
    t.effacer();

    QString s1 = edit_text->toPlainText().toUtf8();
    std::string str = s1.toStdString();
    t = old_texte(str);
}

/*! --------------------------------------------------------------------------------------
 \brief Charge un TextEdit à partir d'un texte.
 \param t Le texte source.
 \param edit_text L'EditText à initialiser.
*/
void utils::charger_edittext(const old_texte &t, QTextEdit * edit_text)
{
    edit_text->clear();
    old_texte::element_iterator it;
    QString str;

    for ( it = t.begin(); it != t.end(); ++it )
    {
        if ( it->get_type() != element::retour_ligne )
            str = str + QString::fromStdString(it->to_string());
        else
        {
            edit_text->append(str);
            str = QString("");
        }
    }

    if ( str.size() != 0 )
        edit_text->append(str);
}
