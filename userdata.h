#ifndef USERDATA_H
#define USERDATA_H 1

#include <QString>

class UserData
{
public:
  QString m_user;
  QString m_password;
  bool    m_new;

  UserData (QString user, QString password, const bool isnew) : 
  m_user(user), m_password(password), m_new(isnew) {} 
  ~UserData () {}
};

#endif
