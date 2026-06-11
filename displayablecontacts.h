#pragma once

#define CONTACTS_SIZE 7

#include <QString>
#include <QList>

class DisplayableContacts
{

public:

   struct MyContact
   {
      QString fileName;
      unsigned index;
      bool inUse;
      QString name;
   };

public:
   explicit DisplayableContacts() {};

   void addContact ( const QString & _fileName, const QString & _name );

   bool find (const QString & _name, MyContact & contact );

   bool removeContact ( const QString & _name );

   ~DisplayableContacts();

private:
   QList<MyContact*> m_contacts;
};
