#include "fsmda/utils/base64zip_coding.h"
#include <zip.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

using std::cout;
using std::clog;
using std::endl;
using std::ofstream;
using std::ios;

bool isDirectory(const char *path) {
  struct stat f_stat;
  stat(path, &f_stat);
  if (f_stat.st_mode & S_IFREG) {
    return false;
  }
  if (f_stat.st_mode & S_IFDIR) {
    return true;
  }
  return false;
}

bool getZipError(zip *file, string *strError) {
  bool hasError = false;
  int zipErr, sysErr;
  char buff[2048];

  zip_error_get(file, &zipErr, &sysErr);
  if (zipErr != 0) {
    zip_error_to_str(buff, 2048, zipErr, sysErr);
    strError->assign(buff, strlen(buff));
    hasError = true;
  }

  return hasError;
}

static void printZipError(string function, string strError) {
  clog << function << " Warning! libzip error: '";
  clog << strError << "'" << endl;
}

int zipwalker(void *zipfile, string initdir, string dirpath, string iUriD) {
  DIR *d;
  struct dirent *dir;
  FILE *fp;
  string relpath;
  string fullpath;
  struct zip *file;
  int len_dirpath;
  int len_initdir;
  int ret = 0;
  string strDirName;
  string strError;
  bool hasError;

  d = opendir(initdir.c_str());
  if (d == NULL) {
    return -1;
  }

  file        = (struct zip *)zipfile;
  len_dirpath = dirpath.length();
  len_initdir = initdir.length();

  while ((dir = readdir(d))) {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
      continue;
    }

    strDirName.assign(dir->d_name, strlen(dir->d_name));
    fullpath = initdir + iUriD + strDirName;
    if (fullpath.length() > len_dirpath) {
      // Uses "/" as separator because is the default zip funcion separator.
      relpath = fullpath.substr(len_dirpath + 1);
    } else {
      continue;
    }

    if (isDirectory(fullpath.c_str())) {
      // \fixme We should not use that!
      chdir(fullpath.c_str());

      clog << "Directory ( " << relpath << " ) " << endl;
      if (zip_dir_add(file, relpath.c_str(), ZIP_FL_ENC_GUESS) < 0) {
        getZipError(file, &strError);
        printZipError("zipwalker", strError);
        ret = -1;
        break;
      }

      if (zipwalker(file, fullpath, dirpath, iUriD) < 0) {
        getZipError(file, &strError);
        printZipError("zipwalker", strError);
        ret = -1;
        break;
      }

      // \fixme We should not use that!
      clog << "Returning to dir '" << initdir << "'" << endl;
      chdir(initdir.c_str());

    } else {
      clog << ":: full uri: " << fullpath << endl;
      clog << ":: init dir: " << initdir << endl;
      clog << ":: file name: " << string(dir->d_name) << endl;
      clog << ":: relpath ( " << relpath << " ) " << endl;

      fp = fopen(fullpath.c_str(), "rb");
      if (fp == NULL) {
        clog << ":: can't open " << string(relpath) << endl;

      } else {
        struct zip_source *s;

        s = zip_source_filep(file, fp, 0, -1);
        if (s == NULL) {
          clog << ":: error [" << string(relpath)
               << "]: " << string(zip_strerror(file)) << endl;
          ret = -1;
          break;
        }

        if (zip_add(file, relpath.c_str(), s) == -1) {
          zip_source_free(s);
          clog << ":: error [" << string(relpath)
               << "]: " << string(zip_strerror(file)) << endl;
          ret = -1;
          break;
        }
      }
    }
  }

  clog << "zipwalker closing dir" << endl;
  closedir(d);
  clog << "zipwalker all done!" << endl;
  return ret;
}

