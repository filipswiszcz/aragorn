#define VK_USE_PLATFORM_MACOS_KHR

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#include <aragorn/util/logger.hpp>

#ifndef ENGINE_H
#define ENGINE_H

class Engine {

    public:

        void run();

        util::Logger getLogger() {return logger;}

        VkInstance getVkInstance() {return instance;}

    private:

        util::Logger logger;

        // settings -> (width, height etc)

        GLFWwindow* window;
        VkInstance instance;
        VkSurfaceKHR surface;
        VkPhysicalDevice phys_device = VK_NULL_HANDLE;
        VkDevice device;
        
        VkQueue graphics_cmds_queue;
        VkQueue surface_presentations_queue;

        const char** glfw_extensions;
        uint32_t glfw_extension_k = 0;

        void init_window();

        void init_vulkan();

        void init_surface();

        void init_physical_device();

        void init_logical_device();

        void init_core_loop();

        void init_engine_destruction();

};

#endif