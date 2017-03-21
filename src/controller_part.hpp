/*
  A "controller part" is a non-static part of the controller you can
  see when you run this program.  It uses the classes from
  real_part.hpp and real_part.cpp to access the physical controller.

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

#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "real_part.hpp"

using std::vector;

class ControllerPart
{
public:
  ControllerPart(SDL_Renderer *renderer, SDL_Surface *surface,
                  SDL_Joystick *joystick);
  ~ControllerPart();
  void add_button(int index, int action, int max);
  void add_axis(int index, char sign, int action, int max, int treshold);
  void add_hat(int index, int direction, int action, int max);
  void render();
protected:
  void update();
  SDL_Rect rect;
  bool show;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Joystick *joystick;
  vector<Real_part*> real_parts;
};

enum {
  SHOW,
  MOVEX,
  MOVEY
};
