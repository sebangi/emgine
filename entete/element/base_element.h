#ifndef BASE_ELEMENT_H
#define BASE_ELEMENT_H

#include "type_element.h"
#include <QString>

class base_element
{
    public:
        base_element();
        base_element( bool valeur );
        base_element( int valeur );
        base_element( QChar valeur );
        base_element( QCharRef valeur );
        base_element( QString valeur );

        type_element get_type() const;
        bool get_booleen() const;
        int get_entier() const;
        QChar get_caractere() const;
        QString to_string() const;

        bool operator <(const base_element& e) const;

    private:
        type_element m_type;

        bool m_booleen;
        int m_entier;
        QChar m_caractere;
        QString m_string;
};

#endif // BASE_ELEMENT_H
