#include "element/mot.h"

mot::mot()
    : vector<base_element>()
{

}

mot::mot(const QString &valeur)
{
    base_element e(valeur);

    push_back(e);
}

QString mot::to_string() const
{
    QString result;

    for ( int i = 0; i < size(); ++i )
        result += this->at(i).to_string();

    return result;
}

