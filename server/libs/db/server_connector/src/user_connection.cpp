#include "user_connection.hpp"

DB_Connection::DB_Connection(){
    db_connection.reset( PQsetdbLogin(db_host.c_str(),db_port.c_str(), nullptr, nullptr, db_name.c_str(), db_user.c_str(), db_password.c_str()), &PQfinish); //установка соединения с бд
    if (PQstatus(db_connection.get())!=CONNECTION_OK && PQsetnonblocking(db_connection.get(), 1)!=0) {  //проверка успешности установки соединения и установка неблокирующего режима соединения
        throw std::runtime_error(PQerrorMessage(db_connection.get()));
    }

}

std::shared_ptr<PGconn> DB_Connection::connection() const //возврат указателя на текущее соединение
{
    return db_connection;
}

bool DB_Connection::is_connected() {
    return db_connection ? true : false;
} 