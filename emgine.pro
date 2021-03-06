#-------------------------------------------------
#
# Project created by QtCreator 2014-04-02T20:58:24
#
#-------------------------------------------------

QT      += core
QT      += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emgine
TEMPLATE = app

DESTDIR = ../emgine
OBJECTS_DIR = .obj
MOC_DIR     = .moc

SOURCES += \
        main.cpp \
        src/compilation/compilateur.cpp \
        src/compilation/log_compilation.cpp \
        src/compilation/logs_compilation_widget.cpp \
        src/compilation/log_widget_item.cpp \
        src/element/base_element.cpp \
        src/element/ligne.cpp \
        src/element/mot.cpp \
        src/element/texte.cpp \
        src/explorateur/base_noeud.cpp \
        src/explorateur/explorateur.cpp \
        src/explorateur/noeud_fonction.cpp \
        src/explorateur/noeud_fonctions_conteneur.cpp \
        src/explorateur/noeud_parametre.cpp \
        src/explorateur/noeud_projet.cpp\
        src/fenetre_principale.cpp \
        src/fonction/bibliotheque_fonctions.cpp \
        src/fonction/fonction_conversion/fonction_cesar.cpp \
        src/fonction/fonction_sortie/fonction_base_sortie.cpp \
        src/fonction/fonction_sortie/fonction_sortie_texte.cpp \
        src/fonction/fonction_sortie/fonction_sortie_frequence.cpp \
        src/fonction/fonction_source/fonction_base_source.cpp \
        src/fonction/fonction_source/fonction_source_booleen.cpp \
        src/fonction/fonction_source/fonction_source_caractere.cpp \
        src/fonction/fonction_source/fonction_source_entier.cpp \
        src/fonction/fonction_source/fonction_source_texte.cpp \
        src/fonction_widget/base_fonction_widget.cpp \
        src/fonction_widget/base_parametre_widget.cpp \
        src/fonction_widget/bouton_choix_fonction.cpp \
        src/fonction_widget/fonction_sortie_widget/fonction_sortie_texte_widget.cpp \
        src/fonction_widget/fonction_source_widget/fonction_source_booleen_widget.cpp \
        src/fonction_widget/fonction_source_widget/fonction_source_caractere_widget.cpp \
        src/fonction_widget/fonction_source_widget/fonction_source_texte_widget.cpp \
        src/fonction_widget/selecteur_fonction_dialog.cpp \
        src/fonction_widget/vue_fonctions.cpp \
        src/parametre/parametre_choix.cpp \
        src/projet/base_fonction.cpp \
        src/projet/base_parametre.cpp \
        src/projet/fonctions_conteneur.cpp \
        src/projet/objet_selectionnable.cpp \
        src/projet/projet.cpp \
        src/element/textes.cpp \
        src/compilation/configuration.cpp \
        src/fonction_widget/fonction_sortie_widget/texte_widget_item.cpp \
        src/fonction_widget/base_fonction_widget_avec_text_edit.cpp \
        src/fonction_widget/fonction_sortie_widget/liste_texte_widget.cpp \
        src/fonction_widget/parametre_aide_message_box.cpp \
        src/fonction/fonction_source/fonction_source_choix.cpp \
        src/fonction_widget/fonction_source_widget/fonction_source_choix_widget.cpp \
        src/fonction/fonction_source/fonction_source_permutation.cpp \
        src/fonction_widget/text_edit.cpp \
        src/fonction/fonction_source/fonction_source_fichier_texte.cpp \
        src/fonction_widget/fonction_source_widget/fonction_source_fichier_texte_widget.cpp \
    src/fonction/fonction_sortie/fonction_sortie_indice_coincidence.cpp \
    src/element/frequence.cpp \
    src/fonction_widget/fonction_sortie_widget/fonction_base_sortie_widget.cpp \
    src/fonction/fonction_conversion/fonction_formatage.cpp \
    src/fonction/fonction_sortie/fonction_sortie_analyse_ligne.cpp \
    entete/dictionnaire/impl/alpha_vector.tpp \
    src/dictionnaire/cle_de_mot.cpp \
    src/dictionnaire/comptage_mot.cpp \
    src/dictionnaire/dictionnaire.cpp \
    src/dictionnaire/mot_binaire.cpp \
    src/fonction/fonction_source/fonction_source_dictionnaire.cpp \
    src/fonction_widget/fonction_source_widget/fonction_source_dictionnaire_widget.cpp \
    src/fonction/fonction_conversion/fonction_selection_selon_dictionnaire.cpp \
    src/fonction/fonction_conversion/fonction_anagramme.cpp \
    src/dictionnaire/lettre_dictionnaire.cpp \
    src/fonction_widget/fonction_source_widget/fonction_source_entier_widget.cpp \
    src/fonction/fonction_conversion/fonction_entier_en_chiffre_romain.cpp \
    src/fonction/algorithme/algo_IPL.cpp \
    src/fonction/fonction_conversion/fonction_ajout_espace_selon_dictionnaire.cpp \
    src/fonction/fonction_conversion/fonction_fusion.cpp \
    src/fonction/fonction_conversion/fonction_substitution.cpp \
    src/fonction/fonction_conversion/fonction_ecriture_morse.cpp \
    src/fonction/fonction_conversion/fonction_lecture_morse.cpp \
    src/fonction/fonction_conversion/fonction_choisir_separateur.cpp \
    src/fonction/fonction_conversion/fonction_transposition.cpp \
    src/fonction/fonction_conversion/fonction_inversion.cpp \
    src/fonction/fonction_conversion/fonction_concatenation.cpp \
    src/fonction/fonction_conversion/fonction_rotation.cpp \
    src/fonction/fonction_conversion/fonction_scission.cpp \
    src/fonction/fonction_conversion/fonction_ecriture_en_diagonale.cpp \
    src/element/liste_choix.cpp \
    src/fonction/fonction_conversion/fonction_inversion_en_diagonale.cpp \
    src/fonction/fonction_conversion/fonction_lecture_braille.cpp \
    src/fonction/fonction_conversion/fonction_expression_reguliere.cpp \
    src/fonction/fonction_source/fonction_source_ensemble_sources.cpp \
    src/fonction/fonction_conversion/fonction_ordonnancement.cpp \
    src/fonction/fonction_conversion/fonction_patron.cpp

