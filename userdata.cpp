#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QtGlobal>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include "eggecrypt.h"
#include "userdata.h"


bool UserData::readFile ( const QString fileName )
{
   // 2. Now read it back in
   QJsonParseError parseError;
   QJsonDocument doc2;
   {
      QFile fin ( fileName );
      fin.open(QIODevice::ReadOnly);
      QByteArray ba2 = fin.readAll();
      doc2 = QJsonDocument::fromJson(ba2, &parseError);
      fin.close();
   }

   if (parseError.error != QJsonParseError::NoError)
      {
	 qWarning() << "Parse error at" << parseError.offset << ":" 
		    << parseError.errorString();
	 return false;
      }
   else
      {
	 qDebug() << "parsed JSON\n";
	 qDebug() << doc2.toJson(QJsonDocument::Indented);
	 //or QJsonDocument::Indented for a JsonFormat
      }

   // Now extract the proper fields of UserData from the JSON.
   QJsonObject rootObj = doc2.object();
   if(rootObj. contains("UserName"))
      {
	 QJsonObject subObj = rootObj.value("UserName").toObject();
	 qDebug() << subObj.value("UserName").toString();
     m_user = subObj.value("UserName").toString();
      }
   else
      {
	 qDebug() << "UserData::readFile: missing UserName\n";
	 return false;
      }

   if(rootObj.contains("Password"))
      {
	 QJsonObject subObj = rootObj.value("Password").toObject();
	 qDebug() << subObj.value("Password").toString();
	 m_password = subObj.value("Password").toString();
      }
   else
      {
	 qDebug() << "UserData::readFile: missing Password\n";
	 return false;
      }

   if(rootObj.contains("ScorchedEarthPassword"))
      {
	 QJsonObject subObj = rootObj.value("ScorchedEarthPassword").toObject();
	 qDebug() << subObj.value("ScorchedEarthPassword").toString();
	 m_scorchedearthpassword = subObj.value("ScorchedEarthPassword").toString();
      }
   else
      {
	 qDebug() << "UserData::readFile: missing ScorchedEarthPassword\n";
	 return false;
      }

   if(rootObj.contains("KeyPair"))
      {
	 QJsonObject subObj = rootObj.value("KeyPair").toObject();
	 qDebug() << subObj.value("KeyPair").toString();
	 // m_OwnKeyPair = subObj.value("KeyPair").toString(); /* egge: needing  a new constructor for EggeCrypt */
      }
   else
      {
	 qDebug() << "UserData::readFile: missing KeyPair\n";
	 return false;
      }

   return true;
}
bool UserData::writeFile ( const QString fileName )
{
  QJsonObject root;

  root["UserName"] = m_user;
  root["Password"] = m_password;
  root["ScorchedEarthPassword"] = m_scorchedearthpassword;
  root["KeyPair"] = m_OwnKeyPair == nullptr
     ? QString ( "nullptr" ) 
     : m_OwnKeyPair->getKeyPairAsString();

  /*
  QJsonArray knownPublicKeys;
  if ( ! m_KnownPublicKeys.isEmpty() )
    {
      for (int i = 0; i < m_KnownPublicKeys.count(); i++ )
        {
          knownPublicKeys.append ( (char *)m_KnownPublicKeys[i] );
        }
    }
  root["KnownPublicKeys"] = knownPublicKeys;
    */

  // `ba` contains JSON
  QByteArray ba = QJsonDocument(root).toJson();

  qDebug() << "rendered JSON:\n" ;
  qDebug() << ba;
  {
    QFile fout( fileName );
    fout.open ( QIODevice::WriteOnly );
    fout.write ( ba );
    fout.close();
  }
  return true;
}

bool UserData::writeOwnPubKey ( const QString fileName )
{
    QJsonObject root;

    root["UserName"] = m_user;
    QString pubkey = "";
    m_OwnKeyPair->getPrintablePubKey( pubkey );
    if ( m_OwnKeyPair == nullptr || pubkey == "" )
    {
        return false;
    }

    root["PubKey"] = m_OwnKeyPair == nullptr ? QString ( "nullptr" ) : pubkey;

    // `ba` contains JSON
    QByteArray ba = QJsonDocument(root).toJson();

    qDebug() << "rendered JSON:\n" ;
    qDebug() << ba;
    {
        QFile fout( fileName );
        fout.open(QIODevice::WriteOnly);
        fout.write(ba);
        fout.close();
    }
    return true;
}

void UserData::setOwnKeyPair ( EggeCrypt * ownKeyPair )
{
    m_OwnKeyPair = ownKeyPair;
}

EggeCrypt * UserData::getOwnKeyPair()
{
    return m_OwnKeyPair;
}

// --- end of userdata.cpp ---

