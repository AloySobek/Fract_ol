/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:34:33 by vrichese          #+#    #+#             */
/*   Updated: 2020/01/24 20:32:24 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.hpp"

int main(int argc, char **argv)
{
	std::vector<char *> extensions;
	std::vector<char *> layers;
	Window	mainWindow(1920, 1080, "Test");
	Vulkan	vulkan;

	vulkan.instanceInit(extensions, layers);
	mainWindow.run();
	return (0);
}