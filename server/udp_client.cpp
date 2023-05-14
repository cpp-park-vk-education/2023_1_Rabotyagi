#include "server.hpp"
#include <nlohmann/json.hpp>
#define SOCKET_PORT 8000
#define MAX_LEN 65534
using json = nlohmann::json;
using udp = boost::asio::ip::udp;
using io_service = boost::asio::io_service;

class Client {
    public:
        Client(std::string addr = "localhost", std::string port = "8000") : _io_service(), _socket(_io_service), _addr(addr, port){};

        void Get(std::string url, json config = NULL) {
            auto destination = *udp::resolver(_io_service).resolve(_addr.first, _addr.second).begin();

            // Request request(url, "GET", "message to server: ligma balls");
            Request request(_url = url, _method = "GET", _data = "message to server: ligma balls");
            
            std::string str_repr(request.dump());

            auto str = str_repr.c_str();
            
            _socket.send_to(boost::asio::buffer(&str[0], str_repr.size()), destination);

            udp::endpoint server;
            char buffer[MAX_LEN];

            size_t bytes_transfered = _socket.receive_from(boost::asio::buffer(buffer), server);
            Request response(json::parse(std::string(buffer, bytes_transfered)));
            std::cout << response.dump() << std::endl;
        };
        void Post(std::string url, json data, json config) {};
        void Delete(std::string url, json config) {};
        void Patch(std::string url, json data, json config) {};
        
    private:
        io_service _io_service;
        udp::socket _socket;
        std::pair<std::string, std::string> _addr;
};

int main(int argc, char **argv) {
    // if (argc < 3){
    //     std::cout << "Main usage: path_to_program <ip_dest> <port_dest>" << std::endl;
    //     return 0;
    // }
    Client client;

    // client
    // Client client(argv[1], argv[2]);
    // Request request(_url = "/api/v1/IUser", _method = "GET", _data = "message to server: ligma balls");
    // json buff = request.form();


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