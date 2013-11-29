include_directories(${InputDisplay_SOURCE_DIR}/include)

if(MINGW)
  link_libraries(mingw32 SDLmain SDL)
else(MINGW)
  link_libraries(SDLmain SDL)
endif(MINGW)

add_executable(buttonmapper main.cpp)
