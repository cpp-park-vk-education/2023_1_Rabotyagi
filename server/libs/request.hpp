#include <boost/parameter.hpp>
#include <boost/parameter/keyword.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

BOOST_PARAMETER_NAME(status);
BOOST_PARAMETER_NAME(message);
BOOST_PARAMETER_NAME(url);
BOOST_PARAMETER_NAME(method);
BOOST_PARAMETER_NAME(params);
BOOST_PARAMETER_NAME(data);


struct Request_impl
{
    public:

        template <class ArgumentPack>
        Request_impl(ArgumentPack const& args) : body()
        {
            body["meta"]["status"] = args[_status | 200];
            body["meta"]["message"] = args[_message | ""];
            body["meta"]["url"] = args[_url | ""];
            body["meta"]["method"] = args[_method | ""];
            body["meta"]["params"] = args[_params | json()];
            body["data"] = args[_data | json()];
        };

        Request_impl(json request){
            body["meta"] = request["meta"];
            body["data"] = request["data"];
        };

        Request_impl(const Request_impl& obj) : body(obj.body) {};

        Request_impl& operator=(const Request_impl& right){
            body = right.body;
            return *this;
        };

        ~Request_impl(){};

        json form() { return body;};

        void parse(json request) {
            body["meta"] = request["meta"];
            body["data"] = request["data"];
        };

    private:
        json body;
};

struct Request : Request_impl {
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
};