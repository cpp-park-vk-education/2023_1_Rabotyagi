#pragma once
#include <boost/parameter.hpp>
#include <boost/parameter/keyword.hpp>
#include <stdexcept>
#include <string>
#include <memory>
#include "json.hpp"
#include "data_types.hpp"

using json = nlohmann::json;

BOOST_PARAMETER_NAME(status);
BOOST_PARAMETER_NAME(message);
BOOST_PARAMETER_NAME(url);
BOOST_PARAMETER_NAME(method);
BOOST_PARAMETER_NAME(params);
BOOST_PARAMETER_NAME(data);
// BOOST_PARAMETER_NAME(json_body);

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

    template<User& user>
    void parse() {
        user.name = data["user"]["name"];
        user.password = data["user"]["password"];
        user.email = data["user"]["email"];
        user.last_login = data["user"]["last_login"];
    }

    template<Guild& guild>
    void parse() {
        guild.owner_id = data["guild"]["owner_id"];
        guild.name = data["guild"]["name"];
        guild.user_count = data["guild"]["user_count"];
        guild.created_at = data["guild"]["created_at"];
    }

    template<Channel& channel>
    void parse() {
        channel.guild_id = data["channel"]["guild_id"];
        channel.name = data["channel"]["name"];
        channel.type = data["channel"]["type"];
        channel.created_at = data["channel"]["created_at"];
        channel.updated_at = data["channel"]["updated_at"];
    }

    template<Message& message>
    void parse() {
        message.owner_i = data["message"]["owner_i"];
        message.channel_id = data["message"]["channel_id"];
        message.content = data["message"]["content"];
        message.created_at = data["message"]["created_at"];
        message.updated_at = data["message"]["updated_at"];
    }
};

struct Request : public Request_impl {
    BOOST_PARAMETER_CONSTRUCTOR(
        Request, (Request_impl), tag,
        (optional
            (status, (int))
            (message, (std::string))
            (url, (std::string))
            (method, (std::string))
            (params, (json))
            (data, (json))
        )
    );

    static Request load_from_string(string message){
        if (message == ""){
            throw std::runtime_error("request string is empty");
        }
        else {
            json body = json::parse(message);
            return Request::load_from_json(body);
        }
    }

    static Request load_from_json(json request) {
        Request result;
        if (!request.empty()){
            if (request.contains("meta")){
                if (request["meta"].contains("status"))
                    result.status = request["meta"]["status"];
                else
                    throw std::runtime_error("invalid json body (no status field)");

                if (request["meta"].contains("message"))
                    result.message = request["meta"]["message"];

                if (request["meta"].contains("url"))
                    result.url = request["meta"]["url"];

                if (request["meta"].contains("method"))
                    result.method = request["meta"]["method"];

                if (request["meta"].contains("params"))
                    result.params = request["meta"]["params"];

            }
            else
                throw std::runtime_error("meta field in json body is missing");

            if (request.contains("data"))
                result.data = request["data"];
        }
        else {
            throw std::runtime_error("json param is empty!");
        }
        return result;
    }
};
