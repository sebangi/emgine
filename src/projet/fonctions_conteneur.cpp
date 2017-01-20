#include "entete/projet/fonctions_conteneur.h"

#include "entete/projet/base_fonction.h"
#include "entete/projet/projet.h"
#include "entete/fonction/bibliotheque_fonctions.h"

#include <iostream>

fonctions_conteneur::fonctions_conteneur( objet_selectionnable * parent )
    : objet_selectionnable(parent)
{

}

fonctions_conteneur::~fonctions_conteneur( )
{

}

// obj_ref :
//   - NULL : ajouter en fin
//   - this : ajouter en début
//   - est conteneur : ajouter en début
//   - fonction du conteneur : ajouter après la fonction
void fonctions_conteneur::ajouter_fonction(base_fonction *f, objet_selectionnable * obj_ref)
{
    f->set_conteneur(this);

    if ( obj_ref == NULL )
        m_fonctions.push_back(f);
    else if ( obj_ref == this )
        m_fonctions.push_front(f);
    else if ( obj_ref->est_conteneur() )
        m_fonctions.push_front(f);
    else if ( m_fonctions.contains((base_fonction*)obj_ref) )
        m_fonctions.insert( m_fonctions.indexOf((base_fonction*)obj_ref) + 1, f);
    else
        m_fonctions.push_back(f);

    connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_supprimer_fonction(base_fonction*)));

    emit signal_fc_creation_fonction(f);

    if ( est_dans_projet() )
        get_projet()->modifier();
}

void fonctions_conteneur::supprimer_fonction(base_fonction *f)
{
    disconnect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
                this, SLOT(on_supprimer_fonction(base_fonction*)));

    m_fonctions.removeOne(f);
    get_projet()->modifier();
}


void fonctions_conteneur::on_supprimer_fonction(base_fonction *f)
{
    supprimer_fonction(f);
}


fonctions_conteneur::fonctions_iterateur fonctions_conteneur::fonctions_begin()
{
    return m_fonctions.begin();
}

fonctions_conteneur::fonctions_iterateur fonctions_conteneur::fonctions_end()
{
    return m_fonctions.end();
}

fonctions_conteneur::fonctions_const_iterateur fonctions_conteneur::fonctions_const_begin() const
{
    return m_fonctions.constBegin();
}

fonctions_conteneur::fonctions_const_iterateur fonctions_conteneur::fonctions_const_end() const
{
    return m_fonctions.constEnd();
}

int fonctions_conteneur::get_position(base_fonction *f)
{
    if ( m_fonctions.contains(f) )
        return m_fonctions.indexOf(f);
    else
        return 0;
}

bool fonctions_conteneur::est_conteneur() const
{
    return true;
}

void fonctions_conteneur::charger_fonction( QXmlStreamReader & xml, objet_selectionnable * obj_ref )
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "fonction");

    xml.readNextStartElement();

    if(xml.name() == "id")
    {
        QString id = xml.readElementText();
        base_fonction * f = bibliotheque_fonctions::get_fonction( (type_id_fonction)id.toInt() );

        f->charger(xml);
        ajouter_fonction(f, obj_ref);
    }
}

void fonctions_conteneur::charger_fonctions(QXmlStreamReader & xml, objet_selectionnable * obj_ref )
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "fonctions");

    while(xml.readNextStartElement())
    {
        if(xml.name() == "fonction")
            charger_fonction(xml, obj_ref);
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

void fonctions_conteneur::sauvegarder(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("fonctions");

    for ( fonctions_const_iterateur it = m_fonctions.constBegin(); it != m_fonctions.constEnd(); ++it )
        (*it)->sauvegarder(stream);

    stream.writeEndElement(); // Fonctions
}

void fonctions_conteneur::clear_fonctions()
{
    for ( fonctions_iterateur it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        delete *it;
    m_fonctions.clear();
}
