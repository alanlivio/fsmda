#ifndef FSMDA_UTILS_BASE64ZIP_CODING_H_
#define FSMDA_UTILS_BASE64ZIP_CODING_H_

#include <string>
using std::string;

string base64_encode(unsigned char const *, unsigned int len);
string base64_decode(string const &s);
string to_base64_from_file(string file_path);
int write_file_from_base64(string payload, char *file_path);
int zip_directory(const string &zipfile_path, const string &directory_path,
                  const string &iUriD);
int unzip_file(const char *zipname, const char *filedir);

#endif  // FSMDA_UTILS_BASE64ZIP_CODING_H_
