#include "SDL/SDL.h"
#include "Conf.h"
#include <cstdlib>
#include <map>
#include <string>
#include <sstream>

int disp_str(std::string str, SDL_Surface* surf, int x, int y);

int main(int argc, char* argv[])
{
  Conf conf("config.txt");

  SDL_Joystick *controller = NULL;

  SDL_Surface* screen = NULL;
  SDL_Surface* background = NULL;
  SDL_Surface* img_a = NULL;
  SDL_Surface* btn_a = NULL;
  SDL_Surface* img_b = NULL;
  SDL_Surface* btn_b = NULL;
  SDL_Surface* img_start = NULL;
  SDL_Surface* btn_start = NULL;
  SDL_Surface* img_cup = NULL;
  SDL_Surface* btn_cup = NULL;
  SDL_Surface* img_cleft = NULL;
  SDL_Surface* btn_cleft = NULL;
  SDL_Surface* img_cright = NULL;
  SDL_Surface* btn_cright = NULL;
  SDL_Surface* img_cdown = NULL;
  SDL_Surface* btn_cdown = NULL;
  SDL_Surface* img_r = NULL;
  SDL_Surface* btn_r = NULL;
  SDL_Surface* img_l = NULL;
  SDL_Surface* btn_l = NULL;
  SDL_Surface* img_z = NULL;
  SDL_Surface* btn_z = NULL;
  SDL_Surface* img_dup = NULL;
  SDL_Surface* btn_dup = NULL;
  SDL_Surface* img_dright = NULL;
  SDL_Surface* btn_dright = NULL;
  SDL_Surface* img_ddown= NULL;
  SDL_Surface* btn_ddown = NULL;
  SDL_Surface* img_dleft = NULL;
  SDL_Surface* btn_dleft = NULL;
  SDL_Surface* img_stick = NULL;
  SDL_Surface* stick = NULL;

  background = SDL_LoadBMP("controller.bmp");
  img_a = SDL_LoadBMP("a.bmp");
  img_b = SDL_LoadBMP("b.bmp");
  img_start = SDL_LoadBMP("start.bmp");
  img_cup = SDL_LoadBMP("cup.bmp");
  img_cleft = SDL_LoadBMP("cleft.bmp");
  img_cright = SDL_LoadBMP("cright.bmp");
  img_cdown = SDL_LoadBMP("cdown.bmp");
  img_r = SDL_LoadBMP("r.bmp");
  img_l = SDL_LoadBMP("l.bmp");
  img_z = SDL_LoadBMP("z.bmp");
  img_dup = SDL_LoadBMP("dup.bmp");
  img_dright = SDL_LoadBMP("dright.bmp");
  img_ddown = SDL_LoadBMP("ddown.bmp");
  img_dleft = SDL_LoadBMP("dleft.bmp");
  img_stick = SDL_LoadBMP("stick.bmp");

  int width;
  int height;
  std::string const &widthstr = conf.get_value("width");
  std::string const &heightstr = conf.get_value("height");
  if (widthstr == "auto" || widthstr == "") {
    width = background->w;
  } else {
    width = atoi(widthstr.c_str());
  }
  if (heightstr == "auto" || heightstr == "") {
    height = background->h;
  } else {
    height = atoi(heightstr.c_str());
  }

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption("InputDisplay", NULL);
  screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

  controller = SDL_JoystickOpen(0);

  btn_a = SDL_DisplayFormat(img_a);
  btn_b = SDL_DisplayFormat(img_b);
  btn_start = SDL_DisplayFormat(img_start);
  btn_cup = SDL_DisplayFormat(img_cup);
  btn_cleft = SDL_DisplayFormat(img_cleft);
  btn_cright = SDL_DisplayFormat(img_cright);
  btn_cdown = SDL_DisplayFormat(img_cdown);
  btn_r = SDL_DisplayFormat(img_r);
  btn_l = SDL_DisplayFormat(img_l);
  btn_z = SDL_DisplayFormat(img_z);
  btn_dup = SDL_DisplayFormat(img_dup);
  btn_dright = SDL_DisplayFormat(img_dright);
  btn_ddown = SDL_DisplayFormat(img_ddown);
  btn_dleft = SDL_DisplayFormat(img_dleft);
  stick = SDL_DisplayFormat(img_stick);

  Uint32 colorkey = SDL_MapRGB(btn_a->format, 0x00, 0x00, 0x00);

  SDL_SetColorKey(btn_a, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_b, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_start, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_cup, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_cleft, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_cright, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_cdown, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_r, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_l, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_z, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_dup, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_dright, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_ddown, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(btn_dleft, SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(stick, SDL_SRCCOLORKEY, colorkey);

  SDL_Rect stick_pos;

  SDL_Event event;

  int i;
  std::string key;
  std::string key2;
  std::string key3;
  std::string value;
  std::map<std::string, SDL_Surface*> buttonmap;
  buttonmap["a"] = btn_a;
  buttonmap["b"] = btn_b;
  buttonmap["c-up"] = btn_cup;
  buttonmap["c-right"] = btn_cright;
  buttonmap["c-down"] = btn_cdown;
  buttonmap["c-left"] = btn_cleft;
  buttonmap["start"] = btn_start;
  buttonmap["r"] = btn_r;
  buttonmap["l"] = btn_l;
  buttonmap["z"] = btn_z;
  buttonmap["d-up"] = btn_dup;
  buttonmap["d-right"] = btn_dright;
  buttonmap["d-down"] = btn_ddown;
  buttonmap["d-left"] = btn_dleft;
  int treshold;
  int stickmax = 32767;
  int stickx = 0;
  int sticky = 1;
  if (conf.get_value("stickmax") != "") {
    stickmax = atoi(conf.get_value("stickmax").c_str());
  }
  if (conf.get_value("stickx") != "") {
    stickx = atoi(conf.get_value("stickx").c_str());
  }
  if (conf.get_value("sticky") != "") {
    sticky = atoi(conf.get_value("sticky").c_str());
  }

  int fps = 100;
  if (conf.get_value("fps") != "") {
    fps = atoi(conf.get_value("fps").c_str());
  }

  bool running = true;
  bool reload = false;
  bool mash = false;
  int mashcounter = 0;
  int framecounter = 0;
  stringstream mashss;
  mashss.str("0");
  while (running) {
    if (reload) {
      conf.reload();
      if (conf.get_value("stickmax") != "") {
        stickmax = atoi(conf.get_value("stickmax").c_str());
      }
      if (conf.get_value("stickx") != "") {
        stickx = atoi(conf.get_value("stickx").c_str());
      }
      if (conf.get_value("sticky") != "") {
        sticky = atoi(conf.get_value("sticky").c_str());
      }
      if (conf.get_value("fps") != "") {
        fps = atoi(conf.get_value("fps").c_str());
      }
      reload = false;
    }
    SDL_BlitSurface(background, NULL, screen, NULL);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        } else if (event.key.keysym.sym == SDLK_r) {
          reload = true;
        } else if (event.key.keysym.sym == SDLK_m) {
          mash = !mash;
        }
      } else if (event.type == SDL_JOYBUTTONDOWN) {
        mashcounter++;
      }
    }

    for (i = 0, key = "button0";
         (value = conf.get_value(key)) != "" || i < 10; i++, key[6]++) {
      if (buttonmap[value] != 0 && SDL_JoystickGetButton(controller, i)) {
        SDL_BlitSurface(buttonmap[value], NULL, screen, NULL);
      }
    }
    for (i = 0, key = "axis0", key2 = "axis0t";
         (value = conf.get_value(key)) != ""
         || i < 10; i++, key[4]++, key2[4]++) {
      treshold = 16384;
      if (conf.get_value(key2) != "") {
        treshold = atoi(conf.get_value(key2).c_str());
      }
      if (buttonmap[value] != 0
          && SDL_JoystickGetAxis(controller, i) > treshold) {
        SDL_BlitSurface(buttonmap[value], NULL, screen, NULL);
      }
    }
    for (i = 0, key = "axis0-", key2 = "axis0t";
         (value = conf.get_value(key)) != ""
         || i < 10; i++, key[4]++, key2[4]++) {
      treshold = 16384;
      if (conf.get_value(key2) != "") {
        treshold = atoi(conf.get_value(key2).c_str());
      }
      if (buttonmap[value] != 0
          && SDL_JoystickGetAxis(controller, i) < -treshold) {
        SDL_BlitSurface(buttonmap[value], NULL, screen, NULL);
      }
    }
    for (i = 0, key = "hat0u";
         (value = conf.get_value(key)) != ""; i++, key[3]++) {
      if (buttonmap[value] != 0 && SDL_JoystickGetHat(controller, i) 
          & SDL_HAT_UP) {
        SDL_BlitSurface(buttonmap[value], NULL, screen, NULL);
      }
    }
    for (i = 0, key = "hat0r";
         (value = conf.get_value(key)) != ""; i++, key[3]++) {
      if (buttonmap[value] != 0 && SDL_JoystickGetHat(controller, i) 
          & SDL_HAT_RIGHT) {
        SDL_BlitSurface(buttonmap[value], NULL, screen, NULL);
      }
    }
    for (i = 0, key = "hat0d";
         (value = conf.get_value(key)) != ""; i++, key[3]++) {
      if (buttonmap[value] != 0 && SDL_JoystickGetHat(controller, i) 
          & SDL_HAT_DOWN) {
        SDL_BlitSurface(buttonmap[value], NULL, screen, NULL);
      }
    }
    for (i = 0, key = "hat0l";
         (value = conf.get_value(key)) != ""; i++, key[3]++) {
      if (buttonmap[value] != 0 && SDL_JoystickGetHat(controller, i) 
          & SDL_HAT_LEFT) {
        SDL_BlitSurface(buttonmap[value], NULL, screen, NULL);
      }
    }

    stick_pos.x = SDL_JoystickGetAxis(controller, stickx) * 12 / stickmax;
    stick_pos.y = SDL_JoystickGetAxis(controller, sticky) * 12 / stickmax;
    SDL_BlitSurface(stick, NULL, screen, &stick_pos);

    if (mash) {
      if (framecounter % fps == 0) {
        mashss.str("");
        mashss << mashcounter;
        mashcounter = 0;
      }
      disp_str(mashss.str(), screen,
               width-10-mashss.str().length()*10, height-20);
    }

    SDL_Flip(screen);
    SDL_Delay(1000 / fps);
    framecounter++;
  }

  SDL_FreeSurface(background);
  SDL_FreeSurface(img_a);
  SDL_FreeSurface(img_b);
  SDL_FreeSurface(img_start);
  SDL_FreeSurface(img_cup);
  SDL_FreeSurface(img_cleft);
  SDL_FreeSurface(img_cright);
  SDL_FreeSurface(img_cdown);
  SDL_FreeSurface(img_r);
  SDL_FreeSurface(img_l);
  SDL_FreeSurface(img_z);
  SDL_FreeSurface(img_stick);
  SDL_FreeSurface(btn_a);
  SDL_FreeSurface(btn_b);
  SDL_FreeSurface(btn_start);
  SDL_FreeSurface(btn_cup);
  SDL_FreeSurface(btn_cleft);
  SDL_FreeSurface(btn_cright);
  SDL_FreeSurface(btn_cdown);
  SDL_FreeSurface(btn_r);
  SDL_FreeSurface(btn_l);
  SDL_FreeSurface(btn_z);
  SDL_FreeSurface(btn_dup);
  SDL_FreeSurface(btn_dright);
  SDL_FreeSurface(btn_ddown);
  SDL_FreeSurface(btn_dleft);
  SDL_FreeSurface(stick);
  SDL_JoystickClose(controller);
  SDL_Quit();

  return 0;
}


int disp_str(std::string str, SDL_Surface* surf, int x, int y)
{
  static SDL_Surface* ascii = SDL_LoadBMP("ascii.bmp");
  SDL_Rect cut;
  SDL_Rect pos;
  cut.w = 10;
  cut.h = 20;
  pos.w = 10;
  pos.h = 20;
  pos.x = x;
  pos.y = y;
  int i;

  for (i = 0; i < str.size(); i++) {
    cut.x = str[i] % 32 * 10;
    cut.y = str[i] / 32 * 20;
    if (str[i] == '\n') {
      pos.x = x;
      pos.y += 20;
    } else {
      SDL_BlitSurface(ascii, &cut, surf, &pos);
      pos.x += 10;
    }
  }

  return i;
}
