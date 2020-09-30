#include "utils.h"

struct renderable
parse_obj(char * data)
{
  return (struct renderable){
    .data = data
  };
}


struct renderable
res_load_obj(const char * filename)
{
  size_t size_data = 0;
  char * data = file_read(filename, &size_data);
  printf("Loaded object from: %s\n", filename);
  return parse_obj(data);
}
