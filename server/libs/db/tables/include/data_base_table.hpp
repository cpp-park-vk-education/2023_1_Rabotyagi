#pragma once
#include "headers.hpp"

class DatabaseTable
{
public:
    DatabaseTable(const std::string&);

    ~DatabaseTable();

    virtual bool insertRecord(Base&) = 0;
    

    virtual bool deleteRecord(unsigned int) = 0;

    virtual bool updateRecord(Base&, unsigned int) = 0;

    virtual Base* readRecord(unsigned int) = 0;

protected:
    std::string tableName;
    pqxx::connection *db;
};
