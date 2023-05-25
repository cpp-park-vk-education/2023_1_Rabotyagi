#include "server.hpp"
#include <memory>

int main(int argc, char **argv) {
    if (argc < 2){
        std::cout << "Main usage: path_to_program <port number>" << std::endl;
        return 0;
    }
    
    boost::asio::io_context io_context;
    AsyncServer server(io_context, std::atoi(argv[1]));
    server.async_accept();
    io_context.run();
    return 0;
}