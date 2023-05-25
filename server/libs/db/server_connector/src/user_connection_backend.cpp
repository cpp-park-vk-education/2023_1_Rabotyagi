#include "user_connection_backend.hpp"

ConnectionPool::ConnectionPool(){
    create_pool();
}

std::shared_ptr<DB_Connection> ConnectionPool::connection(){
    std::unique_lock<std::mutex> lock( db_mutex );
    while (db_pool.empty()){
        db_condition.wait(lock);
    }
    std::shared_ptr<DB_Connection> conn = db_pool.front();
    db_pool.pop();
    return conn;
}

void ConnectionPool::create_pool(){
    std::lock_guard<std::mutex> locker( db_mutex );
    for (unsigned int i=0; i<POOL; ++i){
        db_pool.emplace(std::make_shared<DB_Connection>());

    }
}


void ConnectionPool::free_connection(std::shared_ptr<DB_Connection> conn){
    std::unique_lock<std::mutex> lock(db_mutex);
    db_pool.push(conn);
    lock.unlock();
    db_condition.notify_one();
}
