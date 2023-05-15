#include "server.hpp"
#define SOCKET_PORT 8000

// using func = std::function<Response(json)>;

int main(int argc, char **argv) {
    if (argc < 2){
        std::cout << "Main usage: path_to_program <port number>" << std::endl;
        return 0;
    }

    // std::uint16_t port = 15001;

    // boost::asio::io_context io_context;
    // boost::asio::ip::udp::endpoint receiver(boost::asio::ip::udp::v4(), port);
    // boost::asio::ip::udp::socket socket(io_context, receiver);

    // while (true) {
    //     char buffer[65536];
    //     boost::asio::ip::udp::endpoint sender;
    //     std::size_t bytes_transferred =
    //         socket.receive_from(boost::asio::buffer(buffer), sender);
    //     socket.send_to(boost::asio::buffer(buffer, bytes_transferred), sender);
    // }
    Server server;
    server.start();

    return 0;
}