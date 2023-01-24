#include <bits/stdc++.h>
#include <curl/curl.h>

size_t WriteCallback(char *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append(contents, size * nmemb);
    return size * nmemb;
}


int main() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.okx.com/api/v5/rfq/public-trades");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "API-Key: your-api-key");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }
    return 0;
}
