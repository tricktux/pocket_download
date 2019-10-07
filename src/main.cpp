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
	dictionary* ini = iniparser_load("pocket.ini");
	if (!ini) {
		std::cout << "Bad ini" << std::endl;
		return 1;
	}

	std::string url = iniparser_getstring(ini, "api:url", NULL);
	std::cout << "[ini]: url = " << url << std::endl;
	iniparser_freedict(ini);
	return 0;
  std::vector<std::string> header{
      "X-Accept: application/json",
      "Content-Type: application/json; charset=UTF8"};
  // std::string postfields{"{\"consumer_key\":\"1234-abcd1234abcd1234abcd1234\",
		// \"redirect_uri\":\"pocketapp1234:authorizationFinished\"}"};

  HTTPDownloader downloader;
  downloader.set_header(header);
  // downloader.set_option(CURLOPT_POSTFIELDS, postfields.c_str());
  // downloader.set_option(CURLOPT_POSTFIELDSIZE, postfields.length());
  downloader.set_option(CURLOPT_POST, 1);
  std::string content = downloader.download(url);
  std::cout << content << std::endl;
  return 0;
}
