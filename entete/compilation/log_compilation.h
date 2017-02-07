#ifndef LOG_COMPILATION_H
#define LOG_COMPILATION_H

/** \file log_compilation.h
 * \brief Fichier de déclaration de la class log_compilation.
 * \author Sébastien Angibaud
 */

#include <QListWidgetItem>
#include <QString>

class objet_selectionnable;

/**
 * \class log_compilation
 * \brief Classe décrivant un message de compilation.
 * \author Sébastien Angibaud
 */
class log_compilation : public QObject
{
        Q_OBJECT

    public:
        /** \enum type_log
         * \brief Type décrivant les différents types de log.
         */
        enum type_log{
            /** \brief Log non typé. */
            LOG_NO_TYPE = QListWidgetItem::UserType,

            /** \brief Log de type information. */
            LOG_INFORMATION,

            /** \brief Log de type erreur. */
            LOG_ERREUR,

            /** \brief Log de type warning. */
            LOG_WARNING,

            /** \brief Log de type succès. */
            LOG_SUCCES,

            /** \brief Log de type important. */
            LOG_IMPORTANT
        };

    public:
        log_compilation( type_log type, QString get_message );
        log_compilation( type_log type, objet_selectionnable* obj, QString get_message );
        log_compilation( const log_compilation& log );

        void informe_supression_selectionnable(objet_selectionnable * obj);

        QString get_message() const;
        objet_selectionnable *get_selectionnable();
        type_log get_type() const;
        QString get_type_string() const;
        QColor get_couleur() const;

    private:
        /** \brief Le type du message. */
        type_log m_type;

        /** \brief Un pointeur sur l'objet associé au message. */
        objet_selectionnable* m_objet;

        /** \brief Le message. */
        QString m_message;
};

#endif // LOG_COMPILATION_H
