#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <memory>
#include <map>
#include <functional>
#include <nlohmann/json.hpp>
#include <optional>
#include "request.hpp"
#include "url_dispatcher.hpp"

using udp = boost::asio::ip::udp;
using io_service = boost::asio::io_service;
using json = nlohmann::json;

class Server {
    public:
        Server(const int& port = 8000) : _io_service(), _receiver(udp::v4(), port), _socket(_io_service, _receiver), _dispatcher() {};

        void start(){
            std::cout << "Server starts on " << _receiver.address() << ":" << _receiver.port() << std::endl;
            try
            {
                char buffer[65534];
                for (;;)
                {
                    udp::endpoint sender;
                    size_t bytes_transfered = _socket.receive_from(boost::asio::buffer(buffer), sender);
                    json buff = json::parse(
                            std::string(buffer, bytes_transfered)
                            );
                    // std::cout << buff.dump() << std::endl;
                    Request request(buff);
                    auto response = _dispatcher(request).dump();
                    strcpy(buffer, response.c_str());
                    std::cout << "received from " << sender << ", bytes: " << bytes_transfered << ", msg: " << request.dump() << std::endl;
                    _socket.send_to(boost::asio::buffer(buffer, response.size()), sender);
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            std::cout << "Server stopped" << std::endl;
        }
    private:
        io_service _io_service;
        udp::endpoint _receiver;
        udp::socket _socket;
        UrlDispatcher _dispatcher;
};