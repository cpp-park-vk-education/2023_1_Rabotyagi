#include "headers.hpp"
#include "data_base_table.hpp"

class GuildTable : DatabaseTable
{  
    bool Checker(unsigned int);
    bool insertRecord(Guild&);
    bool deleteRecord(unsigned int);
    bool updateRecord(Guild&, unsigned int);
    Guild* readRecord(unsigned int);
};