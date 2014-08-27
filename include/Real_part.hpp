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

#define AXIS_MAX 32767
#define AXIS_MIN -32768

#include <SDL2/SDL.h>

class Real_part
{
public:
  Real_part();
  virtual bool is_pressed() = 0;
  virtual bool get_axis() = 0;
protected:
  SDL_Joystick *joystick;
  int index;
  int move_max;
};

class Button : public Real_part
{
public:
  Button(SDL_Joystick *joystick, int index);
  bool is_pressed();
  bool get_axis();
protected:
};

class Axis : public Real_part
{
public:
  Axis(SDL_Joystick *joystick, int index);
  bool is_pressed();
  bool get_axis();
protected:
};

class Hat : public Real_part
{
public:
  Hat(SDL_Joystick *joystick, int index, int direction);
  bool is_pressed();
  bool get_axis();
protected:
  int direction;
};
