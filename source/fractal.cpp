/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:34:33 by vrichese          #+#    #+#             */
/*   Updated: 2020/01/23 20:08:41 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.hpp"

int main(int argc, char **argv)
{
	Window	mainWindow(1920, 1080, "Test");
	Vulkan	vulkan;

	vulkan.instanceInit();
	mainWindow.run();
	return (0);
}