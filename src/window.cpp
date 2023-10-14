#include "fractal.hpp"

void glfw_error_callback(int error_code, const char *description)
{
    printf("GLFW Error callback: %d, %s", error_code, description);
}

GLFWwindow *init_window(const char *title)
{
    GLFWwindow *window;

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        return (NULL);
    }

    if (!glfwVulkanSupported())
    {
        return (NULL);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);

    if (!window)
    {
        glfwTerminate();

        return (NULL);
    }

    return window;
}

void destroy_window(GLFWwindow *window)
{
    glfwDestroyWindow(window);

    glfwTerminate();
}
