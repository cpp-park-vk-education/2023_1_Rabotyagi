#include <url_dispatcher.hpp>

TEST(DispatcherTests, no_url_to_dispatch){
    // Arrange
    UrlDispatcher dispatcher;
    Request request(
        _status=200,
        _url=""
        );

    // Act
    auto result = dispatcher(request);

    // Assert
    ASSERT_EQ(result.status, 502);
}

TEST(DispatcherTests, IUser_url){
    // Arrange
    UrlDispatcher dispatcher;
    Request request(
        _status=200,
        _url="/api/v1/IUser",
        _method="GET"
        );

    // Act
    auto result = dispatcher(request);

    // Assert
    ASSERT_EQ(result.status, 200);
}

TEST(DispatcherTests, IGuild_url){
    // Arrange
    UrlDispatcher dispatcher;
    Request request(
        _status=200,
        _url="/api/v1/IGuild",
        _method="GET"
        );

    // Act
    auto result = dispatcher(request);

    // Assert
    ASSERT_EQ(result.status, 200);
}

TEST(DispatcherTests, IChannel_url){
    // Arrange
    UrlDispatcher dispatcher;
    Request request(
        _status=200,
        _url="/api/v1/IChannel",
        _method="GET"
        );

    // Act
    auto result = dispatcher(request);

    // Assert
    ASSERT_EQ(result.status, 200);
}

TEST(DispatcherTests, IMessage_url){
    // Arrange
    UrlDispatcher dispatcher;
    Request request(
        _status=200,
        _url="/api/v1/IMessage",
        _method="GET"
        );

    // Act
    auto result = dispatcher(request);

    // Assert
    ASSERT_EQ(result.status, 200);
}

TEST(DispatcherTests, url_with_no_method){
    // Arrange
    UrlDispatcher dispatcher;
    Request request(
        _status=200,
        _url="/api/v1/IMessage"
        );

    // Act
    auto result = dispatcher(request);

    // Assert
    ASSERT_EQ(result.status, 405);
}
