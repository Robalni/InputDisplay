/*
  Copyright (C) 2014, 2015  Robert Alm Nilsson <rorialni@gmail.com>

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

#include "controller.hpp"

Controller::Controller(SDL_Renderer *renderer, Conf &conf)
{
  this->imgdir = conf.get_value("imgdir");
  this->renderer = renderer;
  this->joystick = NULL;
  this->open_joystick();
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

  map<string, Controller_part*>::iterator i;
  for (i = this->parts.begin(); i != this->parts.end(); i++) {
    delete i->second;
  }

  if (SDL_JoystickGetAttached(this->joystick)) {
    SDL_JoystickClose(this->joystick);
  }
}

bool Controller::open_joystick(int first_try)
{
  int i;
  int joy_n = SDL_NumJoysticks();
  int joy_index;
  const char *joy_name = NULL;
  if (SDL_JoystickGetAttached(this->joystick)) {
    SDL_JoystickClose(this->joystick);
  }
  if (joy_n == 1) {
    cerr << "\nThere is 1 joystick connected." << endl;
  } else {
    cerr << "\nThere are " << joy_n << " joysticks connected." << endl;
  }
  this->joystick = NULL;
  for (i = first_try; i < first_try + joy_n; i++) {
    joy_index = i % joy_n;
    this->joystick = SDL_JoystickOpen(joy_index);
    if (this->joystick) {
      break;
    } else {
      joy_name = SDL_JoystickNameForIndex(joy_index);
      cerr << "Could not open joystick " << joy_index << " ("
           << (joy_name ? joy_name : "") << ")"<< endl;
    }
  }
  if (this->joystick) {
    joy_name = SDL_JoystickNameForIndex(joy_index);
    cerr << "Opened joystick " << joy_index << " ("
         << (joy_name ? joy_name : "")
         <<  ")\nYou can open another one with the tab key." << endl;
    this->joystick_index = joy_index;
    return true;
  } else {
    cerr << "Could not open any joystick. Restart the program or press r"
      " to try again." << endl;
    return false;
  }
}

bool Controller::open_another_joystick()
{
  if (SDL_JoystickGetAttached(this->joystick)) {
    return this->open_joystick((joystick_index + 1) % SDL_NumJoysticks());
  } else {
    return this->open_joystick(0);
  }
}

char const *Controller::get_joystick_name() const
{
  return SDL_JoystickName(this->joystick);
}

int Controller::action_str_to_int(string const &str)
{
  int action = SHOW;
  if (str == "" || str == "show")
    action = SHOW;
  else if (str == "movex")
    action = MOVEX;
  else if (str == "movey")
    action = MOVEY;
  return action;
}

bool Controller::load_buttons(Conf &conf)
{
  SDL_Surface *surf;
  int action, max;
  string name;
  for (int i = 0; i < this->n_buttons; i++) {
    stringstream ss;
    ss << "button" << i;
    name = conf.get_value(ss.str());
    action = action_str_to_int(conf.get_value(ss.str()+'a'));
    conf.get_int(ss.str()+'m', max);
    if (name != "") {
      surf = this->load_image(name.c_str());
      if (this->parts.count(name) == 0) {
        this->parts[name] = new Controller_part(this->renderer, surf,
                                                this->joystick);
      }
      this->parts[name]->add_button(i, action, max);
      SDL_FreeSurface(surf);
    }
  }
  return true;
}

bool Controller::load_axes(Conf &conf)
{
  SDL_Surface *surf;
  int action, max, treshold, deftreshold;
  char sign = '+';
  string name;
  if (!conf.get_int("default_treshold", deftreshold))
    deftreshold = -1;
  while (true) {
    for (int i = 0; i < this->n_axes; i++) {
      stringstream ss;
      ss << "axis" << i << sign;
      name = conf.get_value(ss.str());
      action = action_str_to_int(conf.get_value(ss.str()+'a'));
      conf.get_int(ss.str()+'m', max);
      if (!conf.get_int(ss.str()+'t', treshold))
        treshold = deftreshold;
      if (name != "") {
        surf = this->load_image(name.c_str());
        if (this->parts.count(name) == 0) {
          this->parts[name] = new Controller_part(this->renderer, surf,
                                                  this->joystick);
        }
        this->parts[name]->add_axis(i, sign, action, max, treshold);
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
  int action, max;
  string name;
  char dirnames[] = "urdl";
  char *dirname = dirnames;
  int directions[] = {SDL_HAT_UP, SDL_HAT_RIGHT, SDL_HAT_DOWN, SDL_HAT_LEFT,
                      SDL_HAT_CENTERED};
  for (int *direction = directions; *direction != SDL_HAT_CENTERED;
       direction++, dirname++) {
    for (int i = 0; i < this->n_hats; i++) {
      stringstream ss;
      ss << "hat" << i << *dirname;
      name = conf.get_value(ss.str());
      action = action_str_to_int(conf.get_value(ss.str()+'a'));
      conf.get_int(ss.str()+'m', max);
      if (name != "") {
        surf = this->load_image(name.c_str());
        if (this->parts.count(name) == 0) {
          this->parts[name] = new Controller_part(this->renderer, surf,
                                                  this->joystick);
        }
        this->parts[name]->add_hat(i, *direction, action, max);
        SDL_FreeSurface(surf);
      }
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
  map<string, Controller_part*>::iterator i;

  SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);

  for (i = this->parts.begin(); i != this->parts.end(); i++) {
    i->second->render();
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
