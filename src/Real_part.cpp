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

#include "Real_part.hpp"

Real_part::Real_part()
{
}

int Real_part::get_action() const
{
  return this->action;
}

Button::Button(SDL_Joystick *joystick, int index, int action)
{
  this->joystick = joystick;
  this->index = index;
  this->action = action;
}

bool Button::is_pressed()
{
  return SDL_JoystickGetButton(this->joystick, this->index);
}

int Button::get_axis()
{
  return SDL_JoystickGetButton(this->joystick, this->index) * AXIS_MAX;
}

Axis::Axis(SDL_Joystick *joystick, int index, int action)
{
  this->joystick = joystick;
  this->index = index;
  this->action = action;
}

bool Axis::is_pressed()
{
  return SDL_JoystickGetAxis(this->joystick, this->index) > AXIS_MAX / 2;
}

int Axis::get_axis()
{
  return SDL_JoystickGetAxis(this->joystick, this->index);
}

Hat::Hat(SDL_Joystick *joystick, int index, int direction, int action)
{
  this->joystick = joystick;
  this->index = index;
  this->direction = direction;
  this->action = action;
}

bool Hat::is_pressed()
{
  return SDL_JoystickGetHat(this->joystick, this->index) & this->direction;
}

int Hat::get_axis()
{
  return (SDL_JoystickGetHat(this->joystick, this->index) & this->direction)
    * AXIS_MAX;
}
