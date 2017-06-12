//
// Created by Jeremy Brown on 2017-05-22.
//

#ifndef COMP371_PROJECT_INPUT_H
#define COMP371_PROJECT_INPUT_H

#include <GLFW/glfw3.h>
#include "window.hpp"

namespace input
{
    Window* active_window = nullptr;

    // called when a key is pressed/released
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        active_window->handle_key(key, scancode, action, mode);
    }

    void window_size_callback(GLFWwindow* window, int width, int height)
    {
        active_window->set_viewport_size(width, height);
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        active_window->handle_mouse(button, action, mods);
    }

    void cursor_callback(GLFWwindow* window, double xpos, double ypos)
    {
        active_window->handle_cursor(xpos, ypos);
    }

    void set_active_window(Window* window)
    {
        active_window = window;
        glfwSetKeyCallback(window->get_glfw_window(), key_callback);
        glfwSetWindowSizeCallback(window->get_glfw_window(), window_size_callback);
        glfwSetMouseButtonCallback(window->get_glfw_window(), mouse_button_callback);
        glfwSetCursorPosCallback(window->get_glfw_window(), cursor_callback);
    }
}


#endif  // COMP371_PROJECT_INPUT_H
