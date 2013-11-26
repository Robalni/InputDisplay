#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

bool read_and_write(std::vector<std::string>& filecontent);
bool update_config(std::vector<std::string>& filecontent, std::string& pressed,
                   std::string& disp_button);

int main(int argc, char* argv[])
{
  using namespace std;
  SDL_Joystick *controller = NULL;
  SDL_Event event;
  vector<string> filecontent;
  bool pressed = false;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
  SDL_JoystickEventState(SDL_ENABLE);
  controller = SDL_JoystickOpen(0);

  fstream file;
  file.open("config.txt", ios::in);
  int i = 0;
  string line;
  while (file.good()) {
    getline(file, line);
    filecontent.push_back(line);
  }
  file.close();

  while (read_and_write(filecontent)) {
  }

  file.open("config.txt", ios::out);
  for (i = 0; i < filecontent.size(); i++) {
    file << filecontent[i] << endl;
    //cout << filecontent[i] << endl;
  }
  file.close();

  SDL_Quit();

  return 0;
}

bool read_and_write(std::vector<std::string>& filecontent)
{
  using namespace std;
  SDL_Event event;
  bool got_input = false;
  string pressed, disp_button;
  stringstream ss;

  cout << "Press something on your controller." << endl;

  while (!got_input) {
    while (SDL_PollEvent(&event)) {
      ss.clear();
      switch (event.type) {
      case SDL_JOYBUTTONDOWN:
        got_input = true;
        ss << "button" << (int)event.jbutton.button;
        break;
      case SDL_JOYAXISMOTION:
        if (event.jaxis.value < -10000) {
          got_input = true;
          ss << "axis" << (int)event.jaxis.axis << '-';
        } else if (event.jaxis.value > 10000) {
          got_input = true;
          ss << "axis" << (int)event.jaxis.axis;
        }
        break;
      case SDL_JOYHATMOTION:
        if (event.jhat.value & SDL_HAT_UP) {
          got_input = true;
          ss << "hat" << (int)event.jhat.hat << 'u';
        } else if (event.jhat.value & SDL_HAT_RIGHT) {
          got_input = true;
          ss << "hat" << (int)event.jhat.hat << 'r';
        } else if (event.jhat.value & SDL_HAT_DOWN) {
          got_input = true;
          ss << "hat" << (int)event.jhat.hat << 'd';
        } else if (event.jhat.value & SDL_HAT_LEFT) {
          got_input = true;
          ss << "hat" << (int)event.jhat.hat << 'l';
        }
        break;
      case SDL_QUIT:
        return false;
      }
    }
  }

  getline(ss, pressed);

  cout << "You pressed " << pressed << ". What should that do?\n"
    " -             c-right      z\n"
    " a             c-down       d-up\n"
    " b             c-left       d-right\n"
    " start         r            d-down\n"
    " c-up          l            d-left"
       << endl;

  cin >> disp_button;

  if (disp_button == "-") {
    disp_button = "";
  }
  update_config(filecontent, pressed, disp_button);

  SDL_JoystickEventState(SDL_IGNORE);
  SDL_JoystickEventState(SDL_ENABLE);

  return true;
}

bool update_config(std::vector<std::string>& filecontent, std::string& pressed,
                   std::string& disp_button)
{
  using namespace std;
  stringstream ss;
  string newline;
  bool found_line = false;
  ss << pressed << " = " << disp_button;
  getline(ss, newline);
  for (int i = 0; i < filecontent.size(); i++) {
    string& line = filecontent[i];
    size_t beg = line.find_first_not_of("\t ");
    if (line.size() + 1 < pressed.size() || line.substr(beg, pressed.size())
        .compare(beg, pressed.size(), pressed) != 0
        || line.find_first_of("\t =", beg) > pressed.size()) {
      continue;
    }
    line.replace(beg, line.size() - beg, newline);
    found_line = true;
  }

  if (!found_line) {
    filecontent.push_back(newline);
  }

  return true;
}
