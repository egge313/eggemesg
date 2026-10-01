// UserData -- Current user's relevant information.

#pragma once

#include <QString>
#include <QList>
#include "eggecrypt.h"
#include "protectedpage.h"

class UserData
{
public:

  explicit UserData ( QString user,
		      QString password,
		      QString scorchedearthpw,
		      const bool isnew = true ) :
        m_user(user),
        m_scorchedearthpassword(scorchedearthpw),
        m_new(isnew),
        m_OwnKeyPair(nullptr)
    {
	QByteArray ba = password.toLocal8Bit();
	const char * pw = ba.data();
	m_password.dowrite ( pw, strlen(pw) );
    }

private:

    // Forbid copy constructor.
    UserData(UserData const &);

    // Forbid assignment operator.
    UserData& operator=(UserData const &);

public:    

    bool readFile ( const QString fileName );
    bool writeFile ( const QString fileName );
    QString getUser() { return m_user; }
    QString getPassword(); 
    void setOwnKeyPair ( EggeCrypt * ownKeyPair );
    EggeCrypt * getOwnKeyPair();
    bool writeOwnPubKey ( QString filename );

    ~UserData () { delete m_OwnKeyPair; }

private:
  QString         m_user;
  ProtectedPage   m_password; // Passwords should be stored as hashes,
                              // even in main
                              // memory. So this is so wrong. Awfully wrong.
  QString         m_scorchedearthpassword; // Ditto.
  bool            m_new;
  EggeCrypt *     m_OwnKeyPair;
};

