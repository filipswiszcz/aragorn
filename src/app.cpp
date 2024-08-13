#include <vector>

#include <aragorn/app.hpp>

#pragma mark - App
#pragma region App {

// TODO init settings in constructor

void App::run() {

    logger.info("aragorn initialization...");

    glfwInit();

    this -> init_window();
    this -> init_vulkan();
    this -> init_core_loop();
    this -> clean_up();

}

void App::init_window() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this -> window = glfwCreateWindow(800, 600, "aragorn odyssey", nullptr, nullptr);
}

void App::init_vulkan() {

    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "aragorn odyssey";
    app_info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    app_info.pEngineName = "aragorn";
    app_info.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    app_info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo inst_info{};
    inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    inst_info.pApplicationInfo = &app_info;

    this -> glfw_extensions = glfwGetRequiredInstanceExtensions(&this -> glfw_extension_k);

    std::vector<const char*> req_extensions;
    for (uint32_t i = 0; i < this -> glfw_extension_k; i++) {
        req_extensions.emplace_back(this -> glfw_extensions[i]);
    }

    req_extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    
    inst_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    inst_info.enabledExtensionCount = (uint32_t) req_extensions.size();
    inst_info.ppEnabledExtensionNames = req_extensions.data();
    // inst_info.enabledLayerCount = 0;

    if (vkCreateInstance(&inst_info, nullptr, &this -> instance) != VK_SUCCESS) {
        logger.warning("failed to create vk instance.");
    }

}

void App::init_core_loop() {
    while (!glfwWindowShouldClose(this -> window)) {
        glfwPollEvents();
    }
}

void App::clean_up() {
    vkDestroyInstance(this -> instance, nullptr);
    glfwDestroyWindow(this -> window);
    glfwTerminate();
}

util::Logger App::getLogger() {
    return logger;
}


#pragma endregion Manager }