#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/GLFW3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>

static unsigned int g_scrWidth = 800;
static unsigned int g_scrHeight = 600;
const char* WINDOW_TITLE = "OpenGL Window";

// This callback function executes whenever the user moves the mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Camera* camera = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        camera->processMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
    }
}

// This callback function executes whenever the user moves the mouse scroll wheel
void scroll_callback(GLFWwindow* window, double /* offsetX */, double offsetY) {
    Camera* camera = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        camera->processMouseScroll(static_cast<float>(offsetY));
    }
}

// Called every frame inside the render loop
static void processInput(GLFWwindow* window, Camera* camera, float deltaTime) {
    // if the escape key is pressed, tell the window to close
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    // WASD for the camera
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->processKeyboard(Camera::FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->processKeyboard(Camera::BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->processKeyboard(Camera::LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->processKeyboard(Camera::RIGHT, deltaTime);
    }
}

int main() {
    // initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create the main window
    GLFWwindow* window = glfwCreateWindow(g_scrWidth, g_scrHeight, WINDOW_TITLE, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
    std::cout << "Starting Application...\n";

    // Set the camera object as the window's user pointer. This makes it accessible 
    // in callback functions by using glfwGetWindowUserPointer().
    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(&camera));

    // vertex buffer data
    const float vData[] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
    };

    // index buffer data
    const unsigned int iData[] = {
        0u, 1u, 3u,
        0u, 3u, 2u,
    };

    ShaderProgram shader("res/shaders/basic_vertex.glsl", "res/shaders/basic_fragment.glsl");
    Mesh mesh(vData, sizeof(vData), { 3 });
    mesh.addSubmesh(iData, sizeof(iData) / sizeof(unsigned int), &shader);

    // set the clear color (background color)
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    // variables for deltaTime
    double previousTime = glfwGetTime();
    double deltaTime = 0.0f;

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // calculate deltaTime and process input
        double currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;
        processInput(window, &camera, static_cast<float>(deltaTime));

        glClear(GL_COLOR_BUFFER_BIT);

        mesh.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}