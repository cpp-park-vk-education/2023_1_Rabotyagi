#pragma once
#include "headers.hpp"
#include "data_base_table.hpp"

class ChannelTable : DatabaseTable
{
    bool Checker(unsigned int);
    bool insertRecord(Channel&);
    bool deleteRecord(unsigned int);
    bool updateRecord(Channel&, unsigned int);
    Channel* readRecord(unsigned int);
};