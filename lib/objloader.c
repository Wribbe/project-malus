#include "utils.h"

char *
res_load_obj(const char * filename)
{
  char * data = file_read(filename);
  printf("Loaded object from: %s\n", filename);
  return data;
}
