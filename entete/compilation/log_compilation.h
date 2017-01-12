#ifndef LOG_COMPILATION_H
#define LOG_COMPILATION_H

#include <QString>
#include <QListWidgetItem>

class projet;
class base_fonction;
class base_parametre;
class objet_selectionnable;

class log_compilation : public QObject
{
        Q_OBJECT

    public:
        /*!
        \brief Type décrivant les différents types de log.
        */
        enum type_log{
            LOG_NO_TYPE = QListWidgetItem::UserType,
            LOG_INFORMATION,
            LOG_ERREUR,
            LOG_WARNING,
            LOG_SUCCES,
            LOG_IMPORTANT
        };

    public:
        log_compilation( type_log type, QString get_message );
        log_compilation( type_log type, projet* f, QString get_message );
        log_compilation( type_log type, base_fonction* f, QString get_message );
        log_compilation( type_log type, base_parametre* f, QString get_message );
        log_compilation( const log_compilation& log );

        void informe_supression_selectionnable(objet_selectionnable * obj);

        QString get_message() const;
        projet *get_projet();
        base_fonction *get_fonction();
        base_parametre *get_parametre();
        objet_selectionnable *get_selectionnable();

        type_log get_type() const;
        QString get_type_string() const;
        QColor get_couleur() const;

    private slots:
        void on_externe_supprimer_fonction(base_fonction *f);

    private:
        type_log m_type;
        projet* m_projet;
        base_fonction* m_fonction;
        base_parametre* m_parametre;
        QString m_message;
};

#endif // LOG_COMPILATION_H
