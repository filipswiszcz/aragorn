#include <aragorn/util/cmd_family_finder.hpp>

#pragma mark - Cmd_Family_Finder
#pragma region Cmd_Family_Finder {

// using namespace util;

std::vector<VkQueueFamilyProperties> util::get_all_queue_families(const VkPhysicalDevice device) {

    uint32_t families_k = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &families_k, nullptr);

    std::vector<VkQueueFamilyProperties> families(families_k);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &families_k, families.data());
    
    return families;
}

#pragma endregion Cmd_Family_Finder }