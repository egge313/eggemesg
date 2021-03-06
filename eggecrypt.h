#ifndef EGGECRYPT_H
#define EGGECRYPT_H 1

#include <QString>
#include <assert.h>
#include <gcrypt.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

class EggeCrypt {

 public:
  EggeCrypt (const QString & user, const QString & password)
    {
      m_user = user;
      m_password = password;
    }
  bool initialize ();
  bool encode (const unsigned char* clearmessage, gcry_sexp_t & ciph);
  bool decode (const gcry_sexp_t & ciph, QString & clearmessage);

  /* Crash routine. */
  virtual void xerr(const char* msg);
  virtual void notify(const char* msg);

  /* Generate keypair */
  int generatekeys();

  /* Get printable key */
  char * getprintablepubkey();

  ~EggeCrypt ();

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
  gcry_cipher_hd_t m_aes_hd;
  gcry_sexp_t m_rsa_keypair;
  gcry_sexp_t m_pubk;
  gcry_sexp_t m_privk;
};

#endif // EGGECRYPT_H
