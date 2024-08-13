cmake_minimum_required(VERSION 3.20)

project(aragorn VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find libraries
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
    find_package(Vulkan REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)
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
    
    src/app.cpp
    src/main.cpp
)

add_executable(aragorn ${SOURCES})

# collect all headers
target_include_directories(aragorn PUBLIC include)
target_link_libraries(aragorn PRIVATE
    Vulkan::Vulkan
    glfw
    glm::glm
)