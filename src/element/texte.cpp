/** \file texte.cpp
 * \brief Fichier d'implémentation de la classe texte.
 * \author Sébastien Angibaud
 */

#include "entete/element/texte.h"

#include "entete/projet/base_fonction.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par défaut de la classe texte.
 */
texte::texte()
    : vector<ligne>(), m_separateur_ligne("\n"), m_configuration_visible(false), m_nb_lignes_configuration(16), m_nb_caracteres(0), m_nb_mots(0)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe texte.
 * \param config La configuration des paramètres induisant ce texte.
 * \param separateur_ligne Le séparateur de ligne.
 */
texte::texte( const configuration& config, const QString & separateur_ligne )
    : vector<ligne>(), m_configuration(config), m_separateur_ligne(separateur_ligne),
      m_configuration_visible(false), m_nb_lignes_configuration(16), m_nb_caracteres(0), m_nb_mots(0)
{
    ajouter_string_configuration( config );
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe texte.
 * \param valeur La chaîne de caractères induisant ce texte.
 * \param separateur_ligne Le séparateur de ligne.
 */
texte::texte(const QString &valeur, const QString & separateur_ligne)
    : vector<ligne>(), m_separateur_ligne(separateur_ligne), m_configuration_visible(false), m_nb_lignes_configuration(16),
      m_nb_caracteres(0), m_nb_mots(0)
{
    if ( ! valeur.isEmpty() )
    {
        ligne l(valeur);
        ajouter_ligne(l);
    }
}


/** --------------------------------------------------------------------------------------
 * \brief Constructeur par copie de la classe texte.
 * \param t Le texte à copier.
 */

texte::texte(const texte &t)
    : vector<ligne>( t ), m_configuration(t.m_configuration), m_string_configuration(t.m_string_configuration),
      m_separateur_ligne(t.m_separateur_ligne),
      m_configuration_visible(t.m_configuration_visible), m_nb_lignes_configuration(t.m_nb_lignes_configuration),
      m_nb_caracteres(t.m_nb_caracteres), m_nb_mots(t.m_nb_mots),
      m_frequences(t.m_frequences), m_indice_coincidence(t.m_indice_coincidence)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe texte.
 */
texte::~texte()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute une ligne donnée en fin de texte.
 * \param l La ligne à ajouter.
 */
void texte::ajouter_ligne( const ligne & l)
{
    push_back(l);
    m_nb_caracteres += l.nb_caracteres();
    m_nb_mots += l.nb_mots();

    if ( l.to_string_lisible().size() > m_nb_lignes_configuration )
        m_nb_lignes_configuration = l.to_string_lisible().size();
}

/** --------------------------------------------------------------------------------------
 * \brief Convertit le texte au format QString.
 * \return Le texte au format QString.
 */
QString texte::to_string() const
{
    QString result;

    for ( int i = 0; i < size(); ++i )
        result += this->at(i).to_string();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Convertit le texte au format QString avec séparateur de ligne.
 * \return Le texte au format QString.
 */
QString texte::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string_lisible();

    for ( int i = 1; i < size(); ++i )
        result += m_separateur_ligne + this->at(i).to_string_lisible();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la configuration des paramètres au format QString.
 * \return La configuration des paramètres au format QString.
 */
QString texte::get_string_configuration() const
{
    QString result = "Configuration : \n";

    if( m_string_configuration.isEmpty() )
        result += "\taucune\n" ;
    else
        result += m_string_configuration;

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne les informations de taille du texte (nombre de lignes, de mots et de caractères) au format QString.
 * \return Les informations de taille au format QString.
 */
QString texte::get_string_information_taille() const
{
    return QString( "Nombre de lignes : " + QString::number( nb_lignes() ) + "\n" +
                    "Nombre de mots : " + QString::number( nb_mots() ) + "\n" +
                    "Nombre de caracteres : " + QString::number( nb_caracteres() ) + "\n" );
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne une ligne de séparation au format QString. La largeur de la séparation s'adpate au contenu du texte.
 * \return Une ligne de séparation au format QString.
 */
QString texte::get_string_separation() const
{
    QString result;
    for ( int i = 0; i < m_nb_lignes_configuration; ++i )
        result += "-";
    result += "\n";

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour la configuration au format QString lors de l'ajout d'une configuration donnée.
 * \param config La configuration ajoutée.
 */
void texte::ajouter_string_configuration(const configuration& config)
{
    for ( configuration::const_iterator it = config.begin(); it != config.end(); ++it )
    {
        QString s = "\t* " + it->first.first->get_nom() +
                "[" + it->first.first->get_parametre(it->first.second)->get_nom() + "] => " + it->second;

        m_string_configuration += s + "\n";

        // on ajuste le max : le 9 vient de la tabulation
        if ( s.size() + 9 > m_nb_lignes_configuration )
            m_nb_lignes_configuration = s.size() + 9;
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute une configuration donnée.
 * \param config La configuration à ajoutée.
 */
void texte::ajouter_configuration(const configuration &config)
{
    for ( configuration::const_iterator it = config.begin(); it != config.end(); ++it )
        m_configuration[ it->first ] = it->second;

    ajouter_string_configuration(config);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la configuration des paramètres induisant ce texte.
 * \return La configuration du texte.
 */
const configuration& texte::get_configuration() const
{
    return m_configuration;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'état de visibilité de la configuration.
 * \return \b True si la configuration est visible, \b False sinon.
 */
bool texte::get_configuration_visible() const
{
    return m_configuration_visible;
}

/** --------------------------------------------------------------------------------------
 * \brief Inverse l'état de visibilité de la configuration.
 */
void texte::inverser_configuration_visibilite()
{
    m_configuration_visible = ! m_configuration_visible;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de lignes dui texte avec les informations (configuration et taille).
 * \return Le nombre de lignes du texte avec les informations.
 */
int texte::get_nb_lignes_avec_information() const
{
    int result = size();

    if ( m_configuration_visible )
    {
        if ( m_configuration.empty() )
            result += 9; // "Texte" + ligne vide + "configuration" + "aucune" + ligne vide + 4 lignes de taille + transition
        else
            result += 8 + m_configuration.size() ; // "texte" + ligne vide + "configuration" + nb param + 4 lignes de taille + transition
    }

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de caractères du texte.
 * \return Le nombre de caractères du texte.
 */
std::vector<ligne>::size_type texte::nb_caracteres() const
{
    return m_nb_caracteres;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de caractère alphabet du mot.
 * \return Le nombre de caractères alphabet du mot.
 */
std::vector<ligne>::size_type texte::nb_caracteres_alphabet() const
{
    std::vector<ligne>::size_type nb = 0;

    for ( int i = 0; i < size(); ++i )
        nb += this->at(i).nb_caracteres_alphabet();

    return nb;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de mots du texte.
 * \return Le nombre de mots du texte.
 */
std::vector<ligne>::size_type texte::nb_mots() const
{
    return m_nb_mots;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de lignes du texte.
 * \return Le nombre de lignes du texte.
 */
std::vector<ligne>::size_type texte::nb_lignes() const
{
    return size();
}

/** --------------------------------------------------------------------------------------
 * \brief Calcule la fréquence des éléments.
 * \param force_upper_case Booléen indiquant s'il faut forcer le upper_case.
 */
void texte::calculer_frequence( bool force_upper_case )
{
    m_frequences.clear();

    for ( texte::const_iterator it_l = begin(); it_l !=  end(); ++it_l )
        for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
            {
                bool trouve = false;
                base_element e( it_c->to_string(), force_upper_case);

                for ( type_frequences_texte::iterator it = m_frequences.begin(); it != m_frequences.end() && ! trouve; ++it )
                    if ( it->get_element() == e )
                    {
                        trouve = true;
                        it->ajouter_occurrence();
                    }
                if ( ! trouve )
                    m_frequences.push_back( frequence(*it_c, force_upper_case) );
            }

    std::sort(m_frequences.begin(), m_frequences.end());
}

/** --------------------------------------------------------------------------------------
 * \brief Calcule l'indice de coincidence du texte.
 */
void texte::calculer_indice_coincidence()
{
    calculer_frequence( true );

    m_indice_coincidence = 0;
    double nb_lettres = nb_caracteres_alphabet();
    double diviseur = nb_lettres * ( nb_lettres - 1 );

    for ( type_frequences_texte::const_iterator it = m_frequences.begin(); it != m_frequences.end(); ++it )
        if ( it->get_element().est_lettre_alphabet() )
            m_indice_coincidence += ( it->get_occurrence() * ( it->get_occurrence() - 1 ) ) / diviseur;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur des fréquences des éléments du texte.
 * \return La référence du tableau des fréquences des éléments.
 */
const texte::type_frequences_texte & texte::get_frequences() const
{
    return m_frequences;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'indice de coincidence du texte.
 * \return L'indice de coincidence du texte.
 */
double texte::get_indice_coincidence() const
{
    return m_indice_coincidence;
}

/** --------------------------------------------------------------------------------------
 * \brief Fusion des lignes, des mots et/ou des caractères.
 * \param fusion_caracteres Indique s'il faut fusionner les caractères.
 * \param fusion_mots Indique s'il faut fusionner les mots.
 * \param fusion_lignes Indique s'il faut fusionner les lignes.
 */
void texte::fusionner(bool fusion_caracteres, bool fusion_mots, bool fusion_lignes)
{
    if ( fusion_lignes && ! empty() )
    {
        iterator it_premier = begin();
        iterator it = begin();

        for ( ++it; it != end(); ++it )
            for ( ligne::iterator it_l = it->begin(); it_l != it->end(); ++it_l )
                it_premier->ajouter_mot(*it_l);

        it = begin();
        ++it;
        erase(it,end());
    }

    if ( fusion_caracteres || fusion_mots )
        for ( iterator it = begin(); it != end(); ++it )
            it->fusionner(fusion_caracteres, fusion_mots);

    maj_comptages();
}

/** --------------------------------------------------------------------------------------
 * \brief Transpose les mots du texte.
 */
void texte::transposer_mots()
{
    /*
     * AA BB CC
     * DD EE FF
     * GG HH
     *
     * AA DD GG
     * BB EE HH
     * CC FF
     * */
    texte t;

    for ( iterator it_t = begin(); it_t != end(); ++it_t )
    {
        unsigned int nb_lignes = 0;

        for ( ligne::iterator it_l = it_t->begin(); it_l != it_t->end(); ++it_l, ++nb_lignes )
        {
            if ( nb_lignes >= t.size() )
            {
                ligne l;
                l.set_separateur_mot( it_t->get_separateur_mot() );
                t.ajouter_ligne(l);
            }
            t[nb_lignes].ajouter_mot(*it_l);
         }
    }

    swap(t);
    maj_comptages();
}


/** --------------------------------------------------------------------------------------
 * \brief Transpose les caractères du texte.
 */
void texte::transposer_caracteres()
{
    /*
     * AA BB CC
     * DD EE FF
     * GG HH
     *
     * A D G
     * A D G
     * B E H
     * B E H
     * C F
     * C F
     * */
    texte t;

    for ( iterator it_t = begin(); it_t != end(); ++it_t )
    {
        unsigned int nb_lignes = 0;

        for ( ligne::iterator it_l = it_t->begin(); it_l != it_t->end(); ++it_l )
            for ( mot::iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m, ++nb_lignes )
            {
                if ( nb_lignes >= t.size() )
                {
                    ligne l;
                    l.set_separateur_mot( it_t->get_separateur_mot() );
                    t.ajouter_ligne(l);
                }
                mot m(it_m->to_string(), it_l->get_separateur_caractere() );
                t[nb_lignes].ajouter_mot( m );
             }
    }

    swap(t);
    maj_comptages();
}


/** --------------------------------------------------------------------------------------
 * \brief Accesseur du séparateur de lignes.
 * \return Le séparateur de ligne.
 */
QString texte::get_separateur_ligne() const
{
    return m_separateur_ligne;
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour les différents comptages.
 */
void texte::maj_comptages()
{
    maj_nb_caracteres();
    maj_nb_mots();
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le nombre de caractères du texte.
 */
void texte::maj_nb_caracteres()
{
    m_nb_caracteres = 0;

    for ( int i = 0; i < size(); ++i )
        m_nb_caracteres += this->at(i).nb_caracteres();
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le nombre de mots du texte.
 */
void texte::maj_nb_mots()
{
    m_nb_mots = 0;

    for ( int i = 0; i < size(); ++i )
        m_nb_mots += this->at(i).nb_mots();
}

