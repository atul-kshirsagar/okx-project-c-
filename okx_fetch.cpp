#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using namespace std;

using json = nlohmann::json;

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        auto response = cpr::Get(cpr::Url{"https://www.okex.com/api/v5/market/trades?instId=BTC-USDT"});

        if (response.status_code == 200) {
            auto data = json::parse(response.text);
            // Print the first trade's price and amount
            //std::cout << "Price: " << data[0]["price"] << ", Amount: " << data[0]["amount"] << std::endl;
            std::cout<<data<<std::endl;
        } else {
            // Handle error
            std::cerr << "Request failed with status code: " << response.status_code << std::endl;
            std::cout << response.error.message << endl;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        if (duration >= 60) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}