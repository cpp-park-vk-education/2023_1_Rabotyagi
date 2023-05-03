#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <memory>
#include <map>
#include <functional>
#include <nlohmann/json.hpp>

using udp = boost::asio::ip::udp;
using io_service = boost::asio::io_service;
using json = nlohmann::json;

struct Response {
    int status;
};

class View {
    public:
        Response as_view(json request) {
            if (request["method"] == "GET")
                return Get(request);
            
            if (request["method"] == "POST")
                return Post(request);
            
            if (request["method"] == "DELETE")
                return Delete(request);
            
            if (request["method"] == "Patch")
                return Patch(request);
            
            return Response(405);
        };

        virtual Response Get(json request) = 0;
        virtual Response Post(json request) = 0;
        virtual Response Delete(json request) = 0;
        virtual Response Patch(json request) = 0;
    // virtual ~View() {};
};

class UserView : public View {
    Response Get(json request) override {
        return Response(200);
    }
    Response Post(json request) override {
        return Response(200);
    }
    Response Delete(json request) override {
        return Response(200);
    }
    Response Patch(json request) override {
        return Response(200);
    }
};

class GuildView : public View {
    Response Get(json request) override {
        return Response(200);
    }
    Response Post(json request) override {
        return Response(200);
    }
    Response Delete(json request) override {
        return Response(200);
    }
    Response Patch(json request) override {
        return Response(200);
    }
};

class ChannelView : public View {
    Response Get(json request) override {
        return Response(200);
    }
    Response Post(json request) override {
        return Response(200);
    }
    Response Delete(json request) override {
        return Response(200);
    }
    Response Patch(json request) override {
        return Response(200);
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
    Response operator()(json request) {
      auto url = request["url"];
      if (urls.contains(url))
        return urls[url]->as_view(request);
      else
        return Response(500);
    }
  private:
    std::map<std::string, std::shared_ptr<View>> urls;
};

class Server {
    public:
        Server(const int& port) : _io_service(), _receiver(udp::v4(), port), _socket(_io_service, _receiver), _dispatcher() {};

        void start(){
            std::cout << "Server starts on " << _receiver.address() << ":" << _receiver.port() << std::endl;
            try
            {
                char buffer[65534];
                for (;;)
                {
                    udp::endpoint sender;
                    size_t bytes_transfered = _socket.receive_from(boost::asio::buffer(buffer), sender);
                    buffer[bytes_transfered] = '\0';
                    json request = json::parse(std::string(buffer, bytes_transfered));
                    std::cout << request << std::endl;
                    // std::cout << "received from " << sender << ", bytes: " << bytes_transfered << ", msg: " << buffer << std::endl;
                    _socket.send_to(boost::asio::buffer(buffer, bytes_transfered), sender);
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