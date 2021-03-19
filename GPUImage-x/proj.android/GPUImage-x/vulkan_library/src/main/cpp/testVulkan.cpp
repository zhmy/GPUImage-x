//
// Created by Zhang,Mingyue(IBPD) on 2021/3/16.
//
#include "vulkan_wrapper/vulkan_wrapper.h"
#include <android/log.h>
#include <stdexcept>
#include <vector>
#include "testVulkan.h"

# define NULL __null

int innerInitVulkan() {

    // 1. check global properties
    if(!InitVulkan()) {
        __android_log_print(ANDROID_LOG_INFO, "zmy", "init vulkan error");
        return -1;
    }
    // 2. create instance
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Zmy";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Zmy Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = NULL;
    createInfo.enabledLayerCount = 0;

    VkInstance inst;
    if (vkCreateInstance(&createInfo, nullptr, &inst) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    // 3. check device
    uint32_t gpu_count = 1;
    VkResult res = vkEnumeratePhysicalDevices(inst, &gpu_count, NULL);
    if (gpu_count == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    __android_log_print(ANDROID_LOG_INFO, "zmy", "gpu_count %d", gpu_count);
    std::vector<VkPhysicalDevice> devices(gpu_count);
    res = vkEnumeratePhysicalDevices(inst, &gpu_count, devices.data());

    // 4. init device
    VkDevice device = init_device(devices);
    VkDevice* de = &device;

    // 5. init command buffer
    uint32_t graphics_queue_family_index;
    VkCommandPool cmd_pool;

    VkCommandPoolCreateInfo cmd_pool_info = {};
    cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmd_pool_info.pNext = NULL;
    cmd_pool_info.queueFamilyIndex = graphics_queue_family_index;
    cmd_pool_info.flags = 0;

    res = vkCreateCommandPool(*de, &cmd_pool_info, NULL, &cmd_pool);

    /* Create the command buffer from the command pool */
    VkCommandBufferAllocateInfo cmd_info = {};
    cmd_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd_info.pNext = NULL;
    cmd_info.commandPool = cmd_pool;
    cmd_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd_info.commandBufferCount = 1;

    VkCommandBuffer cmd; // Buffer for initialization commands
    res = vkAllocateCommandBuffers(device, &cmd_info, &cmd);


//    vkDestroyDevice(device, NULL);
//    vkDestroyInstance(inst, NULL);
    __android_log_print(ANDROID_LOG_INFO, "zmy", "starting");
    return 0;
}

VkDevice init_device(std::vector<VkPhysicalDevice> devices) {
    VkDeviceQueueCreateInfo queue_info = {};
    uint32_t queue_family_count = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(devices[0], &queue_family_count, NULL);
    __android_log_print(ANDROID_LOG_INFO, "zmy", "queue_family_count %d", queue_family_count);

    std::vector<VkQueueFamilyProperties> queue_props(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(devices[0], &queue_family_count, queue_props.data());

    bool found = false;
    for (unsigned int i = 0; i < queue_family_count; i++) {
        if (queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queue_info.queueFamilyIndex = i;
            found = true;
            break;
        }
    }
    __android_log_print(ANDROID_LOG_INFO, "zmy", "found %d", found == true);

    float queue_priorities[1] = {0.0};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.pNext = NULL;
    queue_info.queueCount = 1;
    queue_info.pQueuePriorities = queue_priorities;

    VkDeviceCreateInfo device_info = {};
    device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_info.pNext = NULL;
    device_info.queueCreateInfoCount = 1;
    device_info.pQueueCreateInfos = &queue_info;
    device_info.enabledExtensionCount = 0;
    device_info.ppEnabledExtensionNames = NULL;
    device_info.enabledLayerCount = 0;
    device_info.ppEnabledLayerNames = NULL;
    device_info.pEnabledFeatures = NULL;

    VkDevice device;
    VkResult res = vkCreateDevice(devices[0], &device_info, NULL, &device);
    return device;
}

