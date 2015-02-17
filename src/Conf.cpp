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
#include "Conf_line.hpp"

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
  string line;
  ifstream file;
  Conf_line cline;

  file.open(filename.c_str());
  if (!file.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return false;
  }

  while (getline(file, line)) {
    cline.set(line);
    switch (cline.type) {
    case variable:
      settings[cline.key] = cline.value;
      break;
    case command:
      if (cline.command == "include" && cline.n_args == 1) {
        readfile(cline.arguments[0]);
      }
      break;
    }
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
