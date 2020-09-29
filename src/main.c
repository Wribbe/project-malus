#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

void
render(void)
{
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}


int
main(void)
{

  if (!glfwInit()) {
    printf("Could not load glfw, aborting\n");
    return(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  size_t width = 800, height = 600;

  GLFWwindow * window = glfwCreateWindow(
    width,
    height,
    "Project Malus",
    NULL,
    NULL
  );

  glfwMakeContextCurrent(window);
  if (window == NULL) {
    printf("Failed to create glfw-window, aborting.\n");
    return EXIT_FAILURE;
  }

  if (!gladLoadGL()) {
    printf("Could not load opengl-bindings, aborting.\n");
    return EXIT_FAILURE;
  }

  printf("OpenGL Version %d.%d loaded.\n", GLVersion.major, GLVersion.minor);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    render();
    glfwSwapBuffers(window);
  }

  res_load_obj("temp_file_name.obj");
}
