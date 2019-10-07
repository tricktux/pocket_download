/**
 * HTTPDownloader.hpp
 *
 * A simple C++ wrapper for the libcurl easy API.
 *
 * Written by Uli Köhler (techoverflow.net)
 * Published under CC0 1.0 Universal (public domain)
 */
#ifndef HTTPDOWNLOADER_HPP
#define HTTPDOWNLOADER_HPP

#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <string_view>
#include <vector>

/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 */
class HTTPDownloader {
public:
  HTTPDownloader() : curl(nullptr) { curl = curl_easy_init(); }

  ~HTTPDownloader() {
    if (curl != nullptr)
      curl_easy_cleanup(curl);
  }

  /**
   * Download a file using HTTP GET and store in in a std::string
   * @param url The URL to download
   * @return The download result
   */
  void set_header(const std::vector<std::string> &headers);
  void set_option(CURLoption opt, int val);
  void set_option(CURLoption opt, const char *val);
  std::string download(const std::string &url);

private:
  void *curl;
  struct curl_slist *headers = NULL; // init to NULL is important
};

#endif /* HTTPDOWNLOADER_HPP */
