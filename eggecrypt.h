// EggeCrypt -- An RSA interface.

#pragma once

#include <QString>
#include <assert.h>
#include <gcrypt.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

class EggeCrypt {

public:
   EggeCrypt (const QString & user, const QString & password) :
      m_aes_hd_ptr ( nullptr ),
      m_rsa_keypair_ptr ( nullptr ),
      m_pubk_ptr ( nullptr ),
      m_privk_ptr ( nullptr )
   {
      m_user = user;
      m_password = password;
   }

   bool initialize ();

   // Encrypt a message using your own public key.
   bool encode (const unsigned char* clearmessage, gcry_sexp_t & ciph);

   // Encrypt a message using some other public key.
   bool encode (const unsigned char* clearmessage, 
		const gcry_sexp_t & pubk, 
		gcry_sexp_t & ciph);

   // Encrypt a message using some other public key.
   bool encode (const unsigned char* clearmessage,
		const QString & pubk,
		gcry_sexp_t & ciph);

   // Decrypt a message using your own keypair.
   bool decode (const gcry_sexp_t & ciph, QString & clearmessage);

   /* Crash routine. */
   virtual void xerr(const char* msg);

   // User notification routine.
   virtual void notify(const char* msg);

   /* Generate keypair */
   int generatekeys();

   QString getKeyPairAsString();
   EggeCrypt * getKeyPair() { return this; }

   /* Get printable key */
   bool getPrintablePubKey ( QString & pubkey );

   // Get pubkey into a form that can be part of a JSON file.
   bool pubKeyToBase64 ( QString & pubkey64 );

   // Get the JSON form of pubkey back to a pubkey.
   bool base64ToPubKey ( const QString & pubkey64 );

   // Convert a key pair represented as an S-expression string back to its
   // EggeCrypt representation.
   //
   bool convertFromString ( const QString keyPair );

   virtual ~EggeCrypt ();

private:
   /* Initialize libgcrypt. */
   void gcrypt_init();

   gcry_mpi_t random_mpi_init ();
   void * data_from_hex (const char *string, size_t *r_length);
   void show_sexp (const char *prefix, gcry_sexp_t a);
   bool readfile ();

   /* Estimate the size of the encrypted key pair. */
   size_t get_keypair_size(int nbits);

   /* Create an AES context out of a user's password. */
   void get_aes_ctx(gcry_cipher_hd_t* aes_hd, char* password);

private:
   QString m_user;
   QString m_password;
   gcry_cipher_hd_t * m_aes_hd_ptr;
   gcry_sexp_t * m_rsa_keypair_ptr;
   gcry_sexp_t * m_pubk_ptr;
   gcry_sexp_t * m_privk_ptr;
};

// --- end of eggecrypt.h ---
