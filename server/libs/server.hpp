#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <memory>
#include <map>
#include <functional>
#include <nlohmann/json.hpp>
#include <optional>
#include "request.hpp"

using udp = boost::asio::ip::udp;
using io_service = boost::asio::io_service;
using json = nlohmann::json;

class View {
    public:
        Request as_view(json request) {
            if (request["method"] == "GET")
                return Get(request);
            
            if (request["method"] == "POST")
                return Post(request);
            
            if (request["method"] == "DELETE")
                return Delete(request);
            
            if (request["method"] == "Patch")
                return Patch(request);
            
            return Request(_status = 405);
        };

        virtual Request Get(json request) = 0;
        virtual Request Post(json request) = 0;
        virtual Request Delete(json request) = 0;
        virtual Request Patch(json request) = 0;
};

class UserView : public View {
    Request Get(json request) override {
        return Request();
    }
    Request Post(json request) override {
        return Request();
    }
    Request Delete(json request) override {
        return Request();
    }
    Request Patch(json request) override {
        return Request();
    }
};

class GuildView : public View {
    Request Get(json request) override {
        return Request();
    }
    Request Post(json request) override {
        return Request();
    }
    Request Delete(json request) override {
        return Request();
    }
    Request Patch(json request) override {
        return Request();
    }
};

class ChannelView : public View {
    Request Get(json request) override {
        return Request();
    }
    Request Post(json request) override {
        return Request();
    }
    Request Delete(json request) override {
        return Request();
    }
    Request Patch(json request) override {
        return Request();
    }
};

class UrlDispatcher {
  public:
    UrlDispatcher() : urls() {
      // using view_ptr = std::shared_ptr<View>;
      std::shared_ptr<UserView> user_v(new UserView());
      std::shared_ptr<GuildView> guild_v(new GuildView());
      std::shared_ptr<ChannelView> channel_v(new ChannelView());
      urls["/api/v1/IUser"] = user_v;
      urls["/api/v1/IGuild"] = guild_v;
      urls["/api/v1/IChannel"] = channel_v;
    };
    Request operator()(json request) {
      auto url = request["meta"]["url"];
      if (urls.contains(url))
        return urls[url]->as_view(request);
      else
        return Request(_status = 500);
    }
  private:
    std::map<std::string, std::shared_ptr<View>> urls;
};

class Server {
    public:
        Server(const int& port = 8000) : _io_service(), _receiver(udp::v4(), port), _socket(_io_service, _receiver), _dispatcher() {};

        void start(){
            std::cout << "Server starts on " << _receiver.address() << ":" << _receiver.port() << std::endl;
            try
            {
                char buffer[65534];
                for (;;)
                {
                    udp::endpoint sender;
                    size_t bytes_transfered = _socket.receive_from(boost::asio::buffer(buffer), sender);

                    Request request(
                        json::parse(
                            std::string(buffer, bytes_transfered)
                            )
                        );
                    auto response = _dispatcher(request.form()).form().dump();
                    strcpy(buffer, response.c_str());
                    // std::cout << request.form() << std::endl;
                    std::cout << "received from " << sender << ", bytes: " << bytes_transfered << ", msg: " << request.form() << std::endl;
                    _socket.send_to(boost::asio::buffer(buffer, response.size()), sender);
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            std::cout << "Server stopped" << std::endl;
        }
    private:
        io_service _io_service;
        udp::endpoint _receiver;
        udp::socket _socket;
        UrlDispatcher _dispatcher;
};