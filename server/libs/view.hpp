#pragma once
#include "request.hpp"

class View {
    public:
        // View() {};

        Request as_view(Request& request) {
            if (request.method == "GET")
                return Get(request);
            
            if (request.method == "POST")
                return Post(request);
            
            if (request.method == "DELETE")
                return Delete(request);
            
            if (request.method == "PATCH")
                return Patch(request);
            
            return Request(405);
        };

        virtual Request Get(Request& request) = 0;
        virtual Request Post(Request& request) = 0;
        virtual Request Delete(Request& request) = 0;
        virtual Request Patch(Request& request) = 0;
};

class UserView : public View {
    Request Get(Request& request) override {
        return Request(_status=200);
    }
    Request Post(Request& request) override {
        return Request(_status=200);
    }
    Request Delete(Request& request) override {
        return Request(_status=200);
    }
    Request Patch(Request& request) override {
        return Request(_status=200);
    }
};

class GuildView : public View {
    Request Get(Request& request) override {
        return Request(_status=200);
    }
    Request Post(Request& request) override {
        return Request(_status=200);
    }
    Request Delete(Request& request) override {
        return Request(_status=200);
    }
    Request Patch(Request& request) override {
        return Request(_status=200);
    }
};

class ChannelView : public View {
    Request Get(Request& request) override {
        return Request(_status=200);
    }
    Request Post(Request& request) override {
        return Request(_status=200);
    }
    Request Delete(Request& request) override {
        return Request(_status=200);
    }
    Request Patch(Request& request) override {
        return Request(_status=200);
    }
};

class MessageView : public View {
    Request Get(Request& request) override {
        return Request(_status=200);
    }
    Request Post(Request& request) override {
        return Request(_status=200);
    }
    Request Delete(Request& request) override {
        return Request(_status=200);
    }
    Request Patch(Request& request) override {
        return Request(_status=200);
    }
};
