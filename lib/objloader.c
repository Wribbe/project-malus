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


struct ret_data {
  GLfloat * v_start, * v_end;
  GLfloat * vt_start, * vt_end;
  GLfloat * vn_start, * vn_end;
  GLuint * f_start, * f_end;
  size_t size_data;
  void * data;
};


struct ret_data
ret_data_init(size_t size_data)
{
  struct ret_data ret_data = {
    .data = malloc(size_data)
  };
  size_t size_part = size_data/4;

  ret_data.v_start = ret_data.data;
  ret_data.v_end = ret_data.data+size_part;

  ret_data.vt_start = ret_data.v_end+1;
  ret_data.vt_end = ret_data.vt_start+size_part;

  ret_data.v_start = ret_data.vt_end+1;
  ret_data.v_end = ret_data.v_start+size_part;

  ret_data.f_start = (GLuint *)(ret_data.v_end+1);
  ret_data.f_end = ret_data.data+size_data;

  return ret_data;
}


void
ret_data_finalize(struct ret_data * ret_data)
{
}


inline static char *
parse_texture_coords(char * c, struct ret_data * ret_data)
{

}


inline static char *
parse_vertex(char * c, struct ret_data * ret_data)
{

}


inline static char *
parse_vertex_normal(char * c, struct ret_data * ret_data)
{

}


inline static char *
parse_face(char * c, struct ret_data * ret_data)
{

}


struct renderable
parse_obj(char * data, size_t size_data)
{
  char * c = data;
  char * n = c+1;

  struct ret_data ret_data = ret_data_init(size_data);

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

    if (*c == 'v') {
      if (*n == 't') { // vt.
        c = parse_texture_coords(c, &ret_data);
      } else if (*n == 'n') { // vn.
        c = parse_vertex_normal(c, &ret_data);
      } else { // v.
        c = parse_vertex(c, &ret_data);
      }
    }
    else if (*c == 'f') {
      c = parse_face(c, &ret_data);
    }

    if (c >= data + size_data) {
      break;
    }

    c++;
    n = c+1;
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
