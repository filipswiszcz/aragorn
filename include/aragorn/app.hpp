#define GLFW_INCLUDE_VULKAN
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include <aragorn/util/logger.hpp>

#ifndef MANAGER_H
#define MANAGER_H

class App {

    public:

        void run();

        util::Logger getLogger();

    private:

        util::Logger logger;

        // settings -> (width, height etc)

        GLFWwindow* window;

        VkInstance instance;

        const char** glfw_extensions;
        uint32_t glfw_extension_k = 0;

        void init_window();

        void init_vulkan();

        void init_core_loop();

        void clean_up();

};

#endif