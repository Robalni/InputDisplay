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
  SDL_DestroyTexture(this->texture);
}

void Controller_part::update()
{
  switch (this->action) {
  case SHOW:
    this->show = this->is_pressed();
    break;
  }
}

void Controller_part::render()
{
  if (this->show) {
    SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rect);
  }
}

Button::Button(SDL_Joystick *joystick, int index, int action,
               SDL_Renderer *renderer, SDL_Surface *surface)
{
  this->joystick = joystick;
  this->index = index;
  this->type = type;
  this->renderer = renderer;
  this->rect.w = surface->w;
  this->rect.h = surface->h;
  this->rect.x = 0;
  this->rect.y = 0;
  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  this->action = action;
}

bool Button::is_pressed()
{
  return SDL_JoystickGetButton(this->joystick, this->index);
}

Axis::Axis(SDL_Joystick *joystick, int index, char sign, int action,
           SDL_Renderer *renderer, SDL_Surface *surface)
{
  this->joystick = joystick;
  this->index = index;
  this->sign = sign;
  this->type = type;
  this->renderer = renderer;
  this->rect.w = surface->w;
  this->rect.h = surface->h;
  this->rect.x = 0;
  this->rect.y = 0;
  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  this->action = action;
}

bool Axis::is_pressed()
{
  if (this->sign == '-') {
    return SDL_JoystickGetAxis(this->joystick, this->index) < AXIS_MIN / 2;
  } else {
    return SDL_JoystickGetAxis(this->joystick, this->index) > AXIS_MAX / 2;
  }
}

Hat::Hat(SDL_Joystick *joystick, int index, int direction, int action,
         SDL_Renderer *renderer, SDL_Surface *surface)
{
  this->joystick = joystick;
  this->index = index;
  this->direction = direction;
  this->type = type;
  this->renderer = renderer;
  this->rect.w = surface->w;
  this->rect.h = surface->h;
  this->rect.x = 0;
  this->rect.y = 0;
  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  this->action = action;
}

bool Hat::is_pressed()
{
  return SDL_JoystickGetHat(this->joystick, this->index) & this->direction;
}
