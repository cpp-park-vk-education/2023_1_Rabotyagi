#include "libs/Server/server.hpp"
#define SOCKET_PORT 8000
// using json = nlohmann::json;


int main() {
    boost::asio::io_context io_context;
    server srv(io_context, SOCKET_PORT);
    srv.async_accept();
    io_context.run();
    return 0;
}