#include <QString>
#include <curl/curl.h>

// curlpostdata -- Send binary data over Tor network. Length of data in 
//                 datalength. Onion address in torserver. Return 0 on
//                 success, 1 on failure, upon which errmsg may explain 
//                 something.
//                 Max data length is 512.
int curlpostdata (const char* data,
		  const int datalength,
		  const char* torserver,
		  QString & errmsg)
{
    CURL *curl;
    CURLcode res;
    boolean success = true;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl) 
      {
	curl_easy_setopt(curl, CURLOPT_URL, torserver);

        curl_easy_setopt(curl, CURLOPT_PROXY, "socks5h://localhost:9050");

	struct curl_slist *list = NULL;
 
	list = curl_slist_append(list, "Content-Type");
	list = curl_slist_append(list, "application/octet-stream");
 
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, datalength);
  
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        res = curl_easy_perform(curl);
	std::cout << "Done talking 1.";
        if(res != CURLE_OK)
	  {
            errmsg << "Error: curl_easy_perform() failed: "
		   << curl_easy_strerror(res);
	    success = false;
	  }
	
        curl_easy_cleanup(curl);

      }

    curl_global_cleanup();

    return (int) !success;
}