int unzip_file(const char *zipname, const char *filedir) {
  struct zip *zipf;
  struct zip_file *inf;
  char cur_dir[2000];
  char buf[1024];
  int len = 0;
  int k;
  int errorp;
  FILE *ofp;
  int i;
  const char *cur_file_name;
  int name_len;

  zipf = zip_open(zipname, 0, &errorp);
  if (!zipf) {
    return 0;
  }
  chdir(filedir);
  for (k = 0; (inf = zip_fopen_index(zipf, k, 0)); k++) {
    cur_file_name = zip_get_name(zipf, k, 0);

    if ((k == 0) && (cur_file_name == NULL)) {
      continue;
    }

    name_len = strlen(cur_file_name);

    char *filename = (char *)malloc((name_len + 3) * sizeof(char));
    filename[0]    = '.';
#ifdef WIN32
    filename[1] = '\\';

#else
    filename[1] = '/';
#endif
    filename[2] = '\0';

    strcat(filename, cur_file_name);
    if (cur_file_name[name_len - 1] == '/') {
      // printf(":: creating dir: %s\n",filename);
      clog << ":: creating dir: " << filename << endl;

#ifdef WIN32
      _mkdir(filename);
#else
      mkdir(filename, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    } else {
      // printf(":: inflating %s",filename);//cout
      clog << ":: inflating file " << filename << endl;

      ofp = fopen(filename, "wb");
      if (!ofp) {
        continue;
      }

      while ((len = zip_fread(inf, buf, 1024))) {
        fwrite(buf, sizeof(char), len, ofp);
      }
      //				printf(" [done] \n");
      // close the files
      zip_fclose(inf);
      fclose(ofp);
    }
    // printf(" [done]\n");//cout
    clog << " [done]" << endl;
    free(filename);
  }
  // go back to our original dir
  chdir(cur_dir);
  return 1;
}

int zip_directory(const string &zipfile_path, const string &directory_path,
                  const string &iUriD) {
  struct zip *zipFile;
  int error_open;
  string dir_name;
  string partial_path;
  int pos;
  string strError;
  string functionStr;
  size_t strPos;

  clog << "functions::zip_directory " << endl;
  clog << "zipfile_path = " << zipfile_path << endl;
  clog << "directory_path = " << directory_path << endl;

  error_open = 0;

  if ((zipFile = zip_open(zipfile_path.c_str(), ZIP_CREATE, &error_open)) ==
      NULL) {
    getZipError(zipFile, &strError);
    printZipError("zip_directory - zip_walker", strError);
    return 1;
  }

  if (zipFile != NULL && error_open == 0) {
    strPos = directory_path.find_last_of(iUriD);
    if (strPos == std::string::npos) {
      dir_name = directory_path;

    } else {
      dir_name = directory_path.substr(strPos + 1);
    }

    partial_path = directory_path;

    // This make no sense. I am always adding an empty directory!

    // \fixme This should not be recursive! So, there would not
    // be a possibility of stack overflow.
    if (zipwalker(zipFile, directory_path, partial_path, iUriD) < 0) {
      getZipError(zipFile, &strError);
      printZipError("zip_directory - zip_walker", strError);
      zip_discard(zipFile);
      return -1;
    }

    if (zip_close(zipFile) == -1) {
      clog << "functions::zip_directory Warning! can't close zip archive '";
      clog << zipfile_path << endl;
      return -1;
    }

  } else {
    clog << "functions::zip_directory Warning! Can't open '";
    clog << zipfile_path << "': error code = " << error_open;
    clog << endl;
    return -1;
  }

  clog << "functions::zip_directory all done" << endl;
  return 0;
}

static const string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

string getBase64FromFile(string file_path) {
  string sResult;
  FILE *readfile;
  char *buffer;
  unsigned long fileLen;

  readfile = fopen(file_path.c_str(), "rb");
  if (!readfile) {
    clog << "getBase64FromFile Unable to open file '" << file_path;
    clog << "'" << endl;
    return "";
  }

  struct stat stbuf;
  stat(file_path.c_str(), &stbuf);
  fileLen = stbuf.st_size;

  clog << "getBase64FromFile FILE LEN = " << fileLen << endl;
  // Allocate memory
  buffer = (char *)malloc(fileLen + 1);

  if (!buffer) {
    clog << "getBase64FromFile malloc" << fileLen << endl;
    fclose(readfile);
    return "";
  }

  // Read file contents into buffer
  int read_bytes = fread(buffer, 1, stbuf.st_size, readfile);

  // dump_buffer(buffer, euli);

  fclose(readfile);

  // readFile

  sResult = base64_encode(reinterpret_cast<const unsigned char *>(buffer),
                          read_bytes);

  free(buffer);

  clog << "getBase64FromFile BASE 64 LEN = ";
  clog << sResult.length() << endl;

  // Finishes the base64 encoding and returns the result as a string
  return sResult;
}

int writeFileFromBase64(string payload, char *file_path) {
  int len = -1;
  string result;

  ofstream out(file_path, ios::out | ios::binary);

  if (!out) {
    clog << "writeFileFromBase64 error opening file: ";
    clog << file_path << endl;
    return -1;
  }

  clog << "util::wb64 PAYLOAD SIZE = " << strlen(payload.c_str()) << endl;

  string strDecode = base64_decode(payload);

  out << strDecode;
  out.close();

  len = (int)payload.size();

  clog << "util::wb64 wrote " << file_path;
  clog << " from " << len << " chars (b64)" << endl;
  return len;
}

std::string base64_encode(unsigned char const *bytes_to_encode,
                          unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] =
          ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] =
          ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; (i < 4); i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] =
        ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] =
        ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while ((i++ < 3))
      ret += '=';
  }

  return ret;
}

std::string base64_decode(std::string const &encoded_string) {
  int in_len = encoded_string.size();

  // std::clog << ":: base64_decode.encoded_string.size()="<<in_len<<std::endl;

  int i   = 0;
  int j   = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && (encoded_string[in_] != '=') &&
         is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_];
    in_++;
    if (i == 4) {
      for (i = 0; i < 4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] =
          (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] =
          ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 4; j++)
      char_array_4[j] = 0;

    for (j = 0; j < 4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] =
        ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++)
      ret += char_array_3[j];
  }

  return ret;
}
