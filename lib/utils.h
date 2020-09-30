#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>


struct renderable {
  size_t num_vertices;
  size_t size_data;
  char * data;
};


char *
file_read(const char * filename, size_t * size_data);


struct renderable
res_load_obj(const char * filename);


#endif
