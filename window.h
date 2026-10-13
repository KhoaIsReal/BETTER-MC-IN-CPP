//
// Created by Khoa on 10/13/2026.
//

#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * @brief A wrapper class for creating and managing an OpenGL window using GLFW.
 *
 * Initializes GLFW, configures an OpenGL 3.3 Core Profile context,
 * creates a window, initializes GLAD, and registers a framebuffer resize callback.
 *
 * The class also provides a main loop that executes a user-defined function
 * every frame, swaps the window buffers, and processes GLFW events.
 *
 * @note GLFW and GLAD must be properly installed and linked before use.
 * @note The OpenGL context is made current on the calling thread.
 */
class Window {
private:
    /* @brief Pointer to the GLFW window managed by this instance. */
    GLFWwindow* window;

public:
    /**
    * @brief Creates and initializes an OpenGL window.
    *
    * Initializes GLFW, requests an OpenGL 3.3 Core Profile context,
    * creates the window, makes its context current, initializes GLAD,
    * and registers the framebuffer resize callback.
    *
    * @param width  Initial window width in pixels.
    * @param height Initial window height in pixels.
    * @param title  Window title displayed in the title bar.
    *
    * @throws std::runtime_error If GLFW cannot create the window or
    *         GLAD fails to initialize.
    */
    Window(int width, int height, const char* title) {
        // Init work
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Must have this hint in MacOS
#if defined(__APPLE__) && defined(__MACH__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(width, height, title, NULL, NULL);

        if (window == NULL)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window\n");
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD\n");
        }

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    /**
     * @brief Runs the main window loop.
     *
     * Repeatedly executes the supplied callback, swaps the front and back
     * buffers, and processes pending GLFW events until the window is closed.
     *
     * @param run_func Optional pointer to a function executed once per frame.
     *        If nullptr, the callback is skipped.
     *
     * @note The callback takes no arguments and returns no value.
     * @note Calls glfwTerminate() when the loop ends.
     */
    void run(void (*run_func)()) {
        while(!glfwWindowShouldClose(window))
        {
            if (run_func != nullptr) {
                run_func();
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
};

#endif //UNTITLED_WINDOW_H
