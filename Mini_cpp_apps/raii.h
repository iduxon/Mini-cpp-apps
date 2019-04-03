#ifndef RAII_H
#define RAII_H
#include <iostream>

class raii {
public:
  raii(const char *fpath, const char *mode);
  ~raii();

private:
  FILE *m_file;
};

#endif // RAII_H
