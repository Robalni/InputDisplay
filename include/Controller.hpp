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

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Conf.hpp"
#include "Controller_part.hpp"

using std::cerr;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::stringstream;

class Controller
{
public:
  Controller(string const &imgdir, SDL_Renderer *renderer, Conf &conf);
  ~Controller();
  void render();
  int get_width();
  int get_height();
private:
  bool load_buttons(Conf &conf);
  bool load_axes(Conf &conf);
  bool load_hats(Conf &conf);
  SDL_Surface *load_image(string const &name);
  SDL_Renderer *renderer;
  vector <Controller_part*> parts;
  SDL_Texture *texture;
  string imgdir;
  int stickx, sticky, stickmax;
  int width, height;
  SDL_Joystick *joystick;
  int n_buttons, n_axes, n_hats;
};

#endif // CONTROLLER_HPP
