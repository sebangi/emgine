#-------------------------------------------------
#
# Project created by QtCreator 2014-04-02T20:58:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emgine
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR     = .moc

SOURCES += \
        main.cpp\
	src/fenetre_principale.cpp \
        src/old_texte.cpp \
        src/element.cpp \
        src/projet.cpp \
        src/parametre/base_parametre.cpp \
        src/explorateur/noeud_fonction.cpp \
        src/fonction/base_fonction.cpp \
    	src/fonction/fonction_conversion/fonction_forcer_casse.cpp \
    	src/fonction/fonction_conversion/fonction_retirer_caracteres.cpp \
    	src/fonction/fonction_conversion/fonction_retrait_accents.cpp \
    	src/fonction/fonction_conversion/fonction_cesar.cpp \
    	src/fonction/fonction_conversion/fonction_ecrire_en_morse.cpp \
    	src/fonction/fonction_conversion/fonction_lire_morse.cpp \
    	src/fonction/fonction_conversion/fonction_frequence.cpp \
    	src/fonction/fonction_conversion/fonction_sur_ligne.cpp \
    	src/fonction/fonction_conversion/fonction_inverser_lignes.cpp \
    	src/fonction/fonction_conversion/fonction_substitution.cpp \
    	src/fonction/fonction_conversion/fonction_inverser_phrases.cpp \
    	src/fonction/fonction_conversion/fonction_composee.cpp \    
	src/explorateur/base_noeud.cpp \
        src/explorateur/noeud_projet.cpp\
        src/element/base_element.cpp \
        src/fonction_widget/base_fonction_widget.cpp \
        src/element/mot.cpp \
        src/element/texte.cpp \
        src/fonction/fonction_source/fonction_base_source.cpp \
        src/fonction/fonction_source/fonction_source_booleen.cpp \
        src/fonction/fonction_source/fonction_source_entier.cpp \
        src/selecteur_fonction_dialog.cpp \
        src/bouton_choix_fonction.cpp \
    	src/explorateur/noeud_parametre.cpp \
    	src/fonction_widget/base_parametre_widget.cpp \
    src/explorateur/explorateur.cpp \
    src/fonction_widget/fonction_source_booleen_widget.cpp \
    src/fonction/fonction_source/fonction_source_texte.cpp \
    src/fonction_widget/fonction_source_texte_widget.cpp \
    src/compilation/compilateur.cpp \
    src/fonction/fonction_source/fonction_source_caractere.cpp \
    src/fonction_widget/fonction_source_caractere_widget.cpp \
    src/compilation/log_compilation.cpp \
    src/compilation/logs_compilation_widget.cpp \
    src/compilation/log_widget_item.cpp \
    src/element/ligne.cpp \
    src/fonction/fonction_sortie/fonction_sortie_texte.cpp \
    src/fonction/fonction_sortie/fonction_base_sortie.cpp \
    src/fonction_widget/fonction_sortie_texte_widget.cpp \
    src/bibliotheque_fonctions.cpp \
    src/vue_fonction/vue_fonctions.cpp \
    src/fonctions_conteneur.cpp
    	
HEADERS  += \
	fenetre_principale.h \
        old_texte.h \
    	texte_edition_dialog.h \
    	element.h \
    	texte_edit.h \
	projet.h \
        parametre/base_parametre.h \
        fonction/base_fonction.h \
    	fonction/fonction_conversion/fonction_forcer_casse.h \
    	fonction/fonction_conversion/fonction_retirer_caracteres.h \
    	fonction/fonction_conversion/fonction_retrait_accents.h \
    	fonction/fonction_conversion/fonction_cesar.h \
    	fonction/fonction_conversion/fonction_ecrire_en_morse.h \
    	fonction/fonction_conversion/fonction_lire_morse.h \
    	fonction/fonction_conversion/fonction_frequence.h \
    	fonction/fonction_conversion/fonction_sur_ligne.h \
    	fonction/fonction_conversion/fonction_inverser_lignes.h \
    	fonction/fonction_conversion/fonction_substitution.h \
    	fonction/fonction_conversion/fonction_inverser_phrases.h \
        fonction/fonction_conversion/fonction_composee.h \
        fonction/fonction_source/fonction_base_source.h \
        fonction/fonction_source/fonction_source_booleen.h \
	explorateur/base_noeud.h \
    	explorateur/noeud_projet.h \
        explorateur/noeud_fonction.h \
        element/base_element.h \
        element/type_element.h \
        fonction_widget/base_fonction_widget.h \
        element/mot.h \
        element/texte.h \
    	fonction/fonction_source/fonction_source_entier.h \
    	selecteur_fonction_dialog.h \
    	bouton_choix_fonction.h \
    	explorateur/noeud_parametre.h \
    	explorateur/explorateur.h \
    	fonction_widget/base_parametre_widget.h \
    	fonction_widget/fonction_source_booleen_widget.h \
    	fonction/fonction_source/fonction_source_texte.h \
    	fonction_widget/fonction_source_texte_widget.h \
    	compilation/compilateur.h \
    	fonction/fonction_source/fonction_source_caractere.h \
    	fonction_widget/fonction_source_caractere_widget.h \
    compilation/log_compilation.h \
    compilation/logs_compilation_widget.h \
    compilation/log_widget_item.h \
    element/ligne.h \
    fonction/fonction_sortie/fonction_sortie_texte.h \
    fonction/fonction_sortie/fonction_base_sortie.h \
    fonction_widget/fonction_sortie_texte_widget.h \
    bibliotheque_fonctions.h \
    define.h \
    vue_fonction/vue_fonctions.h \
    fonctions_conteneur.h

FORMS    += \
    fenetre_principale.ui

DISTFILES += \
    stylesheet.qss

