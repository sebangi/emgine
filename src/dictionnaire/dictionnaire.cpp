#include "entete/dictionnaire/dictionnaire.h"

#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

/*----------------------------------------------------------------------------*/
dictionnaire::dictionnaire(const QString & nom_fichier)
    : m_nom_fichier( nom_fichier ), m_cles( sizeof(unsigned int) * 8 + 1 )
{
    charger_dictionnaire( nom_fichier );
}

void dictionnaire::mettre_a_jour()
{
    QFile file(m_nom_fichier);

    if (! file.open(QIODevice::ReadOnly))
    {
        std::cout << "Erreur : impossible d'ouvrir le dictionnaire " << m_nom_fichier.toStdString() << std::endl;
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
void dictionnaire::grep( const QString& motif, uint_set& mots ) const
{

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
} // dictionnaire::anagramme()

/*----------------------------------------------------------------------------*/
void dictionnaire::sur_anagramme( const QString& motif, uint_set& mots ) const
{
    cle_de_mot cle(motif);
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
    cle_de_mot cle(motif);
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
} // dictionnaire::sous_anagramme()

/*----------------------------------------------------------------------------*/
void dictionnaire::formater( QString& s ) const
{
    s = s.toUpper();

    s.replace( QRegExp( "[ÁÀÂÄ]") , "A" );
    s.replace( QRegExp( "[ÉÈÊË]") , "E" );
    s.replace( QRegExp( "[ÍÌÎÏ]") , "I" );
    s.replace( QRegExp( "[ÓÒÔÖ]") , "O" );
    s.replace( QRegExp( "[ÚÙÛÜ]") , "U" );
    s.replace( QRegExp( "[Ç]") , "C" );

    QString ponct = QRegExp::escape("«»,;:!?./§*%^¨$£&~\"#'{([|`_\\^@)]°=}+-");
    s.remove( QRegExp( "[" + ponct + "]" ) );
} // dictionnaire::formater()

void dictionnaire::charger_dictionnaire( const QString & nom_fichier )
{
    if (nom_fichier.isEmpty())
        return;

    QFile file(nom_fichier);

    if (! file.open(QIODevice::ReadOnly))
    {
        std::cout << "Erreur : impossible d'ouvrir le dictionnaire " << nom_fichier.toStdString() << std::endl;
        return;
    }

    QFileInfo info(file);
    m_date_derniere_modification = info.lastModified();
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();

        m_mots.push_back(line);

        cle_de_mot cle(line);
        m_cles[ cle.taille() ][ cle.code_binaire() ][ cle.comptage() ].push_front( m_mots.size() - 1 );
   }

    file.close();
}


void dictionnaire::clear(  )
{
    m_cles.clear();
    m_mots.clear();
}
