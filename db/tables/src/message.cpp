#include "message.hpp"

MessageTable::MessageTable("messages") {}

MessageTable::~MessageTable() {}

bool MessageTable::Checker(unsigned int owner_id, unsigned int channel_id){
    pqxx::work transaction(*conn);
    std::string sql="SELECT COUNT(*) FROM users";
    pqxx::result user_count=transaction.exec(sql);
    sql="SELECT COUNT(*) FROM channels";
    pqxx::result channel_count=transaction.exec(sql);
    transaction.commit();
    if (owner_id<=user_count.as<unsigned int>() && channel_id<=channel_count.as<unsigned int>()) return true;
    else return false;
}

bool MessageTable::insertRecord(Message& message_struct) override //добавить проверку на существование канала и обладателя
{
    if (Checker(message_struct.owner_id, message_struct.channel_id)){
        try{
            pqxx::work transaction(*conn);
            std::string sql = "INSERT INTO " + tableName + "(owner_id,channel_id,content,created_at,updated_at) VALUES ($1,$2,$3,$4,$5)";
            transaction.exec_params(sql, message_struct.owner_id, message_struct.channel_id, message_struct.content, message_struct.created_at, message_struct.updated_at);
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
    return false;
}

bool MessageTable::deleteRecord(unsigned int id) override
{ 
    try{
        pqxx::work transaction(*conn);
        std::string sql="DELETE FROM "+ tableName + " WHERE id=$1";
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

bool MessageTable::updateRecord(Message& message_struct, unsigned int id) override
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="UPDATE " + tableName + " SET content=$1, updated_at=$2 WHERE id=$3";
        transaction.exec_params(sql, message_struct.content, message_struct.updated_at, id);
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

Message* MessageTable::readRecord(unsigned int id)
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="SELECT * FROM " + tableName + " WHERE id=$1";
        pqxx::result result = transaction.exec_params(sql, id);
        transaction.commit();
        Message message_result;
        message_result.id=result[0].as<unsigned int>();
        message_result.owner_id=result[1].as<unsigned int>();
        message_result.channel_id=result[2].as<unsigned int>();
        message_result.content=result[3].as<std::string>();
        message_result.created_at=result[4].as<std::string>();
        message_result.updated_at=result[5].as<std::string>();
        std::cout << "Record was found!" << std::endl;
        return message_result;

    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        Message message_result;
        return message_result; //возвращает пустой шаблон
    }
}
