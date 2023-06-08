#include "headers.hpp"
#include "data_base_table.hpp"

class UserTable : DatabaseTable
{    
    bool insertRecord(User&);
    bool deleteRecord(unsigned int);
    bool updateRecord(User&, unsigned int);
    User* readRecord(unsigned int);
};
