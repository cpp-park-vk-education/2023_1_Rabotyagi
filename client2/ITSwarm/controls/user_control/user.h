#include <iostream>

struct User{
    unsigned int id;
    std::string name;
    std::string password;
    std::string email;
    std::string last_login;
    User(): id(-1), name(""), password(""), email(""), last_login("") {}
};

extern User user;
