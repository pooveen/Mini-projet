#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Mesh.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"


// Callback pour resize de fenêtre
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialisation de GLFW
    if (!glfwInit()) {
        std::cerr << "Erreur : GLFW init a échoué" << std::endl;
        return -1;
    }

    // Contexte OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Nécessaire sur macOS
#endif

    // Création de la fenêtre
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mini3DViewer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur : création de la fenêtre GLFW échouée" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialisation de GLAD2
    if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "Erreur : échec du chargement de GLAD" << std::endl;
    return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // // Viewport et callback resize
    // glViewport(0, 0, 800, 600);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Mesh mesh("../models/cube.obj");
    Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    Renderer renderer(mesh, shader);

    // Boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        // Input
        glfwPollEvents();

        // Clear
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = static_cast<float>(glfwGetTime());
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::lookAt(glm::vec3(2,2,2), glm::vec3(0,0,0), glm::vec3(0,1,0));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f/600.f, 0.1f, 100.0f);

        shader.use();
        shader.setUniform("model", model);
        shader.setUniform("view", view);
        shader.setUniform("projection", projection);

        // Rendu
        renderer.draw();

        // Swap buffers
        glfwSwapBuffers(window);
    }


    // Nettoyage
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
