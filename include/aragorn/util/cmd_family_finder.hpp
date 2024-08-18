#include <vulkan/vulkan.h>

#include <optional>
#include <vector>

#ifndef CMD_FAMILY_FINDER_H
#define CMD_FAMILY_FINDER_H

namespace util {

    struct QueueFamilyFinder {

        std::optional<uint32_t> families;

    };

    std::vector<VkQueueFamilyProperties> get_all_queue_families(const VkPhysicalDevice device);

} // namespace util

#endif