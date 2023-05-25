#include "user.hpp"

UserTable::UserTable("users") {}

UserTable::~UserTable() {}

bool UserTable::insertRecord(User& user_struct) override  //добавить проверку на уникальность
{
    try{
        pqxx::work transaction(*conn);
        std::string sql = "INSERT INTO " + tableName + "(name,password,email,last_login) VALUES ($1,$2,$3,$4)";
        transaction.exec_params(sql, user_struct.name, user_struct.password, user_struct.email, user_struct.last_login);
        transaction.commit();
        std::cout << "Record was added to db!" << std::endl;
        return true;
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

bool UserTable::deleteRecord(unsigned int id) override
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="DELETE FROM "+ tableName + " WHERE id=$1";
        transaction.exec_params(sql, id );
        sql="DELETE FROM messages WHERE owner_id=$1";
        transaction.exec_params(sql, id );
        sql="DELETE FROM users_guilds WHERE user_id=$1";
        transaction.exec_params(sql, id );
        sql="DELETE FROM guilds WHERE owner_id=$1";
        transaction.exec_params(sql, id );
        transaction.commit();
        std::cout << "Record was deleted from db!" << std::endl;
        return true;

    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

bool UserTable::updateRecord(User& user_struct, unsigned int id) override
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="UPDATE " + tableName + " SET name=$1, password=$2, email=$3, last_login=$4 WHERE id=$5";
        transaction.exec_params(sql, user_struct.name, user_struct.password, user_struct.email, user_struct.last_login, id);
        transaction.commit();
        std::cout << "Record was updated!" << std::endl;
        return true;
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

User* UserTable::readRecord(unsigned int id)
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="SELECT * FROM " + tableName + " WHERE id=$1";
        pqxx::result result = transaction.exec_params(sql, id);
        transaction.commit();
        User user_result;
        user_result.id=result[0].as<unsigned int>();
        user_result.name=result[1].as<std::string>();
        user_result.pasword=result[2].as<std::string>();
        user_result.email=result[3].as<std::string>();
        user_result.last_login=result[4].as<std::string>();
        std::cout << "Record was found!" << std::endl;
        return user_result;

    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        User user_result;
        return user_result; //возвращает пустой шаблон
    }
}

