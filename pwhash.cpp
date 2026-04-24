#include "pwhash.h"
#include "sodium.h"
#include <iostream>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

// Set things up for other operations. Has to be invoked before anything else.
//
bool PwHash::initialize ()
{
   static bool isInitialized = false;
   
   if ( !isInitialized )
      {
         if ( sodium_init () == 0 )
            {
               isInitialized = true;
            }
         else
            {
               xerr ( "PwHash: Cannot initialize sodium." );
               return false;
            }
      }
   return true;
}

// Create a hash for a user's password.
//
bool PwHash::createHash ( const QString pw, const QString user )
{
   char hashed_password[crypto_pwhash_STRBYTES];  
   const char* mypw = pw.toLocal8Bit().data();

   if ( crypto_pwhash_str ( hashed_password,
                            mypw,
                            strlen(mypw),
                            crypto_pwhash_OPSLIMIT_SENSITIVE,
                            crypto_pwhash_MEMLIMIT_SENSITIVE ) != 0)
      {
         xerr ( "PwHash::createHash: Out of memory." );
         return false;
      }
   
   m_hashedPw = hashed_password;
   m_user = user;
   writeFile();
   
   return true;
}

// The error notification method. Virtual.
//
void PwHash::xerr ( const QString errmsg )
{
    qWarning() << errmsg << "\n";
}

// Verify that a given password matches the hash.
bool PwHash::verify ( const QString given_pw, const QString user )
{
   const char* pw = given_pw.toLocal8Bit().data();
   const char* hpw = m_hashedPw.toLocal8Bit().data();

   if ( user == m_user )
   {
       if ( crypto_pwhash_str_verify ( hpw,
                                   pw,
                                   strlen ( pw )) != 0)
      {
         xerr ( "Incorrect user or password." );
         return false;
      }
   }
   else
   {
       xerr ( "Incorrect user or password." );
       return false;
   }
   return true;
}

// Read password information from file.
//
bool PwHash::readFile ()
{
   // 2. Now read it back in
   QJsonParseError parseError;
   QJsonDocument doc2;

   try
      {
         {
            QFile fin(".eggemesgpw");
            if ( !fin.exists() )
               {
                  xerr ( "There are no registered users." );
                  throw eError;
               }
            fin.open(QIODevice::ReadOnly);
            QByteArray ba2 = fin.readAll();
            doc2 = QJsonDocument::fromJson(ba2, &parseError);
            fin.close();
         }

         if (parseError.error != QJsonParseError::NoError)
            {
               qWarning() << "Parse error at" << parseError.offset << ":" 
                          << parseError.errorString();
               throw eError;
            }
         else
            {
               qDebug() << "parsed JSON\n";
               qDebug() << doc2.toJson(QJsonDocument::Indented);
               //or QJsonDocument::Indented for a JsonFormat
            }

         // Now extract the proper fields of UserData from the JSON.
         QJsonObject rootObj = doc2.object();
         if(rootObj. contains("username"))
            {
               QJsonObject subObj = rootObj.value("username").toObject();
               qDebug() << subObj.value("username").toString();
               m_user = rootObj.value("username").toString();
            }
         else
            {
               qDebug() << "UserData::readFile: missing username\n";
               throw eError;
            }

         if(rootObj.contains("pwhash"))
            {
               QJsonObject subObj = rootObj.value("pwhash").toObject();
               qDebug() << subObj.value("pwhash").toString();
               m_hashedPw = rootObj.value("pwhash").toString();
            }
         else
            {
               qDebug() << "UserData::readFile: missing pwhash\n";
               throw eError;
            }
      }
   catch (FileError fe)
      {
         return false;
      }
   return true;
}

bool PwHash::writeFile ()
{
   QJsonObject root;

   root["username"] = m_user;
   root["pwhash"] = m_hashedPw;

   QByteArray ba = QJsonDocument(root).toJson();

   qDebug() << "rendered JSON:\n" ;
   qDebug() << ba;
   {
      QFile fout( ".eggemesgpw" );
      fout.open( QIODevice::WriteOnly );
      fout.write( ba );
      fout.close();
   }
   return true;
}

// ---- end pwhash.cpp ----
