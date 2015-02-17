/*
  Copyright (C) 2015  Robert Alm Nilsson <rorialni@gmail.com>

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

#ifndef CONF_LINE_HPP
#define CONF_LINE_HPP

#include <string>

class Conf_line
{
public:
  using std::string;
  using std::vector;

  void set(string line);

  string key;
  string value;
  string command;
  vector<string> arguments;
}

#endif // CONF_LINE_HPP
