/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:51:15 by Rustam            #+#    #+#             */
/*   Updated: 2020/01/23 18:32:46 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_CLASS_HPP
# define WINDOW_CLASS_HPP

#include "fractal.hpp"

class Window
{
	public:
		Window(uint32_t width = 1920, uint32_t height = 1080, const char *title = "Default")
			: width{width}, height{height}, window{nullptr}
		{
			if (glfwInit() != GLFW_TRUE)
				throw std::runtime_error("Failed to init Glfw");
			glfwSetErrorCallback(errorCallback);
			create(width, height, title);
			glfwSetKeyCallback(window, keyCallback);
			setWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
			setWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}

		void create(int width, int height, const char *title)
		{
			assert(!window);
			if (!(window = glfwCreateWindow(width, height, title, nullptr, nullptr)))
				throw std::runtime_error("Failed to recreate Glfw Window");
		}

		void setWindowHint(int hint, int value) { glfwWindowHint(hint, value); }

		void run()
		{
			while (!glfwWindowShouldClose(window))
			{
				glfwPollEvents();
			}
			glfwDestroyWindow(window);
			window = nullptr;
		}

		~Window() { glfwTerminate(); }

	private:
		GLFWwindow	*window;

		uint32_t	width{1920};
		uint32_t	height{1920};

		static void errorCallback(int error, const char *description)
		{
			std::cout << "Error occured, code: " << error << ", description: " << description << std::endl;
		}

		static void keyCallback(GLFWwindow *window, int keyCode, int scancode, int action, int mods)
		{
			if (keyCode == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
};

#endif