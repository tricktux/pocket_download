/// @file main.cpp
/// @brief File description
/// @author Reinaldo Molina
/// @version  0.0
/// @date Mar 05 2019
// Copyright © 2019 Reinaldo Molina

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http:www.gnu.org/licenses/>.

#include <iostream>
#include <string>

#include "http_downloader.hpp"
#include "iniparser.h"

int main() {
  std::string url{
      "https://api.sunrise-sunset.org/json?lat=27.972572&lng=-82.796745"};
  std::vector<std::string> header{"Accept: application/json",
                                  "Content-Type: application/json",
                                  "charsets: utf-8"};
  HTTPDownloader downloader;
	downloader.set_header(header);
  std::string content = downloader.download(url);
  std::cout << content << std::endl;
  auto ini = iniparser_load("pocket.ini");

  iniparser_freedict(ini);
  return 0;
}
