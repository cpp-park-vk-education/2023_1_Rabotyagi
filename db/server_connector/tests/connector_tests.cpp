#include <gtest/gtest.h>
#include <memory>
#include <mutex>
#include <postgresql/libpq-fe.h>

//класс соединения с базой данных
class DB_Connection{
    public:
    DB_Connection();
    std::shared_ptr<PGconn> connection() const;

    private:
    void establish_connection();      //устанавливает соединение с базой данных

    std::string db_host="localhost";
    std::string db_port="5432";
    std::string db_name="name";
    std::string db_user="user";
    std::string db_password="password";
    std::shared_ptr<PGconn> db_connection;
};

//тестовый класс
class DB_Connection_Test : public ::testing::Test {
    protected:
    virtual void SetUp() {
        //настройка перед тестами
    }

    virtual void TearDown() {
        //очистка после тестов
    }

    DB_Connection conn;
};

//тест на успешное установление соединения с базой данных
TEST_F(DB_Connection_Test, ConnectionTest) {
    std::shared_ptr<PGconn> db_conn = conn.connection();
    EXPECT_NE(db_conn.get(), nullptr);
}

//тест на проверку значений по умолчанию для параметров подключения к базе данных
TEST_F(DB_Connection_Test, DefaultValuesTest) {
    EXPECT_EQ(conn.db_host, "localhost");
    EXPECT_EQ(conn.db_port, "5432");
    EXPECT_EQ(conn.db_name, "name");
    EXPECT_EQ(conn.db_user, "user");
    EXPECT_EQ(conn.db_password, "password");
}

//тест на изменение параметров подключения к базе данных
TEST_F(DB_Connection_Test, ChangeValuesTest) {
    conn.db_host = "test_host";
    conn.db_port = "1234";
    conn.db_name = "test_db";
    conn.db_user = "test_user";
    conn.db_password = "test_password";
    std::shared_ptr<PGconn> db_conn = conn.connection();
    EXPECT_NE(db_conn.get(), nullptr);
}

//тест на проверку повторного вызова метода connection()
TEST_F(DB_Connection_Test, ConnectionReuseTest) {
    std::shared_ptr<PGconn> db_conn1 = conn.connection();
    std::shared_ptr<PGconn> db_conn2 = conn.connection();
    EXPECT_EQ(db_conn1.get(), db_conn2.get());
}

//тест на проверку исключения при попытке установить соединение с некорректными параметрами
TEST_F(DB_Connection_Test, InvalidConnectionTest) {
    conn.db_host = "invalid_host";
    EXPECT_THROW(conn.connection(), std::exception);
}

//запуск всех тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
