#include <iostream>
#include <gtest/gtest.h>
#include "user_connection_backend.hpp"

// Тестирование функции connection() класса ConnectionPool
TEST(ConnectionPoolTest, ConnectionTest){
    ConnectionPool pool;
    std::shared_ptr<DB_Connection> conn1 = pool.connection();
    // Проверяем, что соединение успешно создано
    EXPECT_TRUE(conn1 != nullptr);
    // Проверяем, что созданное соединение работает
    EXPECT_TRUE(conn1->is_connected());
    std::shared_ptr<DB_Connection> conn2 = pool.connection();
    // Проверяем, что соединение успешно создано
    EXPECT_TRUE(conn2 != nullptr);
    // Проверяем, что созданное соединение работает
    EXPECT_TRUE(conn2->is_connected());
    // Проверяем, что создано не более 10 соединений
    for(int i=0; i<8; i++){
        std::shared_ptr<DB_Connection> conn = pool.connection();
    }
    std::shared_ptr<DB_Connection> conn11 = pool.connection();
    EXPECT_TRUE(conn11 == nullptr);
}

// Тестирование функции free_connection() класса ConnectionPool
TEST(ConnectionPoolTest, FreeConnectionTest){
    ConnectionPool pool;
    std::shared_ptr<DB_Connection> conn1 = pool.connection();
    // Проверяем, что соединение успешно создано
    EXPECT_TRUE(conn1 != nullptr);
    // Проверяем, что созданное соединение работает
    EXPECT_TRUE(conn1->is_connected());
    pool.free_connection(conn1);
    std::shared_ptr<DB_Connection> conn2 = pool.connection();
    // Проверяем, что соединение, которое мы вернули в пул, снова доступно
    EXPECT_TRUE(conn1 == conn2);
}

// Тестирование функции create_pool() класса ConnectionPool
TEST(ConnectionPoolTest, CreatePoolTest){
    ConnectionPool pool;
    std::shared_ptr<DB_Connection> conn1 = pool.connection();
    // Проверяем, что соединение успешно создано
    EXPECT_TRUE(conn1 != nullptr);
    // Проверяем, что созданное соединение работает
    EXPECT_TRUE(conn1->is_connected());
    // Ожидаем, что все соединения будут созданы
    for(int i=0; i<9; i++){
        std::shared_ptr<DB_Connection> conn = pool.connection();
    }
    // Ожидаем, что пул не будет создавать больше соединений
    std::shared_ptr<DB_Connection> conn11 = pool.connection();
    EXPECT_TRUE(conn11 == nullptr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
