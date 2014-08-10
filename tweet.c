#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <curl/curl.h>

CURL *curl;
CURLcode res;

char *oauth_consumer_key = "PuwsYiFuQyGsEJZ9hHofGQtW3";
char *oauth_nonce = "8a127998f9b4b47f15e90868d88a364d";
char *oauth_signature = "NizxGYiGC6iRvFQTCGXHBIMvvGM%3D";
char *oauth_signature_method = "HMAC-SHA1";
char *oauth_timestamp = "1407636076";
char *oauth_token = "620331547-x2XviwVplG1rawauTMgOKq4Mew4MyddEbGDCXnQ2";
char *oauth_version="1.0";

/*

Authorization: OAuth oauth_consumer_key="PuwsYiFuQyGsEJZ9hHofGQtW3", oauth_nonce="8a127998f9b4b47f15e90868d88a364d", oauth_signature="NizxGYiGC6iRvFQTCGXHBIMvvGM%3D", oauth_signature_method="HMAC-SHA1", oauth_timestamp="1407636076", oauth_token="620331547-x2XviwVplG1rawauTMgOKq4Mew4MyddEbGDCXnQ2

*/

char *response;

/* Callback to change return value to string to be parsed. */
void callback(void *buffer, size_t size, size_t nmemb, void *userp) {
    response = buffer;
}

char* headers() {
    char *auth = "Authorization: OAuth oauth_consumer_key=\"PuwsYiFuQyGsEJZ9hHofGQtW3\", oauth_nonce=\"8a127998f9b4b47f15e90868d88a364d\", oauth_signature=\"NizxGYiGC6iRvFQTCGXHBIMvvGM%3D\", oauth_signature_method=\"HMAC-SHA1\", oauth_timestamp=\"1111111111\", oauth_token=\"620331547-x2XviwVplG1rawauTMgOKq4Mew4MyddEbGDCXnQ2\"";

char buf[strlen(auth)+ 1000];

    sprintf(buf, "Authorization: OAuth oauth_consumer_key=\"PuwsYiFuQyGsEJZ9hHofGQtW3\", oauth_nonce=\"8a127998f9b4b47f15e90868d88a364d\", oauth_signature=\"NizxGYiGC6iRvFQTCGXHBIMvvGM%3D\", oauth_signature_method=\"HMAC-SHA1\", oauth_timestamp=\"%lu\", oauth_token=\"620331547-x2XviwVplG1rawauTMgOKq4Mew4MyddEbGDCXnQ2\"", 1234123412);
printf("%s", buf);
    return buf;
}

int main (int argc, char **argv) {

    struct curl_slist *chunk = NULL;
 
    chunk = curl_slist_append(chunk, headers());

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if(curl) {
        /* POST URL */
        curl_easy_setopt(curl, CURLOPT_URL, "http://api.twitter.com/1.1/statuses/mentions_timeline.json");

        /* POST form */
        //curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        /* Make return data a buffer */
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

        /* passing the pointer to the response as the callback parameter */
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        /* Perform the request */
        res = curl_easy_perform(curl);

//printf("%s", response);

        /* Check for errors */
        if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    curl_slist_free_all(chunk);
    return 0;
}