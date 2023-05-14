#include <gtest/gtest.h>
#include <request.hpp>

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
    Request request(_json_body=in);

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
            {"url", "/api/v1"},
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
        _url="/api/v1",
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
