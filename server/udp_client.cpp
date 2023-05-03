#include "libs/Server/server.hpp"
#include <nlohmann/json.hpp>
#define SOCKET_PORT 8000
#define MAX_LEN 65534
using json = nlohmann::json;
using udp = boost::asio::ip::udp;
using io_service = boost::asio::io_service;

class Client {
    public:
        Client(const char* addr, const char* port) : _io_service(), _socket(_io_service)
        {
            auto resolver = udp::resolver(_io_service);
            _destination = *resolver.resolve(addr, port).begin();
        }

        void Get(std::string url, json config = NULL) {
            json request = {
                {"url", url},
                {"method", "GET"},
                {"data", "message to server: ligma balls"}
            };

            std::string str_repr(request.dump());
            _socket.send_to(boost::asio::buffer(&str_repr[0], str_repr.size()), _destination);

            udp::endpoint server;
            char buffer[65534];

            size_t bytes_transfered = _socket.receive_from(boost::asio::buffer(buffer), server);
            json response = json::parse(std::string(buffer, bytes_transfered));
            std::cout << response << std::endl;
        };
        void Post(std::string url, json data, json config) {};
        void Delete(std::string url, json config) {};
        void Patch(std::string url, json data, json config) {};
        
    private:
        udp::socket _socket;
        io_service _io_service;
        boost::asio::ip::basic_resolver_entry<udp> _destination;
};

int main(int argc, char **argv) {
    if (argc < 3){
        std::cout << "Main usage: path_to_program <ip_dest> <port_dest>" << std::endl;
        return 0;
    }

    Client client(argv[1], argv[2]);

    client.Get("/api/v1/IUser");

    // io_service io_service;
    // auto socket = udp::socket(io_service, udp::endpoint(udp::v4(), 0));
    // auto resolver = udp::resolver(io_service);
    // auto destination = *resolver.resolve(udp::v4(), argv[1], argv[2]).begin();
    
    // udp::endpoint server;


    // std::string message;
    // while (std::cin >> message){
    //     socket.send_to(boost::asio::buffer(&message[0], message.size()), destination);

    //     char buffer[65534];
    //     size_t bytes_transfered = socket.receive_from(boost::asio::buffer(buffer), server);
    //     buffer[bytes_transfered] = '\0';
    //     std::cout << "received from " << server << ", bytes: " << bytes_transfered << ", msg: " << buffer << std::endl;

    // }
    return 0;
}