HEADERS  += \
        entete/compilation/compilateur.h \
        entete/compilation/log_compilation.h \
        entete/compilation/logs_compilation_widget.h \
        entete/compilation/log_widget_item.h \
        entete/define.h \
        entete/element/base_element.h \
        entete/element/ligne.h \
        entete/element/mot.h \
        entete/element/texte.h \
        entete/element/type_element.h \
        entete/explorateur/base_noeud.h \
        entete/explorateur/explorateur.h \
        entete/explorateur/noeud_fonction.h \
        entete/explorateur/noeud_fonctions_conteneur.h \
        entete/explorateur/noeud_parametre.h \
        entete/explorateur/noeud_projet.h \
        entete/fenetre_principale.h \
        entete/fonction/bibliotheque_fonctions.h \
        entete/fonction/fonction_conversion/fonction_cesar.h \
        entete/fonction/fonction_sortie/fonction_base_sortie.h \
        entete/fonction/fonction_sortie/fonction_sortie_texte.h \
        entete/fonction/fonction_sortie/fonction_sortie_frequence.h \
        entete/fonction/fonction_source/fonction_base_source.h \
        entete/fonction/fonction_source/fonction_source_booleen.h \
        entete/fonction/fonction_source/fonction_source_caractere.h \
        entete/fonction/fonction_source/fonction_source_entier.h \
        entete/fonction/fonction_source/fonction_source_texte.h \
        entete/fonction_widget/base_fonction_widget.h \
        entete/fonction_widget/base_parametre_widget.h \
        entete/fonction_widget/bouton_choix_fonction.h \
        entete/fonction_widget/fonction_sortie_widget/fonction_sortie_texte_widget.h \
        entete/fonction_widget/fonction_source_widget/fonction_source_booleen_widget.h \
        entete/fonction_widget/fonction_source_widget/fonction_source_caractere_widget.h \
        entete/fonction_widget/fonction_source_widget/fonction_source_texte_widget.h \
        entete/fonction_widget/selecteur_fonction_dialog.h \
        entete/fonction_widget/vue_fonctions.h \
        entete/parametre/parametre_choix.h \
        entete/projet/base_fonction.h \
        entete/projet/base_parametre.h \
        entete/projet/fonctions_conteneur.h \
        entete/projet/objet_selectionnable.h \
        entete/projet/projet.h \
        entete/element/textes.h \
        entete/compilation/configuration.h \
        entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h \
        entete/fonction_widget/text_edit.h \
        entete/fonction_widget/base_fonction_widget_avec_text_edit.h \
        entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h \
        entete/fonction_widget/parametre_aide_message_box.h \
        entete/fonction/fonction_source/fonction_source_choix.h \
        entete/fonction_widget/fonction_source_widget/fonction_source_choix_widget.h \
        entete/fonction/fonction_source/fonction_source_permutation.h \
        entete/fonction/define_fonction.h \
        entete/fonction/define_parametre.h \
        entete/fonction/fonction_source/fonction_source_fichier_texte.h \
        entete/fonction_widget/fonction_source_widget/fonction_source_fichier_texte_widget.h \
    entete/fonction/fonction_sortie/fonction_sortie_indice_coincidence.h \
    entete/element/frequence.h \
    entete/fonction_widget/fonction_sortie_widget/fonction_base_sortie_widget.h \
    entete/fonction/fonction_conversion/fonction_formatage.h \
    entete/fonction/fonction_sortie/fonction_sortie_analyse_ligne.h \
    entete/fonction/fonction_source/fonction_source_dictionnaire.h \
    entete/fonction_widget/fonction_source_widget/fonction_source_dictionnaire_widget.h \
    entete/dictionnaire/alpha_vector.h \
    entete/dictionnaire/cle_de_mot.h \
    entete/dictionnaire/comptage_mot.h \
    entete/dictionnaire/dictionnaire.h \
    entete/dictionnaire/indice_lettre.h \
    entete/dictionnaire/mot_binaire.h \
    entete/fonction/fonction_conversion/fonction_selection_selon_dictionnaire.h \
    entete/fonction/fonction_conversion/fonction_anagramme.h \
    entete/dictionnaire/lettre_dictionnaire.h \
    entete/fonction_widget/fonction_source_widget/fonction_source_entier_widget.h \
    entete/fonction/fonction_conversion/fonction_entier_en_chiffre_romain.h \
    entete/fonction/algorithme/algo_IPL.h \
    entete/fonction/fonction_conversion/fonction_ajout_espace_selon_dictionnaire.h \
    entete/fonction/fonction_conversion/fonction_fusion.h \
    entete/fonction/fonction_conversion/fonction_substitution.h \
    entete/fonction/fonction_conversion/fonction_ecriture_morse.h \
    entete/fonction/fonction_conversion/fonction_lecture_morse.h \
    entete/fonction/fonction_conversion/fonction_choisir_separateur.h \
    entete/fonction/fonction_conversion/fonction_transposition.h \
    entete/fonction/fonction_conversion/fonction_inversion.h \
    entete/fonction/fonction_conversion/fonction_concatenation.h \
    entete/fonction/fonction_conversion/fonction_rotation.h \
    entete/fonction/fonction_conversion/fonction_scission.h \
    entete/fonction/fonction_conversion/fonction_ecriture_en_diagonale.h \
    entete/element/liste_choix.h \
    entete/fonction/fonction_conversion/fonction_inversion_en_diagonale.h \
    entete/fonction/fonction_conversion/fonction_lecture_braille.h \
    entete/fonction/fonction_conversion/fonction_expression_reguliere.h \
    entete/fonction/fonction_source/fonction_source_ensemble_sources.h \
    entete/fonction/fonction_conversion/fonction_ordonnancement.h \
    entete/fonction/fonction_conversion/fonction_patron.h

FORMS    += \
    fenetre_principale.ui

TRANSLATIONS = emgine_en.ts

DISTFILES += \
    stylesheet.qss \
    TODO.txt \
    Doxyfile \
    stylesheet.qss

RESOURCES += \
    ressources.qrc

