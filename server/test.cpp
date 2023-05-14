#include <request_tests.hpp>
// Цикличные ссылки!!!! БУдь осторожен будущий я
// #include <request_tests.hpp>
// #include <dispatcher_tests.hpp>

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}