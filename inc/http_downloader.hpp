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

#include <string>
#include <string_view>
#include <vector>

/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 */
class HTTPDownloader {
public:
  HTTPDownloader();
  ~HTTPDownloader();
  /**
   * Download a file using HTTP GET and store in in a std::string
   * @param url The URL to download
   * @return The download result
   */
	void set_header(const std::vector<std::string> &headers);
	void set_post(std::string_view postfields);
  std::string download(const std::string &url);

private:
  void *curl;
	struct curl_slist *headers = NULL; // init to NULL is important
};

#endif /* HTTPDOWNLOADER_HPP */
