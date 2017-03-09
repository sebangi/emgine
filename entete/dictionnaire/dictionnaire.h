#ifndef __DICTIONNAIRE_HPP__
#define __DICTIONNAIRE_HPP__

#include <set>
#include <map>
#include <list>
#include <vector>
#include <QString>
#include <QDateTime>

#include "entete/dictionnaire/cle_de_mot.h"
#include "entete/dictionnaire/lettre_dictionnaire.h"

class dictionnaire
{
    public:
        typedef std::set<unsigned int> uint_set;

    private:
        typedef std::list<unsigned int> uint_list;
        typedef std::map<comptage_mot, uint_list> map_comptage_indice;
        typedef std::map<unsigned int, map_comptage_indice> map_code_comptage;
        typedef std::vector<map_code_comptage> vector_codes;

    public:
        dictionnaire( const QString & nom_fichier );
        ~dictionnaire();

        void mettre_a_jour();

        bool existe( const QString& motif ) const;
        void grep( const QString& motif, uint_set& mots ) const;
        void anagramme( const QString& motif, uint_set& mots ) const;
        void sur_anagramme( const QString& motif, uint_set& mots ) const;
        void sous_anagramme( const QString& motif, uint_set& mots ) const;

        const QString& operator[]( unsigned int i ) const
        {
            return m_mots[i];
        }

    private:
        void formater( QString& s ) const;
        void charger_dictionnaire( const QString & nom_fichier );
        void clear();
        void ajouter_mot_dans_arbre( const QString& s);
        void clear_arbre();

    private:
        /** \brief Le nom du fichier source. */
        QString m_nom_fichier;

        /** \brief Le tableau des clés.*/
        vector_codes m_cles;

        /** \brief Tous les mots du dictionnaire. */
        std::vector<QString> m_mots;

        /** \brief La date de la dernière modification du fichier source. */
        QDateTime m_date_derniere_modification;

        /** \brief Tous les mots du dictionnaire sous forme d'arbre. */
        lettre_dictionnaire * m_arbre_mots;
};

#endif // __DICTIONNAIRE_HPP__