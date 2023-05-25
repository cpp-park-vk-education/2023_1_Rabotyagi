// #pragma once
// #include <iostream>
// #include <memory>
// #include <mutex>
// #include <postgresql/libpq-fe.h>
// #include "user_connection.hpp"

// //тест на успешное установление соединения с базой данных
// TEST(DB_Connection_Test, ConnectionTest) {
//     std::shared_ptr<PGconn> db_conn = conn.connection();
//     EXPECT_NE(db_conn.get(), nullptr);
// }

// //тест на проверку значений по умолчанию для параметров подключения к базе данных
// TEST(DB_Connection_Test, DefaultValuesTest) {
//     EXPECT_EQ(conn.db_host, "localhost");
//     EXPECT_EQ(conn.db_port, "5432");
//     EXPECT_EQ(conn.db_name, "name");
//     EXPECT_EQ(conn.db_user, "user");
//     EXPECT_EQ(conn.db_password, "password");
// }

// //тест на изменение параметров подключения к базе данных
// TEST(DB_Connection_Test, ChangeValuesTest) {
//     conn.db_host = "test_host";
//     conn.db_port = "1234";
//     conn.db_name = "test_db";
//     conn.db_user = "test_user";
//     conn.db_password = "test_password";
//     std::shared_ptr<PGconn> db_conn = conn.connection();
//     EXPECT_NE(db_conn.get(), nullptr);
// }

// //тест на проверку повторного вызова метода connection()
// TEST(DB_Connection_Test, ConnectionReuseTest) {
//     std::shared_ptr<PGconn> db_conn1 = conn.connection();
//     std::shared_ptr<PGconn> db_conn2 = conn.connection();
//     EXPECT_EQ(db_conn1.get(), db_conn2.get());
// }

// //тест на проверку исключения при попытке установить соединение с некорректными параметрами
// TEST(DB_Connection_Test, InvalidConnectionTest) {
//     conn.db_host = "invalid_host";
//     EXPECT_THROW(conn.connection(), std::exception);
// }
