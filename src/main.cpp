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

#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string url = "https://api.sunrise-sunset.org";
  std::string postfields = "json?lat=27.972572&lng=-82.796745";

  struct curl_slist *headers = nullptr; // init to NULL is important

  headers = curl_slist_append(headers, "Accept: application/json");
  headers = curl_slist_append(headers, "Content-Type: application/json");
  headers = curl_slist_append(headers, "charsets: utf-8");

  auto curl = curl_easy_init();
  if (!curl) {
    std::cout << "curl_easy_getinfo() failed!" << std::endl;
    return 1;
  }

  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postfields.length());
  curl_easy_setopt(curl, CURLOPT_POST, 1);

  curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  auto rc = curl_easy_perform(curl);

  if (rc != CURLE_OK) {
    std::cout << "curl_easy_perform() failed!" << std::endl;
    return 2;
  }
  char *ct = nullptr;
  /* ask for the content-type */
  rc = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
	if ((rc != CURLE_OK) || (ct == nullptr) || (ct[0] == 0)) {
		std::cout << "curl_easy_getinfo() failed!" << std::endl;
		return 2;
	}

	printf("We received Content-Type: %s\n", ct);
  return 0;
}
