add_library(Server INTERFACE)
target_link_libraries(Server INTERFACE Request)
# target_link_libraries(Server PRIVATE Request)
target_include_directories(Server INTERFACE .)