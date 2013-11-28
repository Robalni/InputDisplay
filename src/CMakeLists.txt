include_directories(${InputDisplay_SOURCE_DIR}/include)
link_libraries(SDL SDLmain)
add_executable(InputDisplay main.cpp Conf.cpp)
