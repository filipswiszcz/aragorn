#define GLFW_INCLUDE_VULKAN
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

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
        VkPhysicalDevice phys_device = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue queue;

        const char** glfw_extensions;
        uint32_t glfw_extension_k = 0;

        void init_window();

        void init_vulkan();

        void init_physical_device();

        void init_logical_device();

        void init_core_loop();

        void init_engine_destruction();

};

#endif