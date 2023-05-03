#include "libs/Server/server.hpp"
#define SOCKET_PORT 8000

// using func = std::function<Response(json)>;

int main(int argc, char **argv) {
    // if (argc < 2){
    //     std::cout << "Main usage: path_to_program <port number>" << std::endl;
    //     return 0;
    // }

    Server server(atoi(argv[1]));
    server.start();

    // std::map<std::string, View> urls;
    // UserView usrView;

    // urls["/api/v1/IUser"] = usrView;
    // {
    //     {std::string(""), &UserView::as_view},
    //     {std::string("/api/v1/getUser2"), &UserView::as_view},
    // }
    return 0;
}