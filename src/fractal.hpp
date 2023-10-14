#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <stdio.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

GLFWwindow *init_window(const char *title);
void destroy_window(GLFWwindow *window);

#endif
