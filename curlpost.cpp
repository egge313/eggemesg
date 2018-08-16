#include <stdio.h>
#include <curl/curl.h>
#include "curlpost.h"

void Curlpost::init ()
{
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
}


void Curlpost::cleanup ()
{
    curl_global_cleanup();
}


static size_t WriteCallback(void *contents, size_t size,
			    size_t nmemb, void *userp)
{
    ((QString*)userp)->append((const char*)contents);
    return size * nmemb;
}


// Curlpost::is_Tor_on -- Check if Tor circuit is active on this host
//
bool Curlpost::is_Tor_on (const int torport)
{
  CURL *curl;
  CURLcode res;
  bool retval = true;
  QString readbuffer = "";

  curl = curl_easy_init();
  if(curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL, 
		     "https://check.torproject.org");

      /* request to use a SOCKS5 proxy */
      curl_easy_setopt(curl, CURLOPT_PROXY, "localhost:9050");
 
      curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);

      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readbuffer);
  
      /* Perform the request, res will get the return code */
      res = curl_easy_perform(curl);

      /* Check for errors */
      if(res != CURLE_OK)
	{
	  QString err = "Failure: curl_easy_perform: ";
	  err.append (curl_easy_strerror(res));
	  CurlpostException cpex (err);
	  throw (cpex);
	}
      /* always cleanup */
      curl_easy_cleanup(curl);
    }

  return readbuffer.contains("Congratulations");
}

void Curlpost::send (const QString & target,
		     const QByteArray & data, 
		     QString & readbuffer,
		     bool useTorProxy)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers=NULL;
  char * targetstr;

  /* get a curl handle */ 
  curl = curl_easy_init();
  if (curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 

    QByteArray ba = target.toLatin1();
    targetstr = (char *)ba.data();
    curl_easy_setopt(curl, CURLOPT_URL, targetstr);
  }
  else
    {
      CurlpostException cpex ("Failure: curl_easy_init");
      curl_easy_cleanup(curl);

      throw (cpex);
    }

  if (useTorProxy)
    {
      /* request to use a SOCKS5 proxy */
      curl_easy_setopt(curl, CURLOPT_PROXY, "localhost:9050");
      curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5_HOSTNAME);
    }

  headers = curl_slist_append(headers, "Content-Type: binary");
 
  /* post binary data */
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.data());
  
  /* set the size of the postfields data */
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size() + 1);
  
  /* pass our list of custom made headers */
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readbuffer);
  
  res = curl_easy_perform(curl);
  /* Check for errors */ 
  if(res != CURLE_OK)
    {
      QString err = "Failure: curl_easy_perform: ";
      err.append (curl_easy_strerror(res));
      CurlpostException cpex (err);
      /* always cleanup */ 
      curl_slist_free_all(headers); /* free the header list */
  
      curl_easy_cleanup(curl);

      throw (cpex);
    }

  /* always cleanup */ 
  curl_slist_free_all(headers); /* free the header list */
  
  curl_easy_cleanup(curl);

}
