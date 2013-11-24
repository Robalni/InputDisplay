#include "Conf.h"

Conf::Conf(char *fname)
{
  this->fname = fname;
  this->readfile();
}

Conf::~Conf()
{
  //dtor
}

bool Conf::readfile()
{
  using namespace std;
  string line, key, value;
  ifstream file;
  file.open(fname.c_str());
  if (file.is_open()) {
    while (getline(file, line)) {
      if (line[0] == '#') {
        continue;
      }
      size_t found_eq = line.find('=');
      if (found_eq != string::npos) {
        key = line.substr(0, found_eq);
        trim(key);
        value = line.substr(found_eq + 1);
        trim(value);
        settings[key] = value;
      }
    }
  } else {
    return false;
  }
  file.close();

  return true;
}

string Conf::get_value(string key)
{
  return this->settings[key];
}

bool Conf::reload()
{
  this->settings.clear();
  this->readfile();
  return true;
}

void Conf::trim(string& str)
{
  string::size_type pos = str.find_last_not_of(" \t");
  if (pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(" \t");
    if (pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}