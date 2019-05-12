#include <curl/curl.h>
#include <iostream>

#include "common.hh"
#include "url.hh"

int curl_GET(const std::string& url)
{

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Don't verify CAcert or host
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            err("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        // Cleanup
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    std::cout << std::endl;
}
