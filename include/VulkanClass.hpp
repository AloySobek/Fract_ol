/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VulkanClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:36:28 by Rustam            #+#    #+#             */
/*   Updated: 2020/01/23 20:10:25 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VULKAN_CLASS_HPP
# define VULKAN_CLASS_HPP

# include "fractal.hpp"

class Vulkan
{
	public:

		Vulkan() { };

		void instanceInit(std::vector<char *> &extensions = std::vector(), std::vector<char *> &layers = std::vector())
		{
			uint32_t							counter{0};
			std::vector<VkExtensionProperties>	extProperties;
			std::vector<char *>					enabledExt;
			std::vector<VkLayerProperties>		layerProperties;
			std::vector<char *>					enabledLay;
			VkApplicationInfo					appInfo{VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "Test", VK_MAKE_VERSION(1, 0, 0), "No", VK_MAKE_VERSION(1, 0, 0), VK_VERSION_1_1};

			vkEnumerateInstanceExtensionProperties(nullptr, &counter, nullptr);
			extProperties.resize(counter);
			vkEnumerateInstanceExtensionProperties(nullptr, &counter, extProperties.data());
			for (VkExtensionProperties &iter : extProperties)
				for (char *(&strIter) : extensions)
					if (!strcmp(iter.extensionName, strIter))
						enabledLay.push_back(strIter);

			vkEnumerateInstanceLayerProperties(&counter, nullptr);
			layerProperties.resize(counter);
			vkEnumerateInstanceLayerProperties(&counter, layerProperties.data());
			for (VkLayerProperties &iter : layerProperties)
				for (char *(&strIter) : layers)
					if (!strcmp(iter.layerName, strIter))
						enabledLay.push_back(strIter);

			instance.getCreateInfo().enabledExtensionCount = enabledExt.size();
			instance.getCreateInfo().enabledLayerCount = enabledLay.size();
			instance.getCreateInfo().ppEnabledExtensionNames = enabledExt.data();
			instance.getCreateInfo().ppEnabledLayerNames = enabledLay.data();
			instance.getCreateInfo().pApplicationInfo = &appInfo;
			try { instance.create(); }
			catch (const std::exception &error) { std::cout << error.what() << std::endl; }
		}

	private:
		FbInstance	instance;

};

#endif