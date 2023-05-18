#include <request.hpp>

TEST(RequestTests, ConstructorFromString){
    //Arrange
    json in = {
        {"meta", {
            {"status", 200},
            {"message", ""},
            {"url", ""},
            {"method", ""},
            {"params", ""},
        }},
        {"data", ""}
    };
    std::string message = in.dump();

    // Act
    Request request = Request::load_from_string(message);

    // Assert
    ASSERT_EQ(in, request.get_body());
}

TEST(RequestTests, ConstructorFromEmptyString){
    //Arrange
    std::string message = "";

    // Act

    // Assert
    EXPECT_THROW(Request request = Request::load_from_string(message), std::runtime_error);
}

TEST(RequestTests, ConstructorFromJson){
    //Arrange
    json in = {
        {"meta", {
            {"status", 200},
            {"message", ""},
            {"url", ""},
            {"method", ""},
            {"params", ""},
        }},
        {"data", ""}
    };

    // Act
    Request request = Request::load_from_json(in);

    // Assert
    ASSERT_EQ(in, request.get_body());
}

TEST(RequestTests, ConstructorStatus){
    //Arrange
    json in = {
        {"meta", {
            {"status", 500},
            {"message", ""},
            {"url", ""},
            {"method", ""},
            {"params", ""},
        }},
        {"data", ""}
    };

    // Act
    Request request(_status=500);

    // Assert
    ASSERT_EQ(in, request.get_body());
}

TEST(RequestTests, ConstructorVariable){
    //Arrange
    json in = {
        {"meta", {
            {"status", 300},
            {"message", ""},
            {"url", "/api/v1/IUser"},
            {"method", "GET"},
            {"params", {
                {"Content-Type", "application/pdf"}
            }},
        }},
        {"data", {
            {"first", 1},
            {"second", 2}
        }}
    };
    
    // Act
    Request request(
        _status=300,
        _url="/api/v1/IUser",
        _method="GET",
        _data=json({
            {"first", 1},
            {"second", 2}
        }),
        _params=json({
            {"Content-Type", "application/pdf"}
        })
    );
    
    // Assert
    ASSERT_EQ(in, request.get_body());
}
