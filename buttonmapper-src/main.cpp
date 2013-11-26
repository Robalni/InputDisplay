#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

bool read_and_write(std::vector<std::string>& filecontent);
bool update_config(std::vector<std::string>& filecontent, std::string& type,
                   int number, std::string& disp_button);

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
    cout << filecontent[i] << endl;
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
  string type, disp_button;
  int number;

  cout << "Press a button." << endl;

  while (!got_input) {
    while (SDL_PollEvent(&event)) {
      //cout << "j" << endl;
      switch (event.type) {
      case SDL_JOYBUTTONDOWN:
        //cout << "button" << endl;
        got_input = true;
        type = "button";
        number = event.jbutton.button;
        break;
      case SDL_QUIT:
        return false;
      }
    }
  }

  cout << "You pressed button" << number << ". What should that do?\n"
    " -             c-right      z\n"
    " a             c-down       d-up\n"
    " b             c-left       d-right\n"
    " start         r            d-down\n"
    " c-up          l            d-left"
       << endl;

  cin >> disp_button;

  if (disp_button != "-") {
    update_config(filecontent, type, number, disp_button);
  }

  SDL_JoystickEventState(SDL_IGNORE);
  SDL_JoystickEventState(SDL_ENABLE);

  return true;
}

bool update_config(std::vector<std::string>& filecontent, std::string& type,
                   int number, std::string& disp_button)
{
  using namespace std;
  stringstream ss;
  string newline;
  string a;
  for (int i = 0; i < filecontent.size(); i++) {
    string& line = filecontent[i];
    size_t beg = line.find_first_not_of("\t ");
    ss << type << number;
    getline(ss, newline);
    if (line.size() < newline.size() || line.substr(beg, newline.size())
        .compare(beg, newline.size(), newline) != 0) {
      continue;
    }
    ss.clear();

    ss << type << number << " = " << disp_button;
    getline(ss, newline);
    line.replace(beg, line.size() - beg, newline);
  }

  return true;
}
