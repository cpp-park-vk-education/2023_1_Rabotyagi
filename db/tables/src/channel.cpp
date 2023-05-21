#include "channel.hpp"

ChannelTable::ChannelTable("channels") {}

ChannelTable::~ChannelTable() {}

bool ChannelTable::Checker(unsigned int guild_id){
    pqxx::work transaction(*conn);
    std::string sql="SELECT COUNT(*) FROM guilds";
    pqxx::result guild_count=transaction.exec(sql);
    transaction.commit();
    if (guild_id<=guild_count.as<unsigned int>()) return true;
    else return false;
}

bool ChannelTable::insertRecord(Channel& channel_struct) override
{
    if (Checker(channel_struct.guild_id)){
        try{
        pqxx::work transaction(*conn);
        std::string sql = "INSERT INTO " + tableName + "(guild_id,name,type,created_at,updated_at) VALUES ($1,$2,$3,$4,$5)";
        transaction.exec_params(sql, channel_struct.guild_id, channel_struct.name, channel_struct.type, channel_struct.created_at, channel_struct.updated_at);
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

bool ChannelTable::deleteRecord(unsigned int id) override
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="DELETE FROM "+ tableName + " WHERE id=$1";
        transaction.exec_params(sql, id );
        sql="DELETE FROM messages WHERE channel_id=$1";
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

bool ChannelTable::updateRecord(Channel& channel_struct, unsigned int id) override
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="UPDATE " + tableName + " SET name=$1,type=$2,updated_at=$3 WHERE id=$4";
        transaction.exec_params(sql, channel_struct.name, channel_struct.type, channel_struct.updated_at, id);
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

Channel* ChannelTable::readRecord(unsigned int id)
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="SELECT * FROM " + tableName + " WHERE id=$1";
        pqxx::result result = transaction.exec_params(sql, id);
        transaction.commit();
        Channel channel_result;
        channel_result.id=result[0].as<unsigned int>();
        channel_result.guild_id=result[1].as<unsigned int>();
        channel_result.name=result[2].as<std::string>();
        message_result.type=result[3].as<std::string>();
        message_result.created_at=result[4].as<std::string>();
        message_result.updated_at=result[5].as<std::string>();
        std::cout << "Record was found!" << std::endl;
        return channel_result;

    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        Channel channel_result;
        return channel_result; //возвращает пустой шаблон
    }
}
