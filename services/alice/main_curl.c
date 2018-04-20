#include <stdio.h>
#include <curl/curl.h>

#include <fnode/service.h>

void postToSpeech(CURL *, const char *);
void postToReplay(CURL *);

CURL * curl = NULL;

void handler(uint32_t cmd, char const * data) {
  postToSpeech(curl, data); 
}

int main(int argc, char ** argv) {
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if ( !curl ) {
    fprintf(stderr, "Failed to init curl driver\n");
    return 1;
  }

  // Creating service
  fnode_service_t * service = fnode_service_create("alice007", "TDAC");

  if ( !service ) {
    fprintf(stderr, "Failed to create TDAC service\n");
    return -1;
  }

  fnode_service_reg_handler(service, handler);

  for(;;) {
    fnode_service_update(service);
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  fnode_service_release(service);
  return 0;
}

void postToSpeech(CURL * curl, const char * text) {
  curl_easy_reset(curl);

  curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/play");

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, text); 

  struct curl_slist * headers = NULL;
  headers = curl_slist_append(headers, "Content-Type; text/html");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  CURLcode res;
  res = curl_easy_perform(curl);

  if ( res != CURLE_OK ) {
    fprintf(stderr, "Query failed: %s\n",
        curl_easy_strerror(res));
  }

  curl_slist_free_all(headers);
}

void postToReplay(CURL * curl) {
  curl_easy_reset(curl);

  curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/replay");

  CURLcode res;
  res = curl_easy_perform(curl);

  if ( res != CURLE_OK ) {
    fprintf(stderr, "Query failed: %s\n",
        curl_easy_strerror(res));
  }
}
