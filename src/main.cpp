/*
  Copyright (C) 2014  Robert Alm Nilsson <rorialni@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <sstream>

#include "Conf.hpp"
#include "Controller.hpp"

int main()
{
  using std::string;
  using std::cerr;
  using std::endl;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
  IMG_Init(IMG_INIT_PNG);
  std::stringstream ss;
  Conf conf("config.txt");

  SDL_Window *window = SDL_CreateWindow("InputDisplay",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        100, 100, // Will resize later.
                                        SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    cerr << SDL_GetError() << endl;
    return 1;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL) {
    cerr << SDL_GetError() << endl;
    return 1;
  }
  SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  int red = 0;
  int green = 0;
  int blue = 0;
  conf.get_int("red", red);
  conf.get_int("green", green);
  conf.get_int("blue", blue);
  SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);

  Controller *controller
    = new Controller(renderer, conf);

  int win_width, win_height;
  string win_width_str, win_height_str;
  win_width_str = conf.get_value("width");
  if (win_width_str == "auto" || win_width_str == "")
    win_width = controller->get_width();
  else
    conf.get_int("width", win_width);
  win_height_str = conf.get_value("height");
  if (win_height_str == "auto" || win_height_str == "")
    win_height = controller->get_height();
  else
    conf.get_int("height", win_height);

  SDL_SetWindowSize(window, win_width, win_height);
  SDL_RenderSetLogicalSize(renderer, win_width, win_height);

  bool running = true;
  SDL_Event event;
  string button_name;
  int fps = 0;
  conf.get_int("fps", fps);
  if (fps <= 0)
    fps = 1;
  while (running) {
    ss.str("");
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
        case SDLK_q:
        case SDLK_ESCAPE:
          running = false;
          break;
        case SDLK_r:
          conf.reload();
          conf.get_int("fps", fps);
          if (fps <= 0)
            fps = 1;
          red = 0;
          green = 0;
          blue = 0;
          conf.get_int("red", red);
          conf.get_int("green", green);
          conf.get_int("blue", blue);
          SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);
          delete controller;
          controller = new Controller(renderer, conf);
          break;
        case SDLK_s:
          SDL_SetWindowSize(window, win_width, win_height);
          break;
        }
        break;
      }
    }

    SDL_RenderClear(renderer);
    controller->render();
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / fps);
  }

  delete controller;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
