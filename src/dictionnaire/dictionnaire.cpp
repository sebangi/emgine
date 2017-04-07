#include "entete/dictionnaire/dictionnaire.h"

#include <QCoreApplication>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

#include <iostream>

/*----------------------------------------------------------------------------*/
dictionnaire::dictionnaire(const QString & nom_fichier)
    : m_nom_fichier( nom_fichier ), m_cles( sizeof(unsigned int) * 8 + 1 )
{
    m_arbre_mots = new lettre_dictionnaire();
    charger_dictionnaire( nom_fichier );
}

dictionnaire::~dictionnaire()
{
    clear();
}

void dictionnaire::mettre_a_jour()
{
    QDir dir( QCoreApplication::applicationDirPath() );
    QString absolu_path = dir.absoluteFilePath( m_nom_fichier );
    QFile file(absolu_path);

    if (! file.open(QIODevice::ReadOnly))
    {
        std::cout << "Erreur : impossible d'ouvrir le dictionnaire " << absolu_path.toStdString() << std::endl;
        return;
    }

    bool charger = false;
    QFileInfo info(file);
    if ( m_date_derniere_modification != info.lastModified() )
        charger = true;
    file.close();

    if ( charger )
    {
        clear();
        charger_dictionnaire( m_nom_fichier );
    }
}


/*----------------------------------------------------------------------------*/
bool dictionnaire::existe( const QString& motif ) const
{
    QString motif_formate(motif);
    formater(motif_formate);

    lettre_dictionnaire * lettre = m_arbre_mots;
    for ( QString::iterator it = motif_formate.begin();
          lettre != NULL && it != motif_formate.end(); ++it )
        lettre = lettre->suivant(it->toLatin1() - 'A');

    if ( lettre != NULL )
        return lettre->est_mot();
    else
        return false;
}

/*----------------------------------------------------------------------------*/
void dictionnaire::anagramme( const QString& motif, uint_set& mots ) const
{
    QString motif_formate(motif);
    formater(motif_formate);
    cle_de_mot cle(motif_formate);
    map_code_comptage::const_iterator it_code;
    map_comptage_indice::const_iterator it_compte;

    it_code = m_cles[ cle.taille() ].find( cle.code_binaire() );

    if ( it_code != m_cles[ cle.taille() ].end() )
    {
        it_compte = it_code->second.find( cle.comptage() );

        if ( it_compte != it_code->second.end() )
            mots.insert( it_compte->second.begin(), it_compte->second.end() );
    }
}

/*----------------------------------------------------------------------------*/
void dictionnaire::recherche_expression_reguliere(const QString &motif, dictionnaire::qstring_set &mots) const
{
    QString motif_formate(motif);
    formater(motif_formate, true);

    if ( est_expression_reguliere( motif_formate ) )
    {
        lettre_dictionnaire * lettre = m_arbre_mots;
        QString mot("");
        parcourir_avec_expression_reguliere( motif, mots, lettre, mot);
    }
} // dictionnaire::recherche_expression_reguliere()

/*----------------------------------------------------------------------------*/
void dictionnaire::parcourir_avec_expression_reguliere
(const QString &motif, dictionnaire::qstring_set &mots, lettre_dictionnaire * lettre, const QString & mot) const
{
    if ( lettre != NULL )
    {
        if ( motif.isEmpty() )
        {
            if ( lettre->est_mot() )
                mots.insert(mot);
        }
        else
        {
            char c = motif[0].toLatin1();
            QString suite = motif.mid(1);

            if ( c == '.' )
            {
                for ( char c = 'A'; c <= 'Z'; ++c )
                {
                    QString s(mot + c);
                    parcourir_avec_expression_reguliere(suite, mots, lettre->suivant(c - 'A'), s );
                }
            }
            else if ( c == '*' )
            {
                parcourir_avec_expression_reguliere( suite, mots, lettre, mot );

                for ( char pos = 'A'; pos <= 'Z'; ++pos )
                {
                    QString s(mot + pos);
                    parcourir_avec_expression_reguliere(motif, mots, lettre->suivant(pos - 'A'), s );
                }
            }
            else if ( c == '(' || c == '|' )
            {
                c = motif[1].toLatin1();
                int pos = c - 'A';

                if ( pos < 26 && pos >= 0 )
                {
                    QString s( mot + c );
                    while ( suite[1].toLatin1() != ')' )
                        suite = suite.mid(2);
                    suite = suite.mid(2);
                    parcourir_avec_expression_reguliere(suite, mots, lettre->suivant(pos), s );
                }

                suite = motif.mid(2);
                parcourir_avec_expression_reguliere(suite, mots, lettre, mot );
            }
            else
            {
                int pos = c - 'A';
                if ( pos < 26 && pos >= 0 )
                {
                    QString s( mot + c );
                    parcourir_avec_expression_reguliere(suite, mots, lettre->suivant(pos), s );
                }
            }
        }
    }
} // dictionnaire::parcourir_avec_expression_reguliere

