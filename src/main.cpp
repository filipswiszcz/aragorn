#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include <aragorn/util/logger.hpp>

int main() {
    
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(800, 600, "aragorn", NULL, NULL);
    if (!window) {
        glfwTerminate(); return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        // glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
