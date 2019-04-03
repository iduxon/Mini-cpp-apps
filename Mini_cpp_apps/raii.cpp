#include "raii.h"

raii::raii(const char *fpath, const char *mode) { m_file = fopen(fpath, mode); }
raii::~raii() { fclose(m_file); }
