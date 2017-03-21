/*
  A "controller" in this file means the controller you can see on your
  screen in this program and it's connection to the physical
  controller.

  Copyright (C) 2014, 2015, 2016  Robert Alm Nilsson <rorialni@gmail.com>

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

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "conf.hpp"
#include "controller_part.hpp"

using std::cerr;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::stringstream;

class Controller
{
public:
  Controller(SDL_Renderer *renderer, Conf &conf);
  ~Controller();
  void render();
  int get_width();
  int get_height();
  bool open_another_joystick(Conf &conf);
  char const *get_joystick_name() const;
private:
  bool open_joystick(int first_try = 0);
  int action_str_to_int(string const &str);
  bool load_parts(Conf &conf);
  void free_parts();
  bool load_buttons(Conf &conf);
  bool load_axes(Conf &conf);
  bool load_hats(Conf &conf);
  SDL_Surface *load_image(string const &name);
  SDL_Renderer *renderer;
  map <string, ControllerPart*> parts;
  SDL_Texture *texture;
  string imgdir;
  int width, height;
  SDL_Joystick *joystick;
  int joystick_index;
  int n_buttons, n_axes, n_hats;
};
