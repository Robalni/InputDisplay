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
    cerr << "Could not open joystick. Restart the program to try again."
         << endl;
  }

  this->n_buttons = SDL_JoystickNumButtons(this->joystick);
  this->n_hats = SDL_JoystickNumHats(this->joystick);
  this->n_axes = SDL_JoystickNumAxes(this->joystick);

  SDL_Surface *surf;
  surf = load_image("controller");
  this->width = surf->w;
  this->height = surf->h;
  this->texture = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(surf);
  this->load_buttons(conf);
  this->load_axes(conf);
  this->load_hats(conf);
}

Controller::~Controller()
{
  SDL_DestroyTexture(this->texture);
  for (size_t i = 0; i < this->parts.size(); i++) {
    delete this->parts[i];
  }
  //SDL_JoystickClose(this->joystick);
}

bool Controller::load_buttons(Conf &conf)
{
  SDL_Surface *surf;
  int action;
  for (int i = 0; i < this->n_buttons; i++) {
    stringstream ss;
    ss << "button" << i;
    string name = conf.get_value(ss.str());
    action = SHOW;
    if (name != "") {
      surf = this->load_image(name.c_str());
      this->parts.push_back(new Button(this->joystick, i, action,
                                       this->renderer, surf));
      SDL_FreeSurface(surf);
    }
  }
  return true;
}

bool Controller::load_axes(Conf &conf)
{
  SDL_Surface *surf;
  int action;
  char sign = '+';
  while (true) {
    for (int i = 0; i < this->n_axes; i++) {
      stringstream ss;
      ss << "axis" << i << sign;
      string name = conf.get_value(ss.str());
      action = SHOW;
      if (name != "") {
        surf = this->load_image(name.c_str());
        this->parts.push_back(new Axis(this->joystick, i, sign, action,
                                       this->renderer, surf));
        SDL_FreeSurface(surf);
      }
    }
    if (sign == '-') {
      break;
    }
    sign = '-';
  }
  return true;
}

bool Controller::load_hats(Conf &conf)
{
  SDL_Surface *surf;
  int action;
  for (int i = 0; i < this->n_hats; i++) {
    stringstream ss;
    ss << "hat" << i;
    string name = conf.get_value(ss.str());
    action = SHOW;
    if (name != "") {
      surf = this->load_image(name.c_str());
      this->parts.push_back(new Hat(this->joystick, i, action,
                                    this->renderer, surf));
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
    cerr << IMG_GetError() << endl;
    exit(1);
    return NULL;
  }
  return img;
}

void Controller::render()
{
  size_t i;

  SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);

  for (i = 0; i < this->parts.size(); i++) {
    this->parts[i]->update();
  }
  for (i = 0; i < this->parts.size(); i++) {
    this->parts[i]->render();
  }
}

int Controller::get_width()
{
  return this->width;
}

int Controller::get_height()
{
  return this->height;
}
