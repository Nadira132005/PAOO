add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE Lab::lab)
set_target_properties(app PROPERTIES CXX_EXTENSIONS OFF)
