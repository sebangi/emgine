#ifndef FONCTION_SOURCE_ENSEMBLE_TEXTE_H
#define FONCTION_SOURCE_ENSEMBLE_TEXTE_H

#include "entete/fonction/fonction_source/fonction_base_source.h"

/**
 * \class fonction_source_ensemble_sources
 * \brief Classe décrivant une fonction source ajoutant un ensemble_sources.
 * \author Sébastien Angibaud
 */
class fonction_source_ensemble_sources : public fonction_base_source
{
    public:
        fonction_source_ensemble_sources(fonctions_conteneur * conteneur);
        ~fonction_source_ensemble_sources();

        base_fonction_widget *generer_fonction_widget();
        void initialisation_par_defaut();
        void executer( compilateur & compil, textes & textes_in, textes & textes_out );
        QString get_valeur_courte() const;
        QString get_string_valeur() const;
        void set_string_valeur(const QString & nom_fichier);

    private:
        bool est_valide(logs_compilation_widget * vue_logs);
};

#endif // FONCTION_SOURCE_ENSEMBLE_TEXTE_H
