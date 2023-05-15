#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <optional>
// #include <nlohmann/json.hpp>
// #include "request.hpp"
#include "url_dispatcher.hpp"

using udp = boost::asio::ip::udp;
using io_service = boost::asio::io_service;
using json = nlohmann::json;

class Session: public std::enable_shared_from_this<Session> {
  public:
    Session(boost::asio::ip::tcp::socket&& socket) :
        _socket(std::move(socket)),
        _dispatcher() {}

    void start() {
        boost::asio::async_read_until(
            _socket,
            _streambuf,
            '\n',
            [self = shared_from_this()](
                boost::system::error_code error,
                std::size_t bytes_transferred) 
                {
                    std::string recieved_str {std::istreambuf_iterator<char>(&self->_streambuf), std::istreambuf_iterator<char>()};
                    try {
                        Request request = Request::load_from_string(recieved_str);
                        std::cout << "received" << ", msg: " << recieved_str << std::endl;

                        auto response_str = self->_dispatcher(request).dump();
                        self->_socket.send(boost::asio::buffer(response_str));

                    }
                    catch (const std::exception& e) {
                        std::cerr << e.what() << std::endl;
                    }
                    // _socket.send_to(boost::asio::buffer(response_str), sender);
                }
            );
    }

  private:
    boost::asio::ip::tcp::socket _socket;
    UrlDispatcher _dispatcher;
    boost::asio::streambuf _streambuf;
};

class AsyncServer {
private:
    boost::asio::io_context& _io_context;
    boost::asio::ip::tcp::acceptor _acceptor;
    std::optional<boost::asio::ip::tcp::socket> _socket;
public:
    AsyncServer(boost::asio::io_context& io_context, std::uint16_t port) :
    _io_context(io_context),
    _acceptor(
        io_context,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)
        ) {}
    
    void async_accept() {
        _socket.emplace(_io_context);

        _acceptor.async_accept(*_socket, [&](boost::system::error_code error) {
            std::make_shared<Session>(std::move(*_socket))->start();
            async_accept();
        });
    }
};