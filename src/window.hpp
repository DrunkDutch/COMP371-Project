//
// Created by Jeremy Brown on 2017-05-20.
//

#ifndef COMP371_PROJECT_WINDOW_H
#define COMP371_PROJECT_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "world.hpp"

class Window
{
public:
    Window(const char* window_title, int window_width, int window_height) : window_title(window_title),
                                                                            window_width(window_width),
                                                                            window_height(window_height)
    {
        initialize();
    }

    ~Window()
    {
        if (world != nullptr) {
            delete world;
        }

        glfwTerminate();  // deallocates glfw_window
    }

    int initialize()
    {
        if (!glfwInit()) {
            std::cerr << "ERROR: Could not start GLFW3" << std::endl;
            return 1;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfw_window = glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);
        if (!glfw_window) {
            std::cerr << "ERROR: Could not open window with GLFW3" << std::endl;
            glfwTerminate();
            return 1;
        }

        glfwMakeContextCurrent(glfw_window);

        // capture cursor
        glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Initialize GLEW extension handler
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cerr << "ERROR: Could not initialize GLEW" << std::endl;
            return 1;
        }

        int width, height;
        glfwGetFramebufferSize(glfw_window, &width, &height);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        world = new World(width, height);
        set_viewport_size(width, height);
        return world->initialize();
    }

    void show_blocking()
    {
        // Doing the actual drawing
        while (!glfwWindowShouldClose(glfw_window)) {
            // Set time frame
            GLfloat current_frame = glfwGetTime();
            GLfloat delta_time = current_frame - last_frame;
            last_frame = current_frame;

            // update input handling
            glfwPollEvents();

            do_camera_movement(delta_time);

            // draw world
            world->draw(delta_time, polygon_mode);

            // swap gl buffers to the display
            glfwSwapBuffers(glfw_window);
        }
    }

    GLFWwindow* get_glfw_window()
    {
        return glfw_window;
    }

    void set_viewport_size(int width, int height)
    {
        glViewport(0, 0, width, height);
        window_width = width;
        window_height = height;
        world->set_viewport_size(width, height);
    }

    void handle_mouse(int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(glfw_window, &xpos, &ypos);
            xpos = xpos - window_width / 2;
            ypos = window_height / 2 - ypos;

            std::cout << "Mouse clicked at " << xpos << ", " << ypos << std::endl;
        }
    }

    void handle_cursor(int xpos, int ypos)
    {
        if (first_mouse) {
            last_x = xpos;
            last_y = ypos;
            first_mouse = false;
        }

        GLfloat xoffset = xpos - last_x;
        GLfloat yoffset = last_y - ypos;  // Reversed since y-coordinates go from bottom to left

        last_x = xpos;
        last_y = ypos;

        world->get_camera()->ProcessMouseMovement(xoffset, yoffset);
    }

    void handle_key(int key, int scancode, int action, int mode)
    {
        // close window
//        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//            glfwSetWindowShouldClose(glfw_window, GL_TRUE);
//        }

        // world or axis rotation
        if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
            world->toggle_lighting(1);
        } else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
            world->toggle_lighting(2);
        } else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
            world->toggle_lighting(3);
        } else if (key == GLFW_KEY_T && action == GLFW_PRESS){
            world->toggle_shader();
        }


        // handle pressed keys over time
        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS) {
                keys[key] = true;
            } else if (action == GLFW_RELEASE) {
                keys[key] = false;
            }
        }
    }

    void do_camera_movement(float delta_time)
    {
        if (keys[GLFW_KEY_W]) {
            world->get_camera()->ProcessKeyboard(FORWARD, delta_time);
        } if (keys[GLFW_KEY_S]) {
            world->get_camera()->ProcessKeyboard(BACKWARD, delta_time);
        } if (keys[GLFW_KEY_A]) {
            world->get_camera()->ProcessKeyboard(LEFT, delta_time);
        } if (keys[GLFW_KEY_D]) {
            world->get_camera()->ProcessKeyboard(RIGHT, delta_time);
        }
    }

private:
    GLFWwindow* glfw_window = nullptr;
    const char* window_title;
    int window_height;
    int window_width;
    World* world = nullptr;
    bool keys[1024];
    GLfloat last_frame = 0.0f;
    GLenum polygon_mode = GL_TRIANGLES;

    // Mouse
    GLfloat last_x = 400, last_y = 300;
    bool first_mouse = true;
};


#endif  // COMP371_PROJECT_WINDOW_H
