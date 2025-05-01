#include "iostream"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "vertex_array.h"
#include "shader.h"

bool initializeGLFW();
bool initializeGLAD();
GLFWwindow* creatwWindowAndMakeContext(int width, int height, const char* title);
void viewportCallback(GLFWwindow* window, int width, int height);
void mainLoop(GLFWwindow* window, VertexArray& vao, Shader& shader);
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

    // Vertices
    float vertices[] = {
        -.5f, -.5f, 0.f, 1.f, 0.f, 0.f,
         .0f,  .5f, 0.f, 0.f, 1.f, 0.f,
         .5f, -.5f, 0.f, 0.f, 0.f, 1.f,
    };

    VertexArray vao;
    unsigned int vbo;
    vao.createVertexBuffer(sizeof(vertices), vertices, GL_STATIC_DRAW);
    vao.enableVertixAttrib(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    vao.enableVertixAttrib(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Shader
    Shader shader("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");

    // Main Loop
    mainLoop(window, vao, shader);

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

void mainLoop(GLFWwindow* window, VertexArray& vao, Shader& shader) {
    while(!glfwWindowShouldClose(window)) {

        // Inputs
        keyboardInputs(window);

        // Clear
        glClear(GL_COLOR_BUFFER_BIT);

        // Update
        vao.use();
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

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