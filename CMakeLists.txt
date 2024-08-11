cmake_minimum_required(VERSION 3.20)

project(aragorn VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find libraries
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
    find_package(Vulkan)
    find_package(glfw3)
    find_package(glm)
endif ()

if (NOT VULKAN_FOUND)
    message(FATAL_ERROR "Could not find vulkan library.")
else ()
    message(STATUS ${Vulkan_LIBRARY})
endif ()

# collect all executables
set(ARAGORN_CORE
    # src/core/
)
set(ARAGORN_UTIL
    src/util/logger.cpp
)
set(SOURCES
    ${ARAGORN_CORE}
    ${ARAGORN_UTIL}
    
    src/main.cpp
)
set(HEADERS
    include/aragorn/util/logger.hpp
)

add_executable(aragorn ${SOURCES} ${HEADERS})
target_link_libraries(aragorn PRIVATE
    Vulkan::Vulkan
    glfw
    glm::glm
)