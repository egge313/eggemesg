#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "contacts.h"

// Curiously, we require unique names and unique pubkeys.

bool Contacts::insert (const QString _name, const QString _pubkey , const QString _address)
{
  QString pk;
  QString nm;
  QString ad;

  if (( findByName ( _name, pk, ad ) && pk == _pubkey ) ||
      ( findByPubKey ( _pubkey, nm, ad ) && nm == _name ))
    return false;
  else
    {
      ContactEle * cele = new ContactEle();
      cele->name = _name;
      cele->pubkey = _pubkey;
      cele->address = _address;
      storage.append ( cele );
      return true;
    }
}

bool Contacts::findByName ( const QString _name, QString & _pubkey, QString & _address ) const
{
  for ( int i = 0; i < storage.length(); i++ )
    {
      if ( storage[i]->name == _name )
        {
            _pubkey = storage[i]->pubkey;
            _address = storage[i]->address;
             return true;
        }
    }
  return false;
}

bool Contacts::findByPubKey ( const QString _pubkey, QString & _name, QString _address ) const
{
  for ( int i = 0; i < storage.length(); i++ )
    {
      if ( storage[i]->pubkey == _pubkey ) 
        {
            _name = storage[i]->name;
            _address = storage[i]->address;
            return true;
        }
    }
  return false;
}

bool Contacts::getJson ( QJsonDocument & jsonDoc ) const
{
    QJsonArray array;

    for ( int i = 0; i < storage.length(); i++ )
    {
        QJsonObject mycontact;
        mycontact["name"] = storage[i]->name;
        mycontact["pubKey"] = storage[i]->pubkey;
        mycontact["address"] = storage[i]->address;
        array.append( mycontact );
    }

    QJsonObject root;

    root["contacts"] = array;

    jsonDoc = QJsonDocument ( root );
    return true;
}

bool Contacts::insertJson ( const QJsonDocument & jsonDoc )
{
    QJsonObject rootObj = jsonDoc.object();
    if(rootObj.contains("contacts"))
    {
        QJsonArray array = rootObj.value("contacts").toArray();
        for ( auto jsonObj : array )
        {
            QString _name = jsonObj.toObject().value("name").toString();
            QString _pubkey = jsonObj.toObject().value("pubKey").toString();
            QString _address = jsonObj.toObject().value("address").toString();
            QString dummyPubKey;
            QString dummyName;
            QString dummyAddress;
            if ( findByName(_name, dummyPubKey, dummyAddress ) || findByPubKey(_pubkey, dummyName, dummyAddress ) )
                insert ( _name, _pubkey, _address );
        }

    }
    else
    {
        qDebug() << "Contacts::insertJson: missing contacts.\n";
        return false;
    }

    return true;
}

Contacts::~Contacts ()
{
  for ( int i = 0; i < storage.length(); i++ )
    {
      delete storage[i];
    }
}
