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

#include "Conf.hpp"

Conf::Conf()
{
}

Conf::Conf(string const &fname)
{
  this->load(fname);
}

Conf::~Conf()
{
}

bool Conf::load(string const &fname)
{
  this->fname = fname;
  return this->readfile();
}

bool Conf::readfile(string const &filename)
{
  using namespace std;
  string line, key, value;
  ifstream file;
  file.open(filename.c_str());
  if (file.is_open()) {
    while (getline(file, line)) {
      if (line[0] == '#') {
        continue;
      }
      if (line.size() > 0 && line[line.size() - 1] < 32) {
        line.resize(line.size() - 1);
      }
      size_t found_eq = line.find('=');
      if (found_eq != string::npos) {
        key = line.substr(0, found_eq);
        trim(key);
        value = line.substr(found_eq + 1);
        trim(value);
        settings[key] = value;
      } else {
        size_t start_first_word = line.find_first_not_of(" \t");
        size_t after_first_word = line.find_first_of(" \t", start_first_word);
        if (after_first_word == string::npos
            || start_first_word == string::npos)
          continue;
        string command = line.substr(0, after_first_word);
        string argument = line.substr(command.length());
        trim(command);
        trim(argument);
        if (command == "include" && argument.length() > 0) {
          readfile(argument);
        }
      }
    }
  } else {
    cerr << "Failed to open " << filename << endl;
    return false;
  }
  file.close();

  return true;
}

bool Conf::readfile()
{
  return readfile(this->fname);
}

string Conf::get_value(string const &key)
{
  return this->settings[key];
}

bool Conf::get_int(string const &key, int &var)
{
  string val = this->get_value(key);
  if (val == "") {
    return false;
  } else {
    var = atoi(val.c_str());
    return true;
  }
}

bool Conf::reload()
{
  this->settings.clear();
  this->readfile();
  return true;
}

void Conf::trim(string &str)
{
  string::size_type pos = str.find_last_not_of(" \t");
  if (pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(" \t");
    if (pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}
