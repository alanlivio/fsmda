#ifndef FSMDA_UTILS_BASE64ZIP_CODING_H_
#define FSMDA_UTILS_BASE64ZIP_CODING_H_

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>
using std::string;

/*----------------------------------------------------------------------
 |   global function
 +---------------------------------------------------------------------*/

string base64_encode(unsigned char const *, unsigned int len);
string base64_decode(string const &s);
string getBase64FromFile(string file_path);
int writeFileFromBase64(string payload, char *file_path);
int zip_directory(const string &zipfile_path, const string &directory_path,
                  const string &iUriD);
int unzip_file(const char *zipname, const char *filedir);

#endif  // FSMDA_UTILS_BASE64ZIP_CODING_H_
