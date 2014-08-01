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

#include "Controller.hpp"

Controller::Controller(string const &imgdir, SDL_Renderer *renderer,
                       Conf &conf)
{
  this->stickx = conf.get_int("stickx");
  this->sticky = conf.get_int("sticky");
  this->stickmax = conf.get_int("stickmax");
  this->imgdir = imgdir;
  this->renderer = renderer;
  this->joystick = SDL_JoystickOpen(0);
  if (this->joystick == NULL) {
    cerr << "Could not open joystick." << endl;
  }

  this->n_buttons = SDL_JoystickNumButtons(this->joystick);
  this->n_hats = SDL_JoystickNumHats(this->joystick);
  this->n_axes = SDL_JoystickNumAxes(this->joystick);

  SDL_Surface *surf;
  surf = load_image("controller");
  this->width = surf->w;
  this->height = surf->h;
  this->texture_controller
    = SDL_CreateTextureFromSurface(this->renderer, surf);
  SDL_FreeSurface(surf);
  surf = this->load_image("stick");
  this->texture_stick = SDL_CreateTextureFromSurface(this->renderer, surf);
  SDL_FreeSurface(surf);
  this->load_buttons(conf);
  this->load_axes(conf);
  this->load_hats(conf);
}

Controller::~Controller()
{
  SDL_DestroyTexture(this->texture_controller);
  SDL_DestroyTexture(this->texture_stick);
  //SDL_JoystickClose(this->joystick);
}

bool Controller::load_buttons(Conf &conf)
{
  SDL_Surface *surf;
  SDL_Texture *text;
  for (int i = 0; i < this->n_buttons; i++) {
    stringstream ss;
    ss << "button" << i;
    string name = conf.get_value(ss.str());
    if (name != "") {
      surf = this->load_image(name.c_str());
      text = SDL_CreateTextureFromSurface(this->renderer, surf);
      this->parts.push_back(Button(i, this->joystick, text));
      SDL_FreeSurface(surf);
    }
  }
  return true;
}

bool Controller::load_axes(Conf &conf)
{
  SDL_Surface *surf;
  SDL_Texture *text;
  for (int i = 0; i < this->n_axes; i++) {
    stringstream ss;
    ss << "axis" << i;
    string name = conf.get_value(ss.str());
    if (name != "") {
      surf = this->load_image(name.c_str());
      text = SDL_CreateTextureFromSurface(this->renderer, surf);
      this->parts.push_back(Button(i, this->joystick, text));
      SDL_FreeSurface(surf);
    }
  }
  return true;
}

bool Controller::load_hats(Conf &conf)
{
  SDL_Surface *surf;
  SDL_Texture *text;
  for (int i = 0; i < this->n_hats; i++) {
    stringstream ss;
    ss << "hat" << i;
    string name = conf.get_value(ss.str());
    if (name != "") {
      surf = this->load_image(name.c_str());
      text = SDL_CreateTextureFromSurface(this->renderer, surf);
      this->parts.push_back(Button(i, this->joystick, text));
      SDL_FreeSurface(surf);
    }
  }
  return true;
}

SDL_Surface *Controller::load_image(string const &name)
{
  string filename = imgdir + "/" + name + ".png";
  SDL_Surface *img = IMG_Load(filename.c_str());
  if (img == NULL) {
    cerr << "Could not load " << filename << ": " << IMG_GetError() << endl;
    return NULL;
  }
  return img;
}

void Controller::render()
{
  size_t i;

  for (i = 0; i < this->parts.size(); i++) {
    this->parts[i].render(this->renderer);
  }

  SDL_Rect rect;
  rect.w = this->width;
  rect.h = this->height;
  rect.x = SDL_JoystickGetAxis(this->joystick, this->stickx)
    * this->stickmax / 32767;
  rect.y = SDL_JoystickGetAxis(this->joystick, this->sticky)
    * this->stickmax / 32767;
  SDL_RenderCopy(this->renderer, this->texture_stick, NULL, &rect);
}

int Controller::get_width()
{
  return this->width;
}

int Controller::get_height()
{
  return this->height;
}
