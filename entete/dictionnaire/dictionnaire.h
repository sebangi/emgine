#ifndef __DICTIONNAIRE_HPP__
#define __DICTIONNAIRE_HPP__

#include <set>
#include <map>
#include <list>
#include <vector>
#include <QString>
#include <QDateTime>
#include <QObject>

#include "entete/dictionnaire/cle_de_mot.h"
#include "entete/dictionnaire/lettre_dictionnaire.h"

class dictionnaire : public QObject
{
        Q_OBJECT

    public:
        typedef std::set<unsigned int> uint_set;
        typedef std::set<QString> qstring_set;

    private:
        typedef std::list<unsigned int> uint_list;
        typedef std::map<comptage_mot, uint_list> map_comptage_indice;
        typedef std::map<unsigned int, map_comptage_indice> map_code_comptage;
        typedef std::vector<map_code_comptage> vector_codes;

        typedef std::map<QString, uint_list> patron_map;

    public:
        dictionnaire( const QString & nom_fichier );
        ~dictionnaire();

        void mettre_a_jour();

        bool existe( const QString& motif ) const;
        void anagramme( const QString& motif, uint_set& mots ) const;
        void patron( const QString& motif, uint_set& mots ) const;
        void recherche_expression_reguliere( const QString& motif, qstring_set& mots ) const;
        void sur_anagramme( const QString& motif, uint_set& mots ) const;
        void sous_anagramme( const QString& motif, uint_set& mots ) const;

        const QString& operator[]( unsigned int i ) const
        {
            return m_mots[i];
        }

        QString plus_grand_prefixe( const QString & s ) const;

    private:
        void formater( QString& s, bool format_expression_reguliere = false ) const;
        QString cle_patron( const QString & line ) const;
        void charger_dictionnaire( const QString & nom_fichier );
        void clear();
        void ajouter_mot_dans_arbre( const QString& s);
        void clear_arbre();
        bool est_expression_reguliere(const QString &motif ) const;
        void parcourir_avec_expression_reguliere
        ( const QString &motif, dictionnaire::qstring_set &mots, lettre_dictionnaire * lettre,
          const QString & mot) const;

    private:
        /** \brief Le nom du fichier source. */
        QString m_nom_fichier;

        /** \brief Le tableau des clés.*/
        vector_codes m_cles;

        /** \brief La map des patrons.*/
        patron_map m_patrons;

        /** \brief Tous les mots du dictionnaire. */
        std::vector<QString> m_mots;

        /** \brief La date de la dernière modification du fichier source. */
        QDateTime m_date_derniere_modification;

        /** \brief Tous les mots du dictionnaire sous forme d'arbre. */
        lettre_dictionnaire * m_arbre_mots;
};

#endif // __DICTIONNAIRE_HPP__
