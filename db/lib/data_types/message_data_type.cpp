struct Message:Base
{
    unsigned int id=0;
    unsigned int owner_i=0;
    unsigned int channel_id=0;
    std::string content="";
    std::string created_at="";
    std::string updated_at="";
};
