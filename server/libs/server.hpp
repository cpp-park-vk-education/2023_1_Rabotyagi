#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
// #include <nlohmann/json.hpp>
// #include "request.hpp"
#include "url_dispatcher.hpp"

using udp = boost::asio::ip::udp;
using io_service = boost::asio::io_service;
using json = nlohmann::json;

class Server {
    public:
        Server(const int& port = 8000) : _io_service(), _receiver(udp::v4(), port), _socket(_io_service, _receiver), _dispatcher() {};

        void start(){
            std::cout << "Server starts on " << _receiver.address() << ":" << _receiver.port() << std::endl;
            accept();
            std::cout << "Server stopped" << std::endl;
        }
    private:
        io_service _io_service;
        udp::endpoint _receiver;
        udp::socket _socket;
        UrlDispatcher _dispatcher;

        void accept();
};

void Server::accept() {
    try
    {
        for (;;)
        {
            char buffer[65534];
            udp::endpoint sender;
            size_t bytes_transfered = _socket.receive_from(boost::asio::buffer(buffer), sender);

            std::string recieved_str = std::string(buffer, bytes_transfered);

            try {
                Request request = Request::load_from_string(recieved_str);
                std::cout << "received from " << sender << ", bytes: " << bytes_transfered << ", msg: " << recieved_str << std::endl;
                auto response_str = _dispatcher(request).dump();
                _socket.send_to(boost::asio::buffer(response_str), sender);
            }                
            catch (const std::exception& e){
                std::cerr << e.what() << std::endl;
                // throw std::runtime_error(e.what());
            }

        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
};