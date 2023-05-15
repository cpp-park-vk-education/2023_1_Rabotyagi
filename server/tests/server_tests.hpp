// #include <gtest/gtest.h>
// #include <request.hpp>

// TEST(ServerTests, Sample1){
//     //Arrange
//     json in = {
//         {"meta", {
//             {"status", 200},
//             {"message", ""},
//             {"url", ""},
//             {"method", ""},
//             {"params", ""},
//         }},
//         {"data", ""}
//     };

//     // Act
//     Request request(_json_body=in);

//     // Assert
//     ASSERT_EQ(in, request.get_body());
// }