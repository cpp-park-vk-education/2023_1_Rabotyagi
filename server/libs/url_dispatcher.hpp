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