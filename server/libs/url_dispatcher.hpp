#include "view.hpp"

class UrlDispatcher {
  public:
    UrlDispatcher() : urls() {
      std::shared_ptr<UserView> user_v(new UserView());
      std::shared_ptr<GuildView> guild_v(new GuildView());
      std::shared_ptr<ChannelView> channel_v(new ChannelView());
      std::shared_ptr<MessageView> message_v(new MessageView());
      
      urls["/api/v1/IUser"] = user_v;
      urls["/api/v1/IGuild"] = guild_v;
      urls["/api/v1/IChannel"] = channel_v;
      urls["/api/v1/IMessage"] = message_v;
    };

    Request operator()(Request& request) {
      if (urls.contains(request.url)){
        return urls[request.url]->as_view(request);
      }
      else{
        return Request(_status=402, _message="wrong url");
      }
    }
  private:
    std::map<std::string, std::shared_ptr<View>> urls;
};