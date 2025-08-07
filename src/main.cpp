#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

    // Initialisation de GLAD2
    if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "Erreur : échec du chargement de GLAD" << std::endl;
    return -1;
    }

    // Viewport et callback resize
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Nettoyage
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
