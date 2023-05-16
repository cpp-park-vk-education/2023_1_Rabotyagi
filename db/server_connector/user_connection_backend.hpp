#pragma once
#include <memory>
#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>
#include <libpq-fe.h>
#include "user_connection.hpp"

//класс реализации пула подключений для базы данных
class ConnectionPool{
    public:
    ConnectionPool();
    std::shared_ptr<DB_Connection> connection();
    void free_connection(std::shared_ptr<DB_Connection>);
    private:
    void create_pool();
    std::mutex db_mutex;
    std::condition_variable db_condition;
    std::queue<std::shared_ptr<DB_Connection> db_pool;
    const int POOL=10;
};
