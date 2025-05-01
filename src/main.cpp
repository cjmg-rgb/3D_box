#include "iostream"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

bool initializeGLFW();
bool initializeGLAD();
GLFWwindow* creatwWindowAndMakeContext(int width, int height, const char* title);
void viewportCallback(GLFWwindow* window, int width, int height);
void mainLoop(GLFWwindow* window);
void keyboardInputs(GLFWwindow* window);

int main() {

    // Initialize GLFW
    if(!initializeGLFW()) return -1;

    // Create Window
    GLFWwindow* window = creatwWindowAndMakeContext(800, 600, "Window");
    if(window == nullptr) return -1;
    
    // Initialize GLAD
    if(!initializeGLAD()) return -1;

    // Viewport
    glfwSetFramebufferSizeCallback(window, viewportCallback);

    // Main Loop
    mainLoop(window);

    // End
    glfwTerminate();

    return 0;
}

bool initializeGLFW() {
    if(!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return false;
    }
    return true;
};

bool initializeGLAD() {
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return false;
    }
    return true;
};

GLFWwindow* creatwWindowAndMakeContext(int width, int height, const char* title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create window\n";
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);
    return window;
};

void viewportCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
};

void mainLoop(GLFWwindow* window) {
    while(!glfwWindowShouldClose(window)) {

        // Inputs
        keyboardInputs(window);

        // Clear
        glClear(GL_COLOR_BUFFER_BIT);

        // Update

        // Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void keyboardInputs(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}