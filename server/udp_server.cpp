#include "libs/Server/server.hpp"
#define SOCKET_PORT 8000
// using json = nlohmann::json;


int main(int argc, char **argv) {
    if (argc < 2){
        std::cout << "Main usage: path_to_program <port number>" << std::endl;
        return 0;
    }
    boost::asio::io_service io_service;
    using udp = boost::asio::ip::udp;
    auto receiver = udp::endpoint(udp::v4(), atoi(argv[1]));
    auto socket = udp::socket(io_service, receiver);


    for (;;){
        char buffer[65534];
        udp::endpoint sender;
        size_t bytes_transfered = socket.receive_from(boost::asio::buffer(buffer), sender);
        std::cout << "received from " << sender << ", bytes: " << bytes_transfered << " msg: " << buffer;
        socket.send_to(boost::asio::buffer(buffer, bytes_transfered), sender);
    }
    return 0;
}