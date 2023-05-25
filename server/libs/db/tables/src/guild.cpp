#include "guild.hpp"

GuildTable::GuildTable("guilds") {}

GuildTable::~GuildTable() {}

bool GuildTable::Checker(unsigned int owner_id){
    pqxx::work transaction(*conn);
    std::string sql="SELECT COUNT(*) FROM users";
    pqxx::result user_count=transaction.exec(sql);
    transaction.commit();
    if (owner_id<=user_count.as<unsigned int>()) return true;
    else return false;
}

bool GuildTable::insertRecord(Guild& guild_struct) override
{
    if (Checker(guild_struct.owner_id)){ //зачем user_count?
        try{
        pqxx::work transaction(*conn);
        std::string sql = "INSERT INTO " + tableName + "(owner_id,name,user_count,created_at) VALUES ($1,$2,$3,$4)";
        transaction.exec_params(sql, guild_struct.owner_id, guild_struct.name, guild_struct.user_count, guild_struct.created_at);
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

bool GuildTable::deleteRecord(unsigned int id) override
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="DELETE FROM "+ tableName + " WHERE id=$1";
        transaction.exec_params(sql, id );
        sql="DELETE FROM users_guilds WHERE guild_id=$1";
        transaction.exec_params(sql, id );
        sql="DELETE FROM channels WHERE guild_id=$1";
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

bool GuildTable::updateRecord(Guild& guild_struct, unsigned int id) override
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="UPDATE " + tableName + " SET name=$1,user_count=$2 WHERE id=$4";
        transaction.exec_params(sql, guild_struct.name, guild_struct.user_count, id);
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

Guild* GuildTable::readRecord(unsigned int id)
{
    try{
        pqxx::work transaction(*conn);
        std::string sql="SELECT * FROM " + tableName + " WHERE id=$1";
        pqxx::result result = transaction.exec_params(sql, id);
        transaction.commit();
        Guild guild_result;
        guild_result.id=result[0].as<unsigned int>();
        guild_result.owner_id=result[1].as<unsigned int>();
        guild_result.name=result[2].as<std::string>();
        guild_result.user_count=result[3].as<unsigned int>();
        guild_result.created_at=result[4].as<std::string>();
        std::cout << "Record was found!" << std::endl;
        return guild_result;

    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        Guild guild_result;
        return guild_result; //возвращает пустой шаблон
    }
}
