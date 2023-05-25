#include "data_base_table.hpp"

DatabaseTable::DatabaseTable(const std::string &tableName) : tableName(tableName)
{
    db = new pqxx::connection(
        "host=db_host port=db_port dbname=db_name user=db_user password=db_password"
    );
    if (!db->is_open())
    {
        std::cerr << "Failed to connect to database:" << std::endl;
        // std::cerr << "Failed to connect to database:" << db->get_error_message() << std::endl;
    }
}

DatabaseTable::~DatabaseTable()
{
    db->disconnect();
    delete db;
}