#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <curl/curl.h>

#include "cfetch.h"

struct curl_string {
    char *ptr;
    size_t len;
};

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    struct curl_string *s = (struct curl_string *)userdata;
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 0;
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    //s->ptr[new_len] = '\0';
    s->len = new_len;
    return size * nmemb;
}

char * cfetch(char *url, size_t *len) {

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Failed to initialize curl\n");
        return NULL;
    }

    struct curl_string s = {
        .ptr = NULL,
        .len = 0
    };
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to fetch url: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return NULL;
    }

    curl_easy_cleanup(curl);

    *len = s.len;
    return s.ptr;

}