/*----------------------------------------------------------------------------*/
void dictionnaire::sur_anagramme( const QString& motif, uint_set& mots ) const
{
    QString motif_formate(motif);
    formater(motif_formate);
    cle_de_mot cle(motif_formate);
    map_code_comptage::const_iterator it_code;
    map_comptage_indice::const_iterator it_compte;

    for ( unsigned int i=cle.taille(); i!=m_cles.size(); ++i )
        for ( it_code=m_cles[i].begin(); it_code!=m_cles[i].end(); ++it_code )
            if ( cle.le_mot_binaire().est_inclus_dans(it_code->first) )
                for ( it_compte=it_code->second.begin();
                      it_compte!=it_code->second.end();
                      ++it_compte )
                    if ( cle.comptage().est_inclus_dans(it_compte->first) )
                        mots.insert( it_compte->second.begin(), it_compte->second.end() );
} // dictionnaire::sur_anagramme()

/*----------------------------------------------------------------------------*/
void
dictionnaire::sous_anagramme( const QString& motif, uint_set& mots ) const
{
    QString motif_formate(motif);
    formater(motif_formate);
    cle_de_mot cle(motif_formate);
    map_code_comptage::const_iterator it_code;
    map_comptage_indice::const_iterator it_compte;

    for ( unsigned int i=0; i<=cle.taille(); ++i )
        for ( it_code=m_cles[i].begin(); it_code!=m_cles[i].end(); ++it_code )
            if ( cle.le_mot_binaire().contient(it_code->first) )
                for ( it_compte=it_code->second.begin();
                      it_compte!=it_code->second.end();
                      ++it_compte )
                    if ( it_compte->first.est_inclus_dans(cle.comptage()) )
                        mots.insert( it_compte->second.begin(), it_compte->second.end() );
}

QString dictionnaire::plus_grand_prefixe(const QString & s) const
{
    QString resultat("");

    QString motif_formate(s);
    formater(motif_formate);
    QString mot_genere("");

    lettre_dictionnaire * lettre = m_arbre_mots;
    for ( QString::iterator it = motif_formate.begin();
          lettre != NULL && it != motif_formate.end(); ++it )
    {
        if ( lettre->est_mot() )
            resultat = mot_genere;

        mot_genere.append( *it );
        lettre = lettre->suivant(it->toLatin1() - 'A');
    }

    if ( lettre != NULL )
        if ( lettre->est_mot() )
            resultat = mot_genere;

    return resultat;
}

/*----------------------------------------------------------------------------*/
void dictionnaire::formater( QString& s, bool format_expression_reguliere ) const
{
    s = s.toUpper();

    s.replace( QRegExp( "[ÁÀÂÄ]") , "A" );
    s.replace( QRegExp( "[ÉÈÊË]") , "E" );
    s.replace( QRegExp( "[ÍÌÎÏ]") , "I" );
    s.replace( QRegExp( "[ÓÒÔÖ]") , "O" );
    s.replace( QRegExp( "[ÚÙÛÜ]") , "U" );
    s.replace( QRegExp( "[Ç]") , "C" );

    QString ponct;
    if ( format_expression_reguliere )
        ponct = QRegExp::escape(" «»,;:!?/§%^¨$£&~\"#'{[`_\\^@]°=}+-");
    else
        ponct = QRegExp::escape(" «»,;:!?./§*%^¨$£&~\"#'{([|`_\\^@)]°=}+-");
    s.remove( QRegExp( "[" + ponct + "]" ) );

} // dictionnaire::formater()

void dictionnaire::charger_dictionnaire( const QString & nom_fichier )
{
    if (nom_fichier.isEmpty())
        return;

    QDir dir( QCoreApplication::applicationDirPath() );
    QString absolu_path = dir.absoluteFilePath( nom_fichier );
    QFile file(absolu_path);

    if (! file.open(QIODevice::ReadOnly))
    {
        std::cout << "Erreur : impossible d'ouvrir le dictionnaire " << absolu_path.toStdString() << std::endl;
        return;
    }

    QFileInfo info(file);
    m_date_derniere_modification = info.lastModified();
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();

        m_mots.push_back(line);
        ajouter_mot_dans_arbre(line);

        cle_de_mot cle(line);
        m_cles[ cle.taille() ][ cle.code_binaire() ][ cle.comptage() ].push_front( m_mots.size() - 1 );
    }

    file.close();
}


void dictionnaire::clear(  )
{
    m_cles.clear();
    m_mots.clear();
    clear_arbre();
}

void dictionnaire::clear_arbre()
{
    delete m_arbre_mots;
    m_arbre_mots = new lettre_dictionnaire();
}

bool dictionnaire::est_expression_reguliere(const QString &motif) const
{
    return true;
}

void dictionnaire::ajouter_mot_dans_arbre( const QString &s )
{
    QString s_formate(s);
    formater(s_formate);

    lettre_dictionnaire * lettre = m_arbre_mots;
    for ( QString::iterator it = s_formate.begin(); it != s_formate.end(); ++it )
    {
        int pos = it->toLatin1() - 'A';
        if ( pos > 25 || pos < 0 )
            std::cout << "Dictionnaire : Attention, impossible d'ajouter le caractère " << it->toLatin1() << std::endl;
        else
            lettre = lettre->get_suivant(pos);
    }

    lettre->set_est_mot();
}
