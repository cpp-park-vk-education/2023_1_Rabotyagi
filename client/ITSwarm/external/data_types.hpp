#pragma once
#include <string>

struct Base {
    unsigned int id=0;
};

struct Channel : Base
{
    unsigned int guild_id=0;
    std::string name="";
    std::string type="";
    std::string created_at="";
    std::string updated_at="";
};

struct Guild:Base
{
    unsigned int owner_id=0;
    std::string name="";
    unsigned int user_count=0;
    std::string created_at="";
};

struct Message:Base
{
    unsigned int owner_i=0;
    unsigned int channel_id=0;
    std::string content="";
    std::string created_at="";
    std::string updated_at="";
};

struct User:Base
{
    std::string name="";
    std::string password="";
    std::string email="";
    std::string last_login="";
    unsigned int guild_id=-1;
    unsigned int channel_id=-1;

};
