#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/**
 * \file configuration.h
 * \brief Fichier de déclaration de la classe configuration.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/define_parametre.h"

#include <QString>

#include <map>

class base_fonction;

/** \brief Type représentant une clé de configuration, i.e. une paire (fonction/id_parametre). */
typedef std::pair< base_fonction *, type_id_parametre > type_cle_configuration;


/**
 * \class configuration
 * \brief Classe décrivant un configuration lors d'une exécution. Pour un texte donné, une configuration correspond à la valeur des paramètres des fonctions.
 * \author Sébastien Angibaud
 */
class configuration : public std::map< type_cle_configuration, QString >
{

};

#endif // CONFIGURATION_H
