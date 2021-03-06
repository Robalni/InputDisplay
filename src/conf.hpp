/*
  In this file you find the Conf class that handles everything about
  configuration files, except parsing the lines.  That is done by
  ConfLine from conf_line.hpp and conf_line.cpp.

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

#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>

using std::string;
using std::endl;
using std::map;
using std::cerr;

class Conf
{
public:
  Conf();
  Conf(string const &fname, bool autoload = true);
  virtual ~Conf();
  string get_value(string const &key);
  bool get_int(string const &key, int &var);
  bool reload();
private:
  bool readfile(string const &filename);
  bool readfile();
  string fname;
  map<string, string> settings;
};
