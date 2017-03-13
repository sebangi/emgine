/** \file base_fonction.cpp
 * \brief Fichier d'implémentation de la classe base_fonction.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/fonction/bibliotheque_fonctions.h"
#include "entete/fonction/fonction_source/fonction_base_source.h"
#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/projet/base_parametre.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la fonctipon base_fonction.
 * \param parent Un pointeur sur le fonctions_conteneur parent.
 * \param type Le type de la fonction.
 */
base_fonction::base_fonction(fonctions_conteneur * parent, type_fonction type)
    : objet_selectionnable(parent), m_nom("fonction inconnue"), m_type(type), m_id(fonction_indefini),
      m_conteneur(parent), m_niveau_visibilite(1), m_max_niveau_visibilite(1),
      m_niveau_visibilite_avant_desactivation(1)
{
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe base_fonction.
 */
base_fonction::~base_fonction()
{
    for ( parametres_iterateur it = m_parametres.begin(); it != m_parametres.end(); ++it )
        delete it->second;
    m_parametres.clear();

    if ( s_objet_courant == this )
        deselectionner();

    emit signal_destruction_fonction(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise par défaut la fonction.
 */
void base_fonction::initialisation_par_defaut()
{
    // Rien à faire par défaut dans cette classe mère.
}

/** --------------------------------------------------------------------------------------
 * \brief Génère et retourne le texte d'info-bulle.
 * \return Le texte à afficher dans l'info bulle.
 */
QString base_fonction::get_info_bulle() const
{
    QString resultat = bibliotheque_fonctions::get_aide( m_id );

    if ( ! m_parametres.empty() )
    {
        resultat += "\n\nParamètre";
        if ( m_parametres.size() > 1 )
            resultat += "s";
        resultat += " :";

        parametres_const_iterateur it;
        for ( it = m_parametres.begin(); it != m_parametres.end(); ++it )
            resultat += "\n\t" + it->second->get_nom() + " :\n\t\t" + it->second->get_aide() + "\n";
    }

    return resultat;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est une fonction.
 * \return \b True.
 */
bool base_fonction::est_fonction() const
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Sauvegarde la fonction dans un flux donné.
 * \param stream Le flux Xml dans lequel écrire.
 */
void base_fonction::sauvegarder( QXmlStreamWriter & stream ) const
{
    stream.writeStartElement("fonction");
    stream.writeTextElement("id", QString::number(m_id));
    stream.writeTextElement("nom", m_nom);
    stream.writeTextElement("niveau_visibilite", QString::number(m_niveau_visibilite));
    stream.writeTextElement("active", QString::number(m_est_active));
    objet_selectionnable::sauvegarder(stream);

    if ( m_type == type_fonction::fonction_source )
        stream.writeTextElement( "valeur", ((fonction_base_source*)(this))->get_string_valeur() );

    stream.writeStartElement("parametres");
    parametres_const_iterateur it;
    for ( it = m_parametres.begin(); it != m_parametres.end(); ++it )
        it->second->sauvegarder(stream);

    stream.writeEndElement(); // parametres
    stream.writeEndElement(); // fonction
}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *base_fonction::generer_fonction_widget()
{
    return new base_fonction_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du nom de la fonction.
 * \return Le nom de la fonction.
*/
QString base_fonction::get_nom() const
{
    return m_nom;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du type de la fonction.
 * \return Le type de la fonction.
*/
type_fonction base_fonction::get_type() const
{
    return m_type;
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un paramètre à la fonction.
 * \param id L'identifiant du paramètre.
 * \param p Un pointeur sur le paramètre à ajouter.
 */
void base_fonction::ajouter_parametre(type_id_parametre id, base_parametre *p)
{
    m_parametres[id] = p;
    p->set_id( id );
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le texte d'un paramètre donné.
 * \param type Le type du paramètre recherché.
 * \return Le texte du paramètre.
 */
const textes &base_fonction::get_textes_parametre(type_id_parametre type) const
{
    parametres_const_iterateur it = m_parametres.find(type);

    if ( it != m_parametres.end() )
        return it->second->get_textes_out();
    else
    {
        std::cout << "ERREUR : base_fonction::get_textes_parametre : impossible de trouver le parametre " << type << std::endl;
        return textes();
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Augmente le niveau maximum de visibilité de la fonction.
 * \param val L'augmentation voulue.
 */
void base_fonction::augmenter_max_niveau_visibilite(int val)
{
    m_max_niveau_visibilite += val;
    m_niveau_visibilite += val;
    m_niveau_visibilite_avant_desactivation += val;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'identifiant de la fonction.
 * \return L'identifiant de la fonction.
 */
type_id_fonction base_fonction::get_id() const
{
    return m_id;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le conteneur de la fonction.
 * \param conteneur Un pointeur sur le nouveau conteneur.
 */
void base_fonction::set_conteneur(fonctions_conteneur *conteneur)
{
    m_objet_parent = conteneur;
    m_conteneur = conteneur;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur sur le conteneur de la fonction.
 * \return Un pointeur sur le conteneur de la fonction.
 */
fonctions_conteneur *base_fonction::get_conteneur() const
{
    return m_conteneur;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'identifiant de la fonction.
 * \param id Le nouvel identifiant de la fonction.
 */
void base_fonction::set_id(const type_id_fonction &id)
{
    m_id = id;
    m_nom = bibliotheque_fonctions::get_nom( m_id );
}

/** --------------------------------------------------------------------------------------
 * \brief Modifier le niveau de visibilité de la fonction.
 * \remark Le niveau est par diminué d'une unité. S'il atteint 0, il revient au niveau max.
 */
void base_fonction::change_niveau_visibilite()
{
    int niveau = m_niveau_visibilite - 1;

    if ( niveau == 0 )
        niveau = m_max_niveau_visibilite;

    set_niveau_visibilite(niveau);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'activation de la fonction.
 * \param active Le nouvel état d'activation.
 */
void base_fonction::set_est_active(bool active)
{
    if ( active )
    {
        if ( get_niveau_visibilite() == 1 )
            set_niveau_visibilite( m_niveau_visibilite_avant_desactivation );
    }
    else
    {
        m_niveau_visibilite_avant_desactivation = get_niveau_visibilite();
        set_niveau_visibilite(1);
    }

    objet_selectionnable::set_est_active( active );

    emit signal_activation_fonction_change(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'état étendu de la fonction.
 * \param est_etendu Le nouvel état étendu de la fonction.
 */
void base_fonction::set_est_etendu(bool est_etendu)
{
    objet_selectionnable::set_est_etendu( est_etendu );

    emit signal_etendu_change(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si la fonction a un paramètre.
 * \return \b True si la fonction contient un paramètre, \b False sinon.
 */
bool base_fonction::a_parametre() const
{
    return ! m_parametres.empty();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du niveau de visibilité de la fonction.
 * \return Le niveau de visibilité de la fonction.
 */
int base_fonction::get_niveau_visibilite() const
{
    return m_niveau_visibilite;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du niveau maximum de visibilité de la fonction.
 * \return Le niveau maximum de visibilité de la fonction.
 */
int base_fonction::get_max_niveau_visibilite() const
{
    return m_max_niveau_visibilite;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le niveau de visibilité de la fonction.
 * \param niveau_visibilite Le nouveau niveau de visibilité de la fonction.
 */
void base_fonction::set_niveau_visibilite(int niveau_visibilite)
{
    m_niveau_visibilite = niveau_visibilite;

    emit signal_niveau_visibilite_change(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Inverse le niveau de visibilité de la fonction.
 */
void base_fonction::inverser_activation()
{
    set_est_active( ! m_est_active );
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la position d'une fonction dans son conteneur.
 * \return La position de la fonction. 0 si elle n'est pas dans un conteneur.
 */
int base_fonction::get_position()
{
    if ( m_conteneur == NULL )
        return 0;
    else
        return m_conteneur->get_position(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'itérateur sur le début de la liste des paramètres.
 * \return L'itérateur sur le début de la liste des paramètres.
 */
base_fonction::parametres_iterateur base_fonction::parametres_begin()
{
    return m_parametres.begin();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'itérateur sur la fin des paramètres.
 * \return L'itérateur sur la fin de la liste des paramètres.
 */
base_fonction::parametres_iterateur base_fonction::parametres_end()
{
    return m_parametres.end();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'itérateur constant sur le début de la liste des paramètres.
 * \return L'itérateur constant sur le début de la liste des paramètres.
 */
base_fonction::parametres_const_iterateur base_fonction::parametres_const_begin() const
{
    return m_parametres.begin();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'itérateur constant sur la fin de la liste des paramètres.
 * \return L'itérateur constant sur la fin de la liste des paramètres.
 */
base_fonction::parametres_const_iterateur base_fonction::parametres_const_end() const
{
    return m_parametres.end();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le paramètre pour un identifiant donné.
 * \param id L'identifiant du paramètre voulu.
 * \return Un pointeur sur le paramètre voulu.
 */
base_parametre *base_fonction::get_parametre(type_id_parametre id)
{
    return m_parametres.find(id)->second;
}

/** --------------------------------------------------------------------------------------
 * \brief Teste si la fonction est valide.
 * \param vue_logs Le widget de la vue des logs.
 * \return \b True si la fonction est valide, \b False sinon.
 */
bool base_fonction::est_fonction_valide(logs_compilation_widget * vue_logs)
{
    bool result = est_valide(vue_logs);

    for ( parametres_const_iterateur it = parametres_const_begin(); it != parametres_const_end(); ++it )
    {
        bool result_param = it->second->est_valide(vue_logs);
        result = result && result_param;
    }

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Charge la fonction à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 */
void base_fonction::charger(QXmlStreamReader & xml)
{
    while(xml.readNextStartElement())
    {
        if(xml.name() == "nom")
        {
            // ignoré
            QString nom = xml.readElementText();
        }
        else if(xml.name() == "niveau_visibilite")
        {
            QString niveau_visibilite = xml.readElementText();
            set_niveau_visibilite( niveau_visibilite.toInt() );
        }
        else if(xml.name() == "active")
        {
            QString active = xml.readElementText();
            set_est_active( active.toInt() );
        }
        else if(xml.name() == "valeur")
        {
            QString valeur = xml.readElementText();
            if ( get_type() == type_fonction::fonction_source )
                ((fonction_base_source*)this)->set_string_valeur(valeur);
        }
        else if (xml.name() == "objet_selectionnable")
            objet_selectionnable::charger(xml);
        else if(xml.name() == "parametres")
        {
            charger_parametres(xml);
        }
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Charge les paramètres à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 */
void base_fonction::charger_parametres(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "parametres");

    while(xml.readNextStartElement())
    {
        if(xml.name() == "parametre")
        {
            charger_parametre(xml);
        }
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Charge un paramètre à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 */
void base_fonction::charger_parametre(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "parametre");

    xml.readNextStartElement();

    if(xml.name() == "id")
    {
        int id = xml.readElementText().toInt();
        m_parametres[(type_id_parametre)id]->charger(xml);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Algorithme d'exécution selon un parametre donné dans le cas : <b>ligne, itération sur chaque ligne</b>.
 * \param id_param L'identifiant du paramètre à exécuter.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 * \param callback La fonction à appeler en fin d'algorithme.
 * \remark L'algorithme itère sur les lignes. Possibilité de parcourir les mots de la ligne et les caractères des mots.\n
 * Les données courantes sont ainsi :
 *  - la ligne courante
 *  - le mot courant
 *  - un itérateur sur la ligne, i.e. un itérateur sur les mots de la ligne.
 */
void base_fonction::algo_IPL_iteration_par_ligne
( type_id_parametre id_param, compilateur &compil, textes & textes_in, textes & textes_out,
  pf_exec_callback callback )
{
    const textes& t_param = get_textes_parametre(id_param);
    bool test_vide = ! m_parametres[id_param]->peut_etre_vide();

    if ( test_vide && t_param.empty() )
        compil.get_vue_logs()->ajouter_log
                ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                   "Le paramètre " + m_parametres[id_param]->get_nom() + " est vide.") );
    else
        for ( textes::const_iterator it_t = t_param.begin(); it_t != t_param.end(); ++it_t)
            if ( test_vide && it_t->empty() )
                compil.get_vue_logs()->ajouter_log
                        ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                           "Le paramètre " + m_parametres[id_param]->get_nom() + " est vide.") );
            else
            {
                for ( texte::const_iterator it_l = it_t->begin(); it_l != it_t->end(); ++it_l)
                    if ( test_vide && it_l->empty() )
                        compil.get_vue_logs()->ajouter_log
                                ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                                   "Le paramètre " + m_parametres[id_param]->get_nom() + " est vide sur une ligne.") );
                    else
                    {
                        m_map_IPL[id_param].it_ligne_debut = it_l->begin();
                        m_map_IPL[id_param].it_mot_courant = it_l->begin();
                        m_map_IPL[id_param].it_ligne_fin = it_l->end();

                        IPL_init(id_param);

                        if ( m_parametres[id_param]->configuration_visible() )
                            compil.ajouter_configuration(this, id_param, it_l->to_string_lisible());

                        (this->*callback)(compil, textes_in, textes_out);

                        if ( m_parametres[id_param]->configuration_visible() )
                            compil.retirer_configuration(this, id_param);
                    }
            }
}

/** --------------------------------------------------------------------------------------
 * \brief Avance l'itérateur d'un paramètre donné pour l'algorithme MIPL.
 * \param id_param L'identifiant du paramètre qu'il faut avancer.
 */
void base_fonction::IPL_mot_suivant(type_id_parametre id_param)
{
    m_map_IPL[id_param].it_mot_courant++;
    if ( m_map_IPL[id_param].it_mot_courant == m_map_IPL[id_param].it_ligne_fin )
        m_map_IPL[id_param].it_mot_courant = m_map_IPL[id_param].it_ligne_debut;

    m_map_IPL[id_param].it_mot_debut = m_map_IPL[id_param].it_mot_courant->begin();
    m_map_IPL[id_param].it_caractere_courant = m_map_IPL[id_param].it_mot_debut;
    m_map_IPL[id_param].it_mot_fin = m_map_IPL[id_param].it_mot_courant->end();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'itérateur d'un paramètre donné pour l'algorithme MIPL.
 * \param id_param L'identifiant du paramètre qu'il faut initialiser.
 */
void base_fonction::IPL_init(type_id_parametre id_param)
{
    m_map_IPL[id_param].it_mot_courant = m_map_IPL[id_param].it_ligne_debut;

    m_map_IPL[id_param].it_mot_debut = m_map_IPL[id_param].it_mot_courant->begin();
    m_map_IPL[id_param].it_caractere_courant = m_map_IPL[id_param].it_mot_debut;
    m_map_IPL[id_param].it_mot_fin = m_map_IPL[id_param].it_mot_courant->end();
}

/** --------------------------------------------------------------------------------------
 * \brief Avance l'itérateur d'un paramètre donné pour l'algorithme MIPL.
 * \param id_param L'identifiant du paramètre qu'il faut avancer.
 */
void base_fonction::IPL_caractere_suivant(type_id_parametre id_param)
{
    m_map_IPL[id_param].it_caractere_courant++;
    if ( m_map_IPL[id_param].it_caractere_courant == m_map_IPL[id_param].it_mot_fin )
        m_map_IPL[id_param].it_caractere_courant = m_map_IPL[id_param].it_mot_debut;
}

/** --------------------------------------------------------------------------------------
 * \brief Première fonction appelée lors de l'exécution automatique d'un paramètre.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void base_fonction::callback_param_1(compilateur &compil, textes & textes_in, textes &textes_out)
{
    std::cout << "base_fonction::callback_param_1" << std::endl;
    std::cout << "Erreur : on ne doit pas passer dans cette méthode virtuelle." << std::endl;
}

/** --------------------------------------------------------------------------------------
 * \brief Deuxième fonction appelée lors de l'exécution automatique d'un paramètre.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void base_fonction::callback_param_2(compilateur &compil, textes & textes_in, textes &textes_out)
{
    std::cout << "base_fonction::callback_param_2" << std::endl;
    std::cout << "Erreur : on ne doit pas passer dans cette méthode virtuelle." << std::endl;
}

/** --------------------------------------------------------------------------------------
 * \brief Troisième fonction appelée lors de l'exécution automatique d'un paramètre.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void base_fonction::callback_param_3(compilateur &compil, textes & textes_in, textes &textes_out)
{
    std::cout << "base_fonction::callback_param_3" << std::endl;
    std::cout << "Erreur : on ne doit pas passer dans cette méthode virtuelle." << std::endl;
}

/** --------------------------------------------------------------------------------------
 * \brief Quatrième fonction appelée lors de l'exécution automatique d'un paramètre.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void base_fonction::callback_param_4(compilateur &compil, textes & textes_in, textes &textes_out)
{
    std::cout << "base_fonction::callback_param_4" << std::endl;
    std::cout << "Erreur : on ne doit pas passer dans cette méthode virtuelle." << std::endl;
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors de l'exécution spécifique d'une fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void base_fonction::execution_specifique(compilateur &compil, textes & textes_in, textes &textes_out)
{
    std::cout << "base_fonction::execution_specifique" << std::endl;
    std::cout << "Erreur : on ne doit pas passer dans cette méthode virtuelle." << std::endl;
}
