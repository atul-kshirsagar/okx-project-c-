#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <fstream>

using json = nlohmann::json;

static std::string data;

size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
  data.append(ptr, size * nmemb);
  return size * nmemb;
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  while (true) {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if(curl) {
        //curl_easy_setopt(curl, CURLOPT_URL, "https://www.okx.com/api/v5/market/trades?instId=BTC-USDT");
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.okx.com/api/v5/market/books?instId=BTC-USDT");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
        }

        std::cout << data << std::endl;

        //json root;
        //bool parsingSuccessful = root.parse(data);
        //if (!parsingSuccessful) {
        //std::cout << "Failed to parse JSON" << std::endl;
        //return 1;
        //}
        //json bids = root["bids"];
        //json asks = root["asks"];

        // Write data to a JSON file
        std::ofstream jsonFile;
        jsonFile.open("data.json");
        jsonFile << data;
        jsonFile.close();


        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        if (duration >= 60) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        }
  return 0;
}