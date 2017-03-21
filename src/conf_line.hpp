/*
  A ConfLine is a line in the configuration file and this class is
  used to parse those lines to make life easier for the Conf class
  from conf.hpp and conf.cpp.

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

#pragma once

#include <string>
#include <vector>

enum Line_type {
  UNKNOWN, IGNORE, VARIABLE, COMMAND
};

class ConfLine
{
public:
  ConfLine(std::string const &line);

  // If type is VARIABLE, key and value are the variable name and the
  // value of that variable.
  //
  // If type is COMMAND, there is always a words[0] that is the
  // command name and the rest of words is the arguments.
  Line_type type;

  std::string key;
  std::string value;
  std::vector<std::string> words;

private:
  std::vector<std::string> split(std::string const &str);

  // This function changes FIRST and LENGTH to the position of the
  // first character and the length of the next word.  It will start
  // looking at the character at FIRST.
  bool find_next_word(std::string const &str, size_t &first, size_t &length);

  std::string trim(std::string const &str);
};
