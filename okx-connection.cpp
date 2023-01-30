#include <iostream>
#include <cpr/cpr.h>
using namespace std;

int main() {
    auto response = cpr::Get(cpr::Url{"https://www.okex.com/api/v5/market/trades?instId=BTC-USDT"});
    cout << response.status_code << endl;
    cout << response.text << endl;
    return 0;
}