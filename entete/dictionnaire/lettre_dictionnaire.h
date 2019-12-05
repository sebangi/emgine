#ifndef LETTRE_DICTIONNAIRE_H
#define LETTRE_DICTIONNAIRE_H

#include <vector>
#include <QObject>

class lettre_dictionnaire : public QObject
{
        Q_OBJECT

public:
    typedef std::vector< lettre_dictionnaire *> type_tab_lettres;

public:
    lettre_dictionnaire();
    ~lettre_dictionnaire();

    lettre_dictionnaire * get_suivant( int pos );
    lettre_dictionnaire * suivant( int pos );
    void set_est_mot();
    bool est_mot();

private:
    bool m_est_mot;
    type_tab_lettres m_suivants;
};

#endif // LETTRE_DICTIONNAIRE_H
