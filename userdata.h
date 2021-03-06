#ifndef USERDATA_H
#define USERDATA_H 1

#include <QString>

class UserData
{
public:
  QString m_user;
  QString m_password; // Passwords should be stored as hashes, even in main
                      // memory.
  QString m_scorchedearthpassword; // Ditto.
  bool    m_new;

  UserData (QString user, QString password, 
	    QString scorchedearthpw, const bool isnew) : 
  m_user(user), m_password(password), 
    m_scorchedearthpassword(scorchedearthpw), m_new(isnew) {} 
  ~UserData () {}
};

#endif
