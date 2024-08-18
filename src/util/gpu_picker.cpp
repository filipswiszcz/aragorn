#include <aragorn/util/gpu_picker.hpp>

#include <vector>

#pragma mark - GPU_Picker
#pragma region GPU_Picker {

VkPhysicalDevice util::get_most_suitable_gpu(const VkInstance instance) {

    uint32_t devices_k = 0;
    vkEnumeratePhysicalDevices(instance, &devices_k, nullptr);

    if (devices_k == 0) {
        // TODO warning
    }

    std::vector<VkPhysicalDevice> devices(devices_k);
    vkEnumeratePhysicalDevices(instance, &devices_k, devices.data());

    VkPhysicalDevice gpu = VK_NULL_HANDLE;
    for (const auto& device : devices) {

        VkPhysicalDeviceProperties props;
        VkPhysicalDeviceFeatures feats;

        vkGetPhysicalDeviceProperties(device, &props);
        vkGetPhysicalDeviceFeatures(device, &feats);

        if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && feats.geometryShader) {
            gpu = device; break;
        }
    } // TODO choose the best by score system motherfucker

    if (gpu == VK_NULL_HANDLE) {
        // TODO warning
    }

    return gpu;
}

#pragma endregion GPU_Picker }