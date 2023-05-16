#include <thread>
#include <iostream>
#include "user_connection_backend.hpp"
#include <postgresql/libpq-fe.h>

void test_connection(std::shared_ptr<ConnectionPool> connection_pool){
    std::shared_ptr<DB_Connection> conn=connection_pool->connection(); //получение свободного соединения

    std::string demo ="SELECT max(id) FROM demo; ";
    PQsendQuery(conn->connection().get(), demo.c_str());

    while (auto i=PQgetResult(conn->connection().get())){
        if (PQresultStatus(i)==PQRES_TUPLES_OK && PQntuples(i)){
            auto id = PQgetvalue(i, 0, 0);
            std::cout<<id<<std::endl;
        }
    

    if (PQresultStatus(i)==PGRES_FATAL_ERROR){
        std::cout<<PQresultErrorMessage(i)<<std::endl;
    }
    PQclean(i);
}
    connection_pool->free_connection(conn);
}

int main(int argc, char const *argv[]){
    std::shared_ptr<ConnectionPool> connection_pool=std::make_shared<ConnectionPool>;
    std::vector<std::shared_ptr<std::thread>> vec;
    for (unsigned int i=0; i<50; ++i){
        vec.push_back(std::make_shared<std::thread>(std::thread(test_connection, connection_pool)));
    }
    for (auto &i:vec){
        i.get()->join();
    }
    return 0;
}