// pacman_core.cpp
// Compile: g++ -std=c++17 pacman_core.cpp -o pacman_core
// Requires: nlohmann/json.hpp (https://github.com/nlohmann/json single header)

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h> // for sockets
#include "json.hpp"    // https://github.com/nlohmann/json

using json = nlohmann::json;

std::atomic<bool> running(true);
int pacman_x = 5, pacman_y = 5;
int sock_fd;

// Send state to Python server
void send_state_to_server() {
    json state = {
        {"x", pacman_x},
        {"y", pacman_y}
    };

    std::string msg = state.dump();
    send(sock_fd, msg.c_str(), msg.size(), 0);
}

// Receive command from Python server
void receive_commands_from_server() {
    char buffer[1024] = {0};
    int valread = recv(sock_fd, buffer, 1024, MSG_DONTWAIT);
    if (valread > 0) {
        std::string data(buffer, valread);
        if (data == "up") pacman_y--;
        else if (data == "down") pacman_y++;
        else if (data == "left") pacman_x--;
        else if (data == "right") pacman_x++;
        else if (data == "stop") running = false;
    }
}

int main() {
    struct sockaddr_in serv_addr;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5555);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return -1;
    }

    std::cout << "Connected to Python server!\n";

    while (running) {
        send_state_to_server();
        receive_commands_from_server();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    close(sock_fd);
    std::cout << "Game stopped.\n";
    return 0;
}
