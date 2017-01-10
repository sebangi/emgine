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

OBJECTS_DIR = .obj
MOC_DIR     = .moc

SOURCES += \
        main.cpp\
        src/fenetre_principale.cpp \
        src/projet/projet.cpp \
        src/projet/base_parametre.cpp \
        src/explorateur/noeud_fonction.cpp \
        src/projet/base_fonction.cpp \
        src/fonction/fonction_conversion/fonction_cesar.cpp \
        src/explorateur/base_noeud.cpp \
        src/explorateur/noeud_projet.cpp\
        src/element/base_element.cpp \
        src/fonction_widget/base_fonction_widget.cpp \
        src/element/mot.cpp \
        src/element/texte.cpp \
        src/fonction/fonction_source/fonction_base_source.cpp \
        src/fonction/fonction_source/fonction_source_booleen.cpp \
        src/fonction/fonction_source/fonction_source_entier.cpp \
        src/fonction_widget/selecteur_fonction_dialog.cpp \
        src/fonction_widget/bouton_choix_fonction.cpp \
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
        src/fonction/bibliotheque_fonctions.cpp \
        src/fonction_widget/vue_fonctions.cpp \
        src/projet/fonctions_conteneur.cpp

HEADERS  += \
        entete/fonction/bibliotheque_fonctions.h \
        entete/fonction_widget/bouton_choix_fonction.h \
        entete/compilation/compilateur.h \
        entete/compilation/log_compilation.h \
        entete/compilation/log_widget_item.h \
        entete/compilation/logs_compilation_widget.h \
        entete/define.h \
        entete/element/base_element.h \
        entete/element/ligne.h \
        entete/element/mot.h \
        entete/element/texte.h \
        entete/element/type_element.h \
        entete/explorateur/base_noeud.h \
        entete/explorateur/explorateur.h \
        entete/explorateur/noeud_fonction.h \
        entete/explorateur/noeud_parametre.h \
        entete/explorateur/noeud_projet.h \
        entete/fenetre_principale.h \
        entete/fonction/fonction_conversion/fonction_cesar.h \
        entete/fonction/fonction_sortie/fonction_base_sortie.h \
        entete/fonction/fonction_sortie/fonction_sortie_texte.h \
        entete/fonction/fonction_source/fonction_base_source.h \
        entete/fonction/fonction_source/fonction_source_booleen.h \
        entete/fonction/fonction_source/fonction_source_caractere.h \
        entete/fonction/fonction_source/fonction_source_entier.h \
        entete/fonction/fonction_source/fonction_source_texte.h \
        entete/fonction_widget/base_fonction_widget.h \
        entete/fonction_widget/base_parametre_widget.h \
        entete/fonction_widget/fonction_sortie_texte_widget.h \
        entete/fonction_widget/fonction_source_booleen_widget.h \
        entete/fonction_widget/fonction_source_caractere_widget.h \
        entete/fonction_widget/fonction_source_texte_widget.h \
        entete/projet/base_fonction.h \
        entete/projet/base_parametre.h \
        entete/projet/fonctions_conteneur.h \
        entete/projet/projet.h \
        entete/fonction_widget/selecteur_fonction_dialog.h \
        entete/fonction_widget/vue_fonctions.h

FORMS    += \
    fenetre_principale.ui

DISTFILES += \
    stylesheet.qss

