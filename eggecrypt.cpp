// Egge Messenger: Basic cryptography
//
// Copyright (C) 2018 Esa Kettunen
//
// Chat program using public key encryption to guarantee secrecy.
//
// SUGARING: 
//   (1) Employing OAEP padding to avoid short messages such as 
//       "Ok" or "Hi" being always encrypted 
//       with the same encoded form.
//   (2) Using RSA key length 2048 just to be on the safe side.
//
// Started by modifying (and rectifying) 
// the original source code for gcrypt-example.
// Copyright (C) 2013  Vedant Kumar <vsk@berkeley.edu>
//
// Also taking excerpts from libgcrypt/tests
// pkcs1v2.c - Test OAEP and PSS padding
// * Copyright (C) 2011 Free Software Foundation, Inc.


#include "eggecrypt.h"
#include <QByteArray>

 
#define my_isascii(c) (!((c) & 0x80))
#define digitp(p)   (*(p) >= '0' && *(p) <= '9')
#define hexdigitp(a) (digitp (a)                     \
                      || (*(a) >= 'A' && *(a) <= 'F')  \
                      || (*(a) >= 'a' && *(a) <= 'f'))
#define xtoi_1(p)   (*(p) <= '9'? (*(p)- '0'): \
                     *(p) <= 'F'? (*(p)-'A'+10):(*(p)-'a'+10))
#define xtoi_2(p)   ((xtoi_1(p) * 16) + xtoi_1((p)+1))
#define DIM(v)		     (sizeof(v)/sizeof((v)[0]))
#define DIMof(type,member)   DIM(((type *)0)->member)


gcry_mpi_t EggeCrypt::random_mpi_init ()
{
  gcry_error_t err = GPG_ERR_NO_ERROR;
  unsigned int key_size = 0;
  gcry_mpi_t data = NULL;

  key_size = 313;
  assert (key_size);

  data = gcry_mpi_new (key_size);
  assert (data);

  gcry_mpi_randomize (data, key_size, GCRY_STRONG_RANDOM);
  gcry_mpi_clear_bit (data, key_size - 1);

  assert (! err);

  return data;
}

/* Convert STRING consisting of hex characters into its binary
   representation and return it as an allocated buffer. The valid
   length of the buffer is returned at R_LENGTH.  The string is
   delimited by end of string.  The function returns NULL on
   error.  */
void * EggeCrypt::data_from_hex (const char *string, size_t *r_length)
{
  const char *s;
  unsigned char *buffer;
  size_t length;

  buffer = (unsigned char *) gcry_xmalloc (strlen(string)/2+1);
  length = 0;
  for (s=string; *s; s +=2 )
    {
      if (!hexdigitp (s) || !hexdigitp (s+1))
        xerr ("error parsing hex string \n");
      ((unsigned char*)buffer)[length++] = xtoi_2 (s);
    }
  *r_length = length;
  return buffer;
}


char * EggeCrypt::getprintablepubkey ()
{
  char *buf;
  size_t size;

  size = gcry_sexp_sprint (m_pubk, GCRYSEXP_FMT_ADVANCED, NULL, 0);
  buf = (char *)gcry_xmalloc (size);

  gcry_sexp_sprint (m_pubk, GCRYSEXP_FMT_ADVANCED, buf, size);
  return buf;
}

void EggeCrypt::show_sexp (const char *prefix, gcry_sexp_t a)
{
  char *buf;
  size_t size;

  if (prefix)
    fputs (prefix, stderr);
  size = gcry_sexp_sprint (a, GCRYSEXP_FMT_ADVANCED, NULL, 0);
  buf = (char *)gcry_xmalloc (size);

  gcry_sexp_sprint (a, GCRYSEXP_FMT_ADVANCED, buf, size);
  fprintf (stderr, "%.*s", (int)size, buf);
  gcry_free (buf);
}



bool EggeCrypt::initialize ()
{
  return readfile ();
}
  

// EggeCrypt::readfile -- Read stored, encrypted keypair from file.
//
//
bool EggeCrypt::readfile ()
{
    gcrypt_init();

    char* fname = (char *)"eggecrypt.dat";
    FILE* lockf = fopen(fname, "rb");
    if (!lockf) {
        xerr("fopen() failed");
	return false;
    }

    /* Grab a key pair password and create an AES context with it. */
    
    QByteArray qba = m_password.toUtf8();
    char * pw = qba.data();
    get_aes_ctx(&m_aes_hd, pw);

    /* Read and decrypt the key pair from disk. */
    size_t rsa_len = get_keypair_size(1024);
    // void* rsa_buf = calloc(1, rsa_len);
    void* rsa_buf = (void *) gcry_xmalloc (rsa_len);

    if (!rsa_buf) {
        xerr("malloc: could not allocate rsa buffer");
	return false;
    }

    if (fread(rsa_buf, rsa_len, 1, lockf) != 1) {
        xerr("fread() failed");
	return false;
    }


    gcry_error_t err;

    err = gcry_cipher_decrypt(m_aes_hd, (unsigned char*) rsa_buf, 
                              rsa_len, NULL, 0);
    if (err) {
        xerr("gcrypt: failed to decrypt key pair");
	return false;
    }

    /* Load the key pair components into sexps. */

    err = gcry_sexp_new(&m_rsa_keypair, rsa_buf, rsa_len, 0);
    if (err) {
        xerr("gcrypt: failed to extract key pair");
	return false;
    }


    m_pubk = gcry_sexp_find_token(m_rsa_keypair, "public-key", 0);
    m_privk = gcry_sexp_find_token(m_rsa_keypair, "private-key", 0);

    free(rsa_buf);
    fclose(lockf);

    return true;
}

