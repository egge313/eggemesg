#pragma once

// contacts.h -- Storage for Eggemesg counterparts with which the user
//            -- can communicate.

#include <QString>
#include <QList>
#include <QJsonDocument>

class Contacts
{

private:
  struct ContactEle
  {
    QString name;
    QString pubkey;
    QString address;
  };

public:
  explicit Contacts () {};
  ~Contacts ();

  bool insert ( const QString _name,
		const QString _pubkey,
		const QString _address );
  bool findByName ( const QString _name,
		    QString & _pubkey,
		    QString & _address ) const;
  bool findByPubKey (const QString _pubkey,
		     QString & _name,
		     QString _address) const;
  bool getJson ( QJsonDocument & jsonDoc ) const;
  bool insertJson ( const QJsonDocument & jsonDoc );

private:

  QList<ContactEle*> storage;

};
