#ifndef REQUEST_IMPL_H
#define REQUEST_IMPL_H

#include <string>

struct User {
    unsigned int id;
    const char* username;
};

struct Guild {
    unsigned int id;
    unsigned int owner_id;
};

struct Channel {
    unsigned int id;
    unsigned int guild_id;
};

struct Message {
    unsigned int id;
    unsigned int owner_id;
    unsigned int channel_id;
};

struct Request_impl
{
    using string = std::string;
    // json body;
    int status;
    string message;
    string url;
    string method;
    json params;
    json data;

    template <class ArgumentPack>
    Request_impl(ArgumentPack const& args)
    {
        status = args[_status | 200];
        message = args[_message | ""];
        url = args[_url | ""];
        method = args[_method | ""];
        params = args[_params | ""];
        data = args[_data | ""];
    };

    Request_impl& operator=(const Request_impl& right){
        status = right.status;
        message = right.message;
        url = right.url;
        method = right.method;
        params = right.params;
        data = right.data;
        return *this;
    };

    string dump() {
        return get_body().dump();
    }

    json get_body() {
        return json({
            {"meta", {
                {"status", status},
                {"message", message},
                {"url", url},
                {"method", method},
                {"params", params},
            }},
            {"data", data}
        });
    }

    template<User>
    User parse_to() {
        return User();
    }

    template<Guild>
    Guild parse_to() {
        return Guild();
    }

    template<Channel>
    Channel parse_to() {
        return Channel();
    }

    template<Message>
    Message parse_to() {
        return Message();
    }
};
#endif // REQUEST_IMPL_H
