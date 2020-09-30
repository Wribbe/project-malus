#include "utils.h"


static inline GLboolean
newline(const char * c) {
  switch (*c) {
    case('\n'):
    case('\r'):
    case('\0'):
      return GL_TRUE;
    default:
      return GL_FALSE;
  }
}


struct renderable
parse_obj(char * data, size_t size_data)
{
  char * c = data;
  char * n = c+1;

  GLboolean ignore = GL_FALSE;

  for (;;) {

    if (ignore && newline(c)) {
      ignore = GL_FALSE;
      c++; n++;
    }

    if (*c == '#' || *c == 'o' || *c == 's') {
      ignore = GL_TRUE;
    }

    if (ignore) {
      c++; n++;
      continue;
    }

    printf("%c", *c);

    if (c >= data + size_data) {
      break;
    }

    c++;
    n++;
  }

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
  return parse_obj(data, size_data);
}
