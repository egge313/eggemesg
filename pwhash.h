// PwHash -- Password hash employing libsodium.

#pragma once

#include <QString>

class PwHash 
{
private:
   enum FileError { eNoError, eError };

public:
   explicit PwHash () { initialize(); };

   // Create a password hash.
   bool createHash ( const QString pw, const QString user );
   
   // Verify that a given password matches the hash.
   bool verify ( const QString given_pw, const QString user );

   bool readFile ();

   bool writeFile ();

   ~PwHash () {};
   
private:
   
   bool initialize ();

   virtual void xerr ( const QString errmsg );
   
   
   
private:
   
   QString m_hashedPw;
   QString m_user;
   
};

// --- end of pwhash.h ---
