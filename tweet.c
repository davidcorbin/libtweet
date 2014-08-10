#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <curl/curl.h>

int main (int argc, char **argv) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if(curl) {
        /* POST URL */
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.twitter.com/1.1/statuses/mentions_timeline.json");

        /* POST form */
        //curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        /* Make return data a buffer */
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

        /* passing the pointer to the response as the callback parameter */
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        /* Perform the request */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(error == 1 && res != CURLE_OK)
            (stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    return 0;
}