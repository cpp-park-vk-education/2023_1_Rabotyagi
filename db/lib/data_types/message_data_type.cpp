struct Message
{
    unsigned int id;
    unsigned int owner_id;
    unsigned int channel_id;
    std::string content;
    std::string created_at;
    std::string updated_at;
};
