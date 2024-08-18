#include <vulkan/vulkan.h>

#ifndef GPU_PICKER_H
#define GPU_PICKER_H

namespace util {

    VkPhysicalDevice get_most_suitable_gpu(const VkInstance instance);

} // namespace util

#endif