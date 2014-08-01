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

#include <SDL2/SDL.h>

class Controller_part
{
public:
  Controller_part();
  virtual ~Controller_part();
  virtual bool render(SDL_Renderer *renderer);
protected:
  int action;
  int index;
  SDL_Joystick *joystick;
};

class Button : public Controller_part
{
public:
  Button(int index, SDL_Joystick *joystick, SDL_Texture *texture);
  ~Button();
  bool render(SDL_Renderer *renderer);
protected:
  SDL_Texture *texture;
};

enum aee
{
  SHOW,
  MOVE_UP,
  MOVE_RIGHT,
  MOVE_DOWN,
  MOVE_LEFT
};

#endif // CONTROLLER_PART_HPP
