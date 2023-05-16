#pragma once

#include <memory>
#include <mutex>
#include <libpd-fe.h>

//класс соединения с базой данных
class DB_Connection{
    public:
    DB_Connection();
    std::shared_ptr<user_connect> connection() const;

    private:
    void establish_connection();      //устанавливает соединение с базой данных

    std::string db_host="localhost";
    std::string db_port="5432";
    std::string db_name="name";
    std::string db_user="user";
    std::string db_password="password";
    std::shared_ptr<user_connect> db_connection;
};
