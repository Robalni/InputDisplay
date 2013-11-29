include_directories(${InputDisplay_SOURCE_DIR}/include)

if(MINGW)
  link_libraries(mingw32 SDLmain SDL)
  add_executable(InputDisplay WIN32 main.cpp Conf.cpp)
else(MINGW)
  link_libraries(SDLmain SDL)
  add_executable(InputDisplay main.cpp Conf.cpp)
endif(MINGW)
