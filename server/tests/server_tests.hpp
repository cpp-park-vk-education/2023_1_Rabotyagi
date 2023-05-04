#include <gtest/gtest.h>
#include <request.hpp>

TEST(RequestTests, ConstructorDefault){
    //Arrange
    json in = {
        {"meta", {
            {"status", 200},
            {"message", nullptr},
            {"url", nullptr},
            {"method", nullptr},
            {"params", nullptr},
        }},
        {"data", nullptr}
    };
    json out = json::parse(R"(
        {
            "meta": {
                "status": 200,
                "message": null,
                "url": null,
                "method": null,
                "params": null
            },
            "data": null
        }
    )");

    // Act
    Request request(in);

    // Assert
    ASSERT_EQ(out, request.get());
}

TEST(RequestTests, ConstructorJson){
    //Arrange
    json in = {
        {"meta", {
            {"status", nullptr},
            {"message", nullptr},
            {"url", "/api/v1/some"},
            {"method", "GET"},
            {"params", nullptr},
        }},
        {"data", nullptr}
    };
    json out = json::parse(R"(
        {
            "meta": {
                "status": null,
                "message": null,
                "url": "/api/v1/some",
                "method": "GET",
                "params": null
            },
            "data": null
        }
    )");

    // Act
    Request request(in);

    // Assert
    ASSERT_EQ(out, request.get());
}

TEST(RequestTests, ConstructorInt){
    // Arrange
    json out = json::parse(R"(
        {
            "meta": {
                "status": 500,
                "message": null,
                "url": null,
                "method": null,
                "params": null
            },
            "data": null
        }
    )");

    // Act
    Request request(500);

    // Assert
    ASSERT_EQ(out, request.get());
}

// TEST(RequestTests, ConstructorType){
//     // Arrange
//     json out = json::parse(R"(
//         {
//             "meta": {
//                 "status": 500,
//                 "message": null,
//                 "url": null,
//                 "method": null,
//                 "params": null
//             },
//             "data": null
//         }
//     )");

//     // Act
//     Request request(500);

//     // Assert
//     ASSERT_EQ(out, request.get());
// }
