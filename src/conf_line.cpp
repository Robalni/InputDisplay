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

#include "conf_line.hpp"

#include <string>
#include <vector>

ConfLine::ConfLine(std::string const &line)
{
  size_t eq_sign = line.find('=');
  size_t first_non_blank = line.find_first_not_of(" \t\r");

  type = UNKNOWN;

  if (first_non_blank == std::string::npos || line[first_non_blank] == '#') {
    type = IGNORE;
  } else if (eq_sign != std::string::npos) {
    key = trim(line.substr(0, eq_sign));
    value = trim(line.substr(eq_sign + 1));
    if (key.length() > 0 && value.length() > 0) {
      type = VARIABLE;
    }
  } else {
    words = split(line);
    if (words.size() > 0) {
      type = COMMAND;
    }
  }
}

std::vector<std::string> ConfLine::split(std::string const &str)
{
  std::vector<std::string> vec;
  size_t first = 0;
  size_t length = 0;

  while (find_next_word(str, first, length)) {
    vec.push_back(str.substr(first, length));
    first += length;
  }

  return vec;
}

bool ConfLine::find_next_word(std::string const &str,
                               size_t &first, size_t &length)
{
  first = str.find_first_not_of(" \t\r", first);
  if (first == std::string::npos)
    return false;

  length = str.find_first_of(" \t\r", first);
  if (length == std::string::npos)
    length = str.length();
  length -= first;

  return true;
}

std::string ConfLine::trim(std::string const &str)
{
  size_t first = str.find_first_not_of(" \t\r");
  size_t last = str.find_last_not_of(" \t\r");

  if (first == std::string::npos) {
    return std::string("");
  } else {
    return str.substr(first, last - first + 1);
  }
}
