#include <set>
#include <vector>

#include <aragorn/util/cmd_family_finder.hpp>
#include <aragorn/util/gpu_picker.hpp>
#include <aragorn/engine.hpp>

#pragma mark - Engine
#pragma region Engine {

#ifdef DEBUG
    const bool VALIDATION_LAYERS_ENABLED = false;
#else
    const bool VALIDATION_LAYERS_ENABLED = true;
#endif

const std::vector<const char*> validation_layers = {"VK_LAYER_KHRONOS_validation"};

// TODO init settings in constructor

void Engine::run() {

    logger.info("aragorn initialization...");

    glfwInit();

    this -> init_window();
    this -> init_vulkan();
    this -> init_core_loop();
    this -> init_engine_destruction();

}

void Engine::init_window() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this -> window = glfwCreateWindow(800, 600, "aragorn odyssey", nullptr, nullptr);
}

void Engine::init_vulkan() {

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

void Engine::init_surface() {
    if (glfwCreateWindowSurface(this -> instance, this -> window, nullptr, &this -> surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create surface!");
    }
}

void Engine::init_physical_device() {
    this -> phys_device = util::get_most_suitable_gpu(this -> instance);
}

void Engine::init_logical_device() {

    std::vector<VkQueueFamilyProperties> families = util::get_all_queue_families(this -> phys_device);

    util::QueueFamilyFinder family_finder;
    int i = 0;

    for (const auto& family : families) {
        if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            family_finder.graphics_cmds_families = i;
        }

        VkBool32 status = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(this -> phys_device, i, this -> surface, &status);
        if (status) {
            family_finder.surface_presentations_families = i;
        } i++;
    }

    std::vector<VkDeviceQueueCreateInfo> queue_devices_info;
    std::set<uint32_t> unique_families = {family_finder.graphics_cmds_families.value(), family_finder.surface_presentations_families.value()};
    
    float queue_priority = 1.0f;

    for (uint32_t family : unique_families) {
        VkDeviceQueueCreateInfo queue_device_info{};
        queue_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_device_info.queueFamilyIndex = family;
        queue_device_info.queueCount = 1;
        queue_device_info.pQueuePriorities = &queue_priority;

        queue_devices_info.push_back(queue_device_info);
    }

    VkDeviceCreateInfo device_info{};
    device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_info.pQueueCreateInfos = queue_devices_info.data();
    device_info.queueCreateInfoCount = static_cast<uint32_t>(queue_devices_info.size());

    VkPhysicalDeviceFeatures device_features{};
    device_info.pEnabledFeatures = &device_features;

    device_info.enabledExtensionCount = 0;

    if (VALIDATION_LAYERS_ENABLED) {
        device_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
        device_info.ppEnabledLayerNames = validation_layers.data();
    } else {
        device_info.enabledLayerCount = 0;
    }

    if (vkCreateDevice(this -> phys_device, &device_info, nullptr, &this -> device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
        // TODO handle error
    }

    vkGetDeviceQueue(this -> device, family_finder.graphics_cmds_families.value(), 0, &graphics_cmds_queue);
    vkGetDeviceQueue(this -> device, family_finder.surface_presentations_families.value(), 0, &surface_presentations_queue);
}

void Engine::init_core_loop() {
    while (!glfwWindowShouldClose(this -> window)) {
        glfwPollEvents();
    }
}

void Engine::init_engine_destruction() {
    vkDestroyDevice(this -> device, nullptr);

    if (VALIDATION_LAYERS_ENABLED) {

    }

    vkDestroySurfaceKHR(this -> instance, this -> surface, nullptr);
    vkDestroyInstance(this -> instance, nullptr);

    glfwDestroyWindow(this -> window);
    glfwTerminate();
}


#pragma endregion Engine }