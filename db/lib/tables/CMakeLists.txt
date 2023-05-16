add_library(tables PRIVATE .)
target_link_libraries(tables PRIVATE PostgreSQL::PostgreSQL)