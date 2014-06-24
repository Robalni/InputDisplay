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

Controller::Controller(string const &imgdir, SDL_Renderer *renderer)
{
  this->renderer = renderer;
  this->joystick = SDL_JoystickOpen(0);
  if (this->joystick == NULL) {
    cerr << "Could not open joystick." << endl;
  }
  this->imgdir = imgdir;
  SDL_Surface *surf;
  surf = load_image("controller");
  this->width = surf->w;
  this->height = surf->h;
  this->textures["controller"]
    = SDL_CreateTextureFromSurface(this->renderer, surf);
  SDL_FreeSurface(surf);
}

Controller::~Controller()
{
  //SDL_JoystickClose(this->joystick);
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

void Controller::render(Conf &conf)
{
  stringstream ss;
  string name;
  SDL_RenderCopy(this->renderer, this->textures["controller"], NULL, NULL);
  for (size_t i = 0; i < this->used_buttons.size(); i++) {
    if (SDL_JoystickGetButton(this->joystick, this->used_buttons[i])) {
      ss << "button" << i;
      name = ss.str();
      SDL_RenderCopy(this->renderer, this->textures[conf.get_value(name)]
                     , NULL, NULL);
    }
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
