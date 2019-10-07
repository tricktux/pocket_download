/**
 * HTTPDownloader.cpp
 *
 * A simple C++ wrapper for the libcurl easy API.
 *
 * Written by Uli Köhler (techoverflow.net)
 * Published under CC0 1.0 Universal (public domain)
 */

#include "http_downloader.hpp"
#include <iostream>
#include <sstream>

void HTTPDownloader::set_option(CURLoption opt, int val) {
  if (curl == nullptr)
    return;

  curl_easy_setopt(curl, opt, val);
}

void HTTPDownloader::set_option(CURLoption opt, const char *val) {
  if (curl == nullptr)
    return;

	if (val == nullptr)
		return;

  curl_easy_setopt(curl, opt, val);
}

void HTTPDownloader::set_header(const std::vector<std::string> &str_headers) {
  for (auto &&header : str_headers) {
    headers = curl_slist_append(headers, header.c_str());
  }
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
  std::string data((const char *)ptr, (size_t)size * nmemb);
  *((std::stringstream *)stream) << data << std::endl;
  return size * nmemb;
}

std::string HTTPDownloader::download(const std::string &url) {
  if (curl == nullptr) {
    std::cout << __FUNCTION__ << ": Invalid curl pointer.\n";
    return {};
  }

  if (url.empty()) {
    std::cout << __FUNCTION__ << ": Empty url provided.\n";
    return {};
  }
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  /* example.com is redirected, so we tell libcurl to follow redirection */
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL,
                   1); // Prevent "longjmp causes uninitialized stack frame" bug
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
  std::stringstream out;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
  /* Perform the request, res will get the return code */
  CURLcode res = curl_easy_perform(curl);
  /* Check for errors */
  if (res != CURLE_OK) {
    std::cout << __FUNCTION__ << ": curl_easy_perform() failed:\n\t"
              << curl_easy_strerror(res);
    return {};
  }
  return out.str();
}
