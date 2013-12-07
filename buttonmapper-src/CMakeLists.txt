include_directories(${InputDisplay_SOURCE_DIR}/include)

if(MINGW)
  link_libraries(mingw32 SDLmain SDL)
  add_executable(buttonmapper WIN32 main.cpp)
else(MINGW)
  link_libraries(SDLmain SDL)
  add_executable(buttonmapper main.cpp)
endif(MINGW)
