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

using std::cerr;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::stringstream;

class Controller
{
public:
  Controller(string const &imgdir, SDL_Renderer *renderer);
  ~Controller();
  void render(Conf &conf);
  int get_width();
  int get_height();
private:
  SDL_Surface *load_image(string const &name);
  SDL_Renderer *renderer;
  map <string, SDL_Texture*> textures;
  vector <int> used_buttons;
  string imgdir;
  int width, height;
  SDL_Joystick *joystick;
};

#endif // CONTROLLER_HPP
