#include "displayablecontacts.h"

static unsigned contactNumber = 1;

void DisplayableContacts::addContact ( const QString & _fileName,
				       const QString & _name )
{
   MyContact contact;

   if ( find ( _name, contact ))
      {
	 if ( contact.fileName == _fileName )
	    {
	       // It's already there.
	       return;
	    }
      }

   MyContact* contactPtr = new MyContact;
   contactPtr->fileName = _fileName;
   contactPtr->index = contactNumber++;
   contactPtr->inUse = true;
   contactPtr->name = _name;
   m_contacts.append ( contactPtr );
}

bool DisplayableContacts::find (const QString & _name, MyContact & contact )
{
   for (qsizetype i = 0; i < m_contacts.size(); ++i) 
      {
	 if ( m_contacts.at(i)->name == _name)
	    {
	       contact = *m_contacts.at(i);
	       return true;
	    }
      }
   return false;
}

bool DisplayableContacts::removeContact ( const QString & _name )
{
   for (qsizetype i = 0; i < m_contacts.size(); ++i) 
      {
	 if ( m_contacts.at(i)->name == _name)
	    {
	       m_contacts.removeAt(i);
	       return true;
	    }
      }
   return false;

}

DisplayableContacts::~DisplayableContacts()
{
   for (qsizetype i = 0; i < m_contacts.size(); ++i) 
      {
	 MyContact* contactptr = m_contacts.at(i);
	 delete contactptr;
	 m_contacts.removeAt(i);

      }
}

// --- end displayablecontacts.cpp ---
