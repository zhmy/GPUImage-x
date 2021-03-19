//
// Created by Zhang,Mingyue(IBPD) on 2021/3/19.
//
#include "vulkan_wrapper/vulkan_wrapper.h"

#ifndef GPUIMAGE_X_TESTVULKAN_H
#define GPUIMAGE_X_TESTVULKAN_H
int innerInitVulkan();
VkDevice init_device(std::vector<VkPhysicalDevice> devices);
#endif //GPUIMAGE_X_TESTVULKAN_H
