// #include<websocketpp/config/asio_no_tls_client.hpp>
// #include<websocketpp/client.hpp>
// #include<iostream>
// #include<nlohmann/json.hpp>

// using json = nlohmann::json;
// typedef websocketpp::client<websocketpp::config::asio_no_tls_client> client;

// void on_message(websocketpp::connection_hdl, client::message_ptr msg){
//     auto j = json::parse(msg->get_payload());
//     auto bids = j["bids"];
//     auto asks = j["asks"];

//     std::cout<<"Top bid:"<< bids[0][0] << " ("<<bids[0][1] <<")\n";
//     std::cout<<"Top ask:"<< asks[0][0] << " ("<<asks[0][1] <<")\n";

// }

// int main(){
//     client c;

//     c.init_asio();
//     std::string uri = "wss://stream.binance.com:9443/ws/btcusdt@depth20@100ms";
//     c.set_message_handler(&on_message);

//     websocketpp::lib::error_code ec;
//     auto con = c.get_connection(uri, ec);
//     if(ec){
//         std::cout<< "Connection failed: "<<ec.message() <<std::endl;
//         return -1;
//     }

//     c.connect(con);
//     c.run();
// }


#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "curl_easy_init() failed\n";
        return 1;
    }

    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v3/depth?symbol=BTCUSDT&limit=10");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/OrderBookData");

    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK){
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        return 2;
    }
    if(http_code != 200){
        std::cerr << "HTTP response code: " << http_code << "\n";
        return 3;
    }
    if(readBuffer.empty()){
        std::cerr << "Empty response\n";
        return 4;
    }

    try{
        json j = json::parse(readBuffer);
        if (!j.contains("bids") || !j.contains("asks") || j["bids"].empty() || j["asks"].empty()) {
            std::cerr << "Unexpected JSON structure\n";
            return 5;
        }
        std::cout << "Top bid: " << j["bids"][0][0] << " (" << j["bids"][0][1] << ")\n";
        std::cout << "Top ask: " << j["asks"][0][0] << " (" << j["asks"][0][1] << ")\n";
        
    }catch (const std::exception &e) {
        std::cerr << "JSON parse/error: " << e.what() << "\n";
        return 6;
    }

    return 0;
}

