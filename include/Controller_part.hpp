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

#define AXIS_MAX 32767
#define AXIS_MIN -32768

#include <SDL2/SDL.h>

class Controller_part
{
public:
  Controller_part();
  virtual ~Controller_part();
  void update();
  void render();
protected:
  virtual bool is_pressed() = 0;
  int action;
  int type;
  int index;
  int show;
  SDL_Joystick *joystick;
  SDL_Rect rect;
  SDL_Renderer *renderer;
  SDL_Texture * texture;
};

class Button : public Controller_part
{
public:
  Button(SDL_Joystick *joystick, int index, int action,
         SDL_Renderer *renderer, SDL_Surface *surface);
protected:
  bool is_pressed();
};

class Axis : public Controller_part
{
public:
  Axis(SDL_Joystick *joystick, int index, char sign, int action,
       SDL_Renderer *renderer, SDL_Surface *surface);
protected:
  bool is_pressed();
  char sign;
};

class Hat : public Controller_part
{
public:
  Hat(SDL_Joystick *joystick, int index, int action,
      SDL_Renderer *renderer, SDL_Surface *surface);
protected:
  bool is_pressed();
};

enum {
  SHOW,
  MOVE_UP,
  MOVE_RIGHT,
  MOVE_DOWN,
  MOVE_LEFT
};

#endif // CONTROLLER_PART_HPP
