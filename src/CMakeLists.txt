include_directories(${InputDisplay_SOURCE_DIR}/include)

if(MINGW)
  link_libraries(mingw32 SDL2 SDL2_image)
  add_executable(InputDisplay WIN32 main.cpp Conf.cpp Controller.cpp)
else(MINGW)
  link_libraries(SDL2 SDL2_image)
  add_executable(InputDisplay main.cpp Conf.cpp Controller.cpp)
endif(MINGW)
