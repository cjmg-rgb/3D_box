#include "iostream"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "vertex_array.h"
#include "shader.h"
#include "texture.h"

bool initializeGLFW();
bool initializeGLAD();
GLFWwindow* creatwWindowAndMakeContext(int width, int height, const char* title);
void viewportCallback(GLFWwindow* window, int width, int height);
void mainLoop(GLFWwindow* window, VertexArray& vao, Shader& shader, Texture* textures);
void keyboardInputs(GLFWwindow* window);


glm::mat4 model(1.f);
glm::mat4 view(1.f);
glm::mat4 projection;


glm::vec3 camPos(0.f, 0.f, 3.f);
glm::vec3 camFront(0.f, 0.f, -1.f);
glm::vec3 camUp(0.f, 1.f, 0.f);
float deltaTime = 0;
float lastFrame = 0;
float camSpeed = 2.5f;


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

    float vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,   1.f, 0.f, 0.f,   0.f, 0.f,  // bottom-left
        0.5f, -0.5f,  0.5f,   0.f, 1.f, 0.f,   1.f, 0.f,  // bottom-right
        0.5f,  0.5f,  0.5f,   0.f, 0.f, 1.f,   1.f, 1.f,  // top-right
        -0.5f,  0.5f,  0.5f,   1.f, 1.f, 0.f,   0.f, 1.f,  // top-left

        // Back face
        -0.5f, -0.5f, -0.5f,   1.f, 0.f, 1.f,   1.f, 0.f,  // bottom-left
        0.5f, -0.5f, -0.5f,   0.f, 1.f, 1.f,   0.f, 0.f,  // bottom-right
        0.5f,  0.5f, -0.5f,   1.f, 1.f, 1.f,   0.f, 1.f,  // top-right
        -0.5f,  0.5f, -0.5f,   0.f, 0.f, 0.f,   1.f, 1.f   // top-left
    };

    unsigned int indices[] = {
        // Front face
        0, 1, 2,
        0, 2, 3,

        // Right face
        1, 5, 6,
        1, 6, 2,

        // Back face
        5, 4, 7,
        5, 7, 6,

        // Left face
        4, 0, 3,
        4, 3, 7,

        // Top face
        3, 2, 6,
        3, 6, 7,

        // Bottom face
        4, 5, 1,
        4, 1, 0
    };


    VertexArray vao;
    unsigned int vbo;
    vao.createVertexBuffer(sizeof(vertices), vertices, GL_STATIC_DRAW);
    vao.createIndexBuffer(sizeof(indices), indices, GL_STATIC_DRAW);
    vao.enableVertixAttrib(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    vao.enableVertixAttrib(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.enableVertixAttrib(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    // Textures
    Texture container("assets/container.jpeg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_RGB);
    Texture tree("assets/tree.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_RGBA);
    Texture textures[] = {
        container,
        tree
    };

    // Shader
    model = glm::rotate(model, glm::radians(-45.f), glm::vec3(1.f, 1.f, 0.f));
    view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
    projection = glm::perspective(45.f, 800.f / 600.f, .1f, 100.f);

    Shader shader("shaders/vertex_shader.vert", "shaders/fragment_shader.frag");
    shader.use();
    shader.setInt("container", 0);
    shader.setInt("tree", 1);
    shader.setMat4fv("view", view);
    shader.setMat4fv("model", model);
    shader.setMat4fv("projection", projection);

    // Main Loop
    mainLoop(window, vao, shader, textures);

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
    glEnable(GL_DEPTH_TEST);
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

void mainLoop(GLFWwindow* window, VertexArray& vao, Shader& shader, Texture* textures) {
    while(!glfwWindowShouldClose(window)) {

        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime; 

        // Inputs
        keyboardInputs(window);

        // Clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update

        view = glm::lookAt(camPos, camPos + camFront, camUp);
        shader.setMat4fv("view", view);

        vao.use();
        shader.use();
        for(unsigned int i = 0; i < 2; i++) {
            textures[i].use();
        }
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
        // Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void keyboardInputs(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    };
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camPos += camFront * camSpeed * deltaTime;
    };
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camPos -= camFront * camSpeed * deltaTime;
    };
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camPos -= glm::normalize(glm::cross(camFront, camUp)) * deltaTime * camSpeed;
    };
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camPos += glm::normalize(glm::cross(camFront, camUp)) * deltaTime * camSpeed;
    };
}