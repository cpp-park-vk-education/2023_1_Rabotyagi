#include <pqxx>

class DatabaseTable
{
public:
    DatabaseTable(const std::string &tableName) : tableName(tableName)
    {
        db = new pqxx::connection(
            "host=db_host port=db_port dbname=db_name user=db_user password=db_password"
        );
        if (!db->is_open())
        {
            std::cerr << "Failed to connect to database:" << db->get_error_message() << std::endl;
        }
    }

    ~DatabaseTable()
    {
        db->disconnect();
        delete db;
    }

    virtual bool insertRecord(Base&)
    {
    }
    

    virtual bool deleteRecord(unsigned int)
    {
    }

    virtual bool updateRecord(Base&, unsigned int)
    {
    }

    virtual Base readRecord(unsigned int)
    {
    }

protected:
    std::string tableName;
    pqxx::connection *db;
};


