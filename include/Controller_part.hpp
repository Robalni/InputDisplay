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

#ifndef CONTROLLER_PART_HPP
#define CONTROLLER_PART_HPP

#include <vector>
#include <SDL2/SDL.h>

#include "Real_part.hpp"

using std::vector;

class Controller_part
{
public:
  Controller_part(SDL_Renderer *renderer, SDL_Surface *surface,
                  SDL_Joystick *joystick, int action, int max);
  ~Controller_part();
  void add_button(int index);
  void add_axis(int index, char sign);
  void add_hat(int index, int direction);
  void render();
protected:
  void update();
  SDL_Rect rect;
  bool show;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Joystick *joystick;
  int action;
  int max;
  vector<Real_part*> real_parts;
};

enum {
  SHOW,
  MOVEX,
  MOVEY
};

#endif // CONTROLLER_PART_HPP
