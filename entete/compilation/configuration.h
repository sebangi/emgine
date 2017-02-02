#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "entete/fonction/define_parametre.h"
#include <map>
#include <QString>

class base_fonction;

typedef std::pair< base_fonction *, type_id_parametre > type_cle_configuration;

class configuration : public std::map< type_cle_configuration, QString >
{

};

#endif // CONFIGURATION_H
