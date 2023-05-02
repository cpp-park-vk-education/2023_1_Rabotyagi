#include <boost/asio.hpp>
#include <iostream>
#include <optional>

class Session: public std::enable_shared_from_this<Session> {
  public:
    Session(boost::asio::ip::tcp::socket&& socket) :
        socket(std::move(socket)) {}

    void start() {
        boost::asio::async_read_until(
          socket,
          streambuf,
          '\n',
          [self = shared_from_this()] (boost::system::error_code error, std::size_t bytes_transferred)
          {
            std::stringstream ss;
            ss << std::istream(&self->streambuf).rdbuf();
            std::string buff = ss.str();
            // auto sender = &self->socket.remote_endpoint(error1);
            // std::cout << "request from " << sender << ": " << buff;
            std::cout << "request: " << buff;
          });
        
    }

  private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
};

class Server {
  public:
    Server(boost::asio::io_context& io_context, std::uint16_t port) :
        io_context(io_context),
        acceptor(
            io_context,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

    void async_accept() {
        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&](boost::system::error_code error) {
            std::make_shared<Session>(std::move(*socket))->start();
            async_accept();
        });
    }

  private:
    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
};