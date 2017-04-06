#ifndef FONCTION_LECTURE_BRAILLE_H
#define FONCTION_LECTURE_BRAILLE_H

/** \file fonction_lecture_braille.h
 * \brief Fichier de déclaration de la classe fonction_lecture_braille.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

#include <map>

class base_element;

/**
 * \class fonction_lecture_braille
 * \brief Classe décrivant une fonction réalisant la lecture en braille d'un texte.
 * \author Sébastien Angibaud
 */
class fonction_lecture_braille : public base_fonction
{
    private:
        typedef QString type_element_braille;
        typedef std::map<QString, QString> type_braille_conversion;

    public:
        fonction_lecture_braille(fonctions_conteneur * conteneur);

        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        void initialisation_par_defaut();

    private:
        void execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out );
        bool est_valide(logs_compilation_widget * vue_logs);
        QString calcul_lettre(const type_element_braille & e) const;

    private:
        static type_braille_conversion s_braille_conversion;
};

#endif // FONCTION_LECTURE_BRAILLE_H
