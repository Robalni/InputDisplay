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

#include "Controller_part.hpp"

Controller_part::Controller_part()
{
}

Controller_part::~Controller_part()
{
}

Button::Button(int index, SDL_Joystick *joystick, SDL_Texture *texture)
{
  this->index = index;
  this->joystick = joystick;
  this->texture = texture;
}

Button::~Button()
{
  SDL_DestroyTexture(this->texture);
}

bool Button::render(SDL_Renderer *renderer)
{
  bool retval;
  if (SDL_JoystickGetButton(this->joystick, this->index))
    if (this->action == SHOW)
      retval = (SDL_RenderCopy(renderer, this->texture, NULL, NULL) == 0);
    else
      retval = false;
  else
    retval = false;

  return retval;
}
