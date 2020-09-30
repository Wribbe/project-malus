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
  GLfloat * v;
  GLfloat * vt;
  GLfloat * vn;
  GLuint * f;
  struct {
    size_t v;
    size_t vt;
    size_t vn;
    size_t f;
  } num;
  struct {
    size_t v;
    size_t vt;
    size_t vn;
    size_t f;
  } size;
};


enum obj_type { V, VT, VN, F };


struct ret_data
ret_data_init(size_t size_data)
{
  size_t size_part = size_data/4;
  struct ret_data ret_data = {
    .v = malloc(size_part*sizeof(GLfloat)),
    .vt = malloc(size_part*sizeof(GLfloat)),
    .vn = malloc(size_part*sizeof(GLfloat)),
    .f = malloc(size_part*sizeof(GLuint)),
    .size.v = size_part,
    .size.vt = size_part,
    .size.vn = size_part,
    .size.f = size_part
  };

  return ret_data;
}



void
ret_data_finalize(struct ret_data * ret_data)
{
}


inline static char *
parse_texture_coords(char * c, struct ret_data * ret_data)
{
  c += 2;
  GLfloat data[2] = {0};
  sscanf(c, "%f %f", &data[0], &data[1]);
  while(!newline(c)) {
    c++;
  }
  for (size_t i=0; i<2; i++) {
    *(ret_data->vt+ret_data->num.vt) = data[i];
    ret_data->num.vt++;
  }
  return c;
}


inline static char *
parse_vertex(char * c, struct ret_data * ret_data)
{
  c += 1;
  GLfloat data[3] = {0};
  sscanf(c, "%f %f %f", &data[0], &data[1], &data[2]);
  while(!newline(c)) {
    c++;
  }
  for (size_t i=0; i<3; i++) {
    *(ret_data->v+ret_data->num.v) = data[i];
    ret_data->num.v++;
  }
  return c;
}


inline static char *
parse_vertex_normal(char * c, struct ret_data * ret_data)
{
  c += 2;
  GLfloat data[3] = {0};
  sscanf(c, "%f %f %f", &data[0], &data[1], &data[2]);
  while(!newline(c)) {
    c++;
  }
  for (size_t i=0; i<3; i++) {
    *(ret_data->vn+ret_data->num.vn) = data[i];
    ret_data->num.vn++;
  }
  return c;
}


inline static char *
parse_face(char * c, struct ret_data * ret_data)
{
  c += 1;
  GLuint data[3] = {0};
  sscanf(c, "%u/%u/%u", &data[0], &data[1], &data[2]);
  while(!newline(c)) {
    c++;
  }
  for (size_t i=0; i<3; i++) {
    *(ret_data->f+ret_data->num.f) = data[i];
    ret_data->num.f++;
  }
  return c;
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