bool EggeCrypt::encode (const unsigned char* clearmessage, gcry_sexp_t & cipher)
{
  /* Create a message. */
  gcry_mpi_t msg;
  gcry_sexp_t data;
  const unsigned char* s = clearmessage;
  gcry_error_t err;
  err = gcry_mpi_scan(&msg, GCRYMPI_FMT_USG, s, 
		      strlen((const char*) s), NULL);
  if (err) {
    xerr("failed to create a mpi from the message");
    return false;
  }
  
  // gcry_mpi_t random313 = random_mpi_init();
  
  //    err = gcry_sexp_build(&data, NULL,
  //                     "(data (flags raw) (value %m))", msg);
  err = gcry_sexp_build(&data, NULL,
			"(data (flags oaep)"
			// "(hash-algo sha1)"
			"(value %m)"
			// "(random-override %m)"
			")",
			msg /*,
			      random313 */
			);
  
  {
    
    show_sexp ("data -- \n", data);
    
  }
  
  if (err)
    {
      xerr("failed to create a sexp from the message");
      return false;
    }
  
  /* Encrypt the message. */
  
  err = gcry_pk_encrypt(&cipher, data, m_pubk);
  if (err)
    {
      char tmp[1024];
      gpg_strerror_r(err, tmp, 1024);
      xerr(tmp);
      return false;
    }
  return true;
}

   /* Extract result of RSA operation (i.e. the actual encrypted data)
       from ciph.
    */

bool EggeCrypt::decode (const gcry_sexp_t & ciph,
                        QString & clearmessage)
{
    gcry_sexp_t l1;
    const void *a;
    size_t alen;

    l1 = gcry_sexp_find_token (ciph, "a", 0);
    a = gcry_sexp_nth_data (l1, 1, &alen);
    if (!a)
      {
	xerr ("parameter 'a' missing in key\n");
	return false;
      }


    /* Decrypt the message. */
    gcry_sexp_t plain;
    gcry_sexp_t ciph2; /* egge */
    gcry_error_t err;

    err = gcry_sexp_build (&ciph2, NULL,
			   "(enc-val (flags oaep)"
			   // "(hash-algo sha1)"
			   // "(random-override %m)"
			   "(rsa (a %b)))",
			   // random313,
			   alen, a);

#ifdef EGGECRYPTTEST

      show_sexp ("ciph2 -- \n", ciph2);

#endif

    if (err) {
	char tmp[1024];
	gpg_strerror_r(err, tmp, 1024);

        xerr("gcrypt: building decryption context failed");
	return false;
    }

    err = gcry_pk_decrypt(&plain, ciph2, m_privk);
    if (err) {
	char tmp[1024];
	gpg_strerror_r(err, tmp, 1024);

        xerr("gcrypt: decryption failed");
	return false;
    }

#ifdef EGGECRYPTTEST    

      show_sexp ("plain -- \n", plain);

#endif

    /* Pretty-print the results. */
    gcry_mpi_t out_msg = gcry_sexp_nth_mpi(plain, 1, GCRYMPI_FMT_USG);
    //    printf("Original:\n");
    // gcry_mpi_dump(msg);
    // printf("\n" "Decrypted:\n");
    // gcry_mpi_dump(out_msg);
    // printf("\n");

    // gcry_mpi_t msg;
    // 
    //
    // if (gcry_mpi_cmp(msg, out_msg)) {
    //    xerr("data corruption!");
    //	return false;
    // } 
    //    printf("Messages match.\n");

    unsigned char obuf[64] = { 0 };
    err = gcry_mpi_print(GCRYMPI_FMT_USG, (unsigned char*) &obuf, 
                         sizeof(obuf), NULL, out_msg);
    if (err) {
        xerr("failed to stringify mpi");
	return false;
    }
    // printf("-> %s\n", (char*) obuf);

    clearmessage = QString((char *)obuf);

    /* Release contexts. */
    // gcry_mpi_release(msg);
    gcry_mpi_release(out_msg);
    gcry_sexp_release(ciph);
    gcry_sexp_release(ciph2);
    gcry_sexp_release(plain);
    gcry_cipher_close(m_aes_hd);

    return true;
}


