#include "libs/Server/server.hpp"
#define SOCKET_PORT 8000
#define MAX_LEN 65534
// using json = nlohmann::json;
using udp = boost::asio::ip::udp;


int main(int argc, char **argv) {
    if (argc < 3){
        std::cout << "Main usage: path_to_program <ip_dest> <port_dest>" << std::endl;
        return 0;
    }

    boost::asio::io_service io_service;
    auto socket = udp::socket(io_service, udp::endpoint(udp::v4(), 0));
    auto resolver = udp::resolver(io_service);
    auto destination = *resolver.resolve(udp::v4(), argv[1], argv[2]).begin();
    udp::endpoint server;

    std::string message;
    while (std::cin >> message){
        socket.send_to(boost::asio::buffer(message), destination);

        char buffer[65534];
        size_t bytes_transfered = socket.receive_from(boost::asio::buffer(buffer), server);
        std::cout << buffer << std::endl;

    }
    return 0;
}