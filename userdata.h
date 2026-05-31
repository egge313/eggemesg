// UserData -- Current user's relevant information.

#pragma once

#include <QString>
#include <QList>
#include "eggecrypt.h"

class UserData
{
public:

  explicit UserData ( QString user, QString password,
             QString scorchedearthpw, const bool isnew = true ) :
        m_user(user),
        m_password(password),
        m_scorchedearthpassword(scorchedearthpw),
        m_new(isnew),
        m_OwnKeyPair(nullptr)
    {}
  bool readFile ( const QString fileName );
  bool writeFile ( const QString fileName );
  QString getUser() { return m_user; }
  QString getPassword() { return m_password; }
  void setOwnKeyPair ( EggeCrypt * ownKeyPair );
  EggeCrypt * getOwnKeyPair();
  bool writeOwnPubKey ( QString filename );

  ~UserData () { delete m_OwnKeyPair; }

private:
  QString     m_user;
  QString     m_password; // Passwords should be stored as hashes, even in main
                          // memory. So this is wrong. Awfully wrong.
  QString     m_scorchedearthpassword; // Ditto.
  bool        m_new;
  EggeCrypt * m_OwnKeyPair;
};

