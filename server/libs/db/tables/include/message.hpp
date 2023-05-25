#include "headers.hpp"
#include "data_base_table.hpp"

class MessageTable : DatabaseTable
{
    bool Checker(unsigned int, unsigned int);
    bool insertRecord(Message&);
    bool deleteRecord(unsigned int);
    bool updateRecord(Message&, unsigned int);
    Message* readRecord(unsigned int);
};
