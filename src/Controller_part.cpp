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

Controller_part::Controller_part(SDL_Renderer *renderer,
                                 SDL_Surface *surface,
                                 SDL_Joystick *joystick)
{
  this->renderer = renderer;
  this->joystick = joystick;
  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  this->rect.x = 0;
  this->rect.y = 0;
  this->rect.w = surface->w;
  this->rect.h = surface->h;
  this->show = true;
}

Controller_part::~Controller_part()
{
  SDL_DestroyTexture(this->texture);
  size_t i;
  for (i = 0; i < this->real_parts.size(); i++) {
    delete this->real_parts[i];
  }
}

void Controller_part::add_button(int index, int action, int max)
{
  Button *button = new Button(this->joystick, index, action, max);
  this->real_parts.push_back(button);
}

void Controller_part::add_axis(int index, char sign, int action, int max,
                               int treshold)
{
  Axis *axis = new Axis(this->joystick, index, sign, action, max, treshold);
  this->real_parts.push_back(axis);
}

void Controller_part::add_hat(int index, int direction, int action, int max)
{
  Hat *hat = new Hat(this->joystick, index, direction, action, max);
  this->real_parts.push_back(hat);
}

void Controller_part::render()
{
  this->update();
  if (this->show) {
    SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rect);
  }
}

void Controller_part::update()
{
  size_t i;
  Real_part *part;
  int value;
  this->rect.x = 0;
  this->rect.y = 0;
  this->show = false;
  for (i = 0; i < this->real_parts.size(); i++) {
    part = this->real_parts[i];
    switch (part->get_action()) {
    case SHOW:
      if (part->is_pressed())
        this->show = true;
      break;
    case MOVEX:
      value = part->get_axis();
      if (value > 0)
        this->rect.x = part->get_axis() * part->get_max() / AXIS_MAX;
      this->show = true;
      break;
    case MOVEY:
      value = part->get_axis();
      if (value > 0)
        this->rect.y = part->get_axis() * part->get_max() / AXIS_MAX;
      this->show = true;
      break;
    }
  }
}