void EggeCrypt::gcrypt_init()
{
    /* Version check should be the very first call because it
       makes sure that important subsystems are intialized. */
    if (!gcry_check_version (GCRYPT_VERSION))
    {
        xerr("gcrypt: library version mismatch");
    }

    gcry_error_t err = 0;

    /* We don't want to see any warnings, e.g. because we have not yet
       parsed program options which might be used to suppress such
       warnings. */
    err = gcry_control (GCRYCTL_SUSPEND_SECMEM_WARN);

    /* ... If required, other initialization goes here.  Note that the
       process might still be running with increased privileges and that
       the secure memory has not been intialized.  */

    /* Allocate a pool of 16k secure memory.  This make the secure memory
       available and also drops privileges where needed.  */
    err |= gcry_control (GCRYCTL_INIT_SECMEM, 16384, 0);

    /* It is now okay to let Libgcrypt complain when there was/is
       a problem with the secure memory. */
    err |= gcry_control (GCRYCTL_RESUME_SECMEM_WARN);

    /* ... If required, other initialization goes here.  */

    /* Tell Libgcrypt that initialization has completed. */
    err |= gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);

    if (err) {
        xerr("gcrypt: failed initialization");
    }
}

size_t EggeCrypt::get_keypair_size(int nbits)
{
    size_t aes_blklen = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES256);

    // format overhead * {pub,priv}key (2 * bits)
    size_t keypair_nbits = 4 * (2 * nbits);

    size_t rem = keypair_nbits % aes_blklen;
    return (keypair_nbits + rem) / 8;
}

void EggeCrypt::get_aes_ctx(gcry_cipher_hd_t* aes_hd, char * passwd)
{
    const size_t keylen = 16;
    char passwd_hash[keylen];
    gcry_error_t err = 0;

    size_t pass_len = passwd ? strlen(passwd) : 0;
    if (pass_len == 0) {
        xerr("getpass: not a valid password");
    }

    err = gcry_cipher_open(aes_hd, 
			   GCRY_CIPHER_AES256, 
			   GCRY_CIPHER_MODE_CFB,
			   0);
    if (err) {
        xerr("gcrypt: failed to create aes handle");
    }

    gcry_md_hash_buffer(GCRY_MD_MD5, (void*) &passwd_hash, 
                        (const void*) passwd, pass_len);

    err = gcry_cipher_setkey(*aes_hd, (const void*) &passwd_hash, keylen);
    if (err) {
        xerr("gcrypt: could not set cipher key");
    }

    err = gcry_cipher_setiv(*aes_hd, (const void*) &passwd_hash, keylen);
    if (err) {
        xerr("gcrypt: could not set cipher initialization vector");
    }
}


void EggeCrypt::xerr(const char* msg)
{
  fprintf(stderr, "Error: %s\n", msg);
}

void EggeCrypt::notify(const char* msg)
{
  fprintf(stderr, "Notification: %s\n", msg);
}


int EggeCrypt::generatekeys()
{
    gcrypt_init();

    char* fname = (char *)"eggecrypt.dat";
    FILE* lockf = fopen(fname, "wb");
    if (NULL == lockf) {
        xerr("fopen() failed");
    }

    /* Generate a new RSA key pair. */
    // printf("RSA key generation can take a few minutes. Your computer \n"
    //       "needs to gather random entropy. Please wait... \n\n");

    gcry_error_t err = 0;
    gcry_sexp_t rsa_parms;
    gcry_sexp_t rsa_keypair;



    //    err = gcry_sexp_build(&rsa_parms, NULL, "(genkey (rsa (nbits 4:1024)))");
    err = gcry_sexp_build(&rsa_parms, NULL, "(genkey (rsa (nbits 4:1024)))");
    if (err) {
        xerr("gcrypt: failed to create rsa params");
    }

    err = gcry_pk_genkey(&rsa_keypair, rsa_parms);
    if (err) {
        xerr("gcrypt: failed to create rsa key pair");
    }

    /*
    printf("RSA key generation complete! Please enter a password to lock \n"
           "your key pair. This password must be committed to memory. \n\n");
    */
    /* Grab a key pair password and create an encryption context with it. */
    gcry_cipher_hd_t aes_hd;
    QByteArray qba = m_password.toUtf8();
    char * pw = qba.data();

    get_aes_ctx(&aes_hd, pw);

    /* Encrypt the RSA key pair. */
    size_t rsa_len = get_keypair_size(1024);
    void* rsa_buf = calloc(1, rsa_len);
    if (!rsa_buf) {
        xerr("malloc: could not allocate rsa buffer");
    }
    gcry_sexp_sprint(rsa_keypair, GCRYSEXP_FMT_CANON, rsa_buf, rsa_len);

    err = gcry_cipher_encrypt(aes_hd, (unsigned char*) rsa_buf, 
                              rsa_len, NULL, 0);
    if (err) {
        xerr("gcrypt: could not encrypt with AES");
    }

    /* Write the encrypted key pair to disk. */
    if (fwrite(rsa_buf, rsa_len, 1, lockf) != 1) {
        perror("fwrite");
        xerr("fwrite() failed");
    }

    /* Release contexts. */
    gcry_sexp_release(rsa_keypair);
    gcry_sexp_release(rsa_parms);
    gcry_cipher_close(aes_hd);
    free(rsa_buf);
    fclose(lockf);

    return 0;
}

EggeCrypt::~EggeCrypt()
{
    gcry_sexp_release(m_rsa_keypair);
    gcry_sexp_release(m_pubk);
    gcry_sexp_release(m_privk);
}
