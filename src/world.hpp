//
// Created by Jeremy Brown on 2017-05-20.
//

#ifndef COMP371_PROJECT_WORLD_H
#define COMP371_PROJECT_WORLD_H

#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/spline.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "cube.hpp"
#include "camera.hpp"
#include "track.hpp"
#include "plane.hpp"
#include "model.hpp"


class World
{
public:

    World(int viewport_height, int viewport_width) : viewport_height(viewport_height), viewport_width(viewport_width) {}

    ~World()
    {
        if (camera != nullptr) {
            delete camera;
        }
        if (col_lighting_shader != nullptr) {
            delete col_lighting_shader;
        }
        if (ground != nullptr) {
            delete ground;
        }
        if (lamp1 != nullptr) {
            delete lamp1;
        }
        if (lamp2 != nullptr) {
            delete lamp2;
        }
    }

    int initialize()
    {
        // Shaders
        no_shade_shader = new Shader("../../shaders/plain.vert", "../../shaders/no_shade.frag");
        col_lighting_shader = new Shader("../../shaders/col_lighting.vert", "../../shaders/col_lighting.frag");

        // initialize colors
        dark_green_color = glm::vec4(0.2f, 0.4f, 0.0f, 1.0f);
        black_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        white_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        brown_color = glm::vec4(0.4f, 0.2f, 0.0f, 1.0f);  // 102r 51g 0b
        red_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        blue_color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        // initialize shader defaults
        ambient_light_level = 0.2f;
        ambient_light_color = glm::vec3(white_color);
        lamp_light_color = glm::vec3(white_color);
        lamp1_light_strength = 0.3f;
        lamp2_light_strength = 1.0f;
        cam_light_color = glm::vec3(white_color);
        cam_light_strength = 0.5f;
        specular_strength = 0.5f;
        shininess = 32;

        // create camera
        camera = new Camera(glm::vec3(2.0f, 2.0f, 100.0f));

        // create ground
        ground = new Plane(glm::vec3(0.0f, 0.0f, 0.0f), 800, 800, *col_lighting_shader);
        ground->set_color(dark_green_color);

        // create lamps
        lamp1 = new Cube(glm::vec3(300.0f, 15.0f, 0.0f), *no_shade_shader);
        lamp1->set_color(white_color);
        lamp2 = new Cube(glm::vec3(-300.0f, 50.0f, 0.0f), *no_shade_shader);
        lamp2->set_color(white_color);

        // create teapot
        walls = new Model("../../models/Project/walls/walls.obj");
        floor = new Model("../../models/Project/floor/floor.obj");
        chair1 = new Model("../../models/Project/chair1/chair1.obj");

        enable_lighting();

        return 0;
    }

    void draw(GLfloat delta_time, GLenum polygon_mode)
    {
        // clear drawing surface
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);

        // camera view
        glm::mat4 view = camera->GetViewMatrix();
        // camera projection
        glm::mat4 projection = glm::perspective(camera->Zoom, (float) viewport_width / viewport_height, 0.1f,
                                                1000.0f);

        // set light levels & draw lamps
        do_lighting(view, projection, camera->Position, ambient_light_level);

        // draw ground
        if (ground != nullptr) {
            ground->draw(view, projection);
        }

        // todo draw stuff
        walls->Draw(*no_shade_shader);
        floor->Draw(*no_shade_shader);
        chair1->Draw(*no_shade_shader);
    }

    void toggle_lighting()
    {
        std::cout << "Toggling lights: ";
        lights_on = !lights_on;

        if (lights_on) {
            enable_lighting();
        } else {
            disable_lighting();
        }
    }

    void enable_lighting()
    {
        // set light color to white
        lamp_light_color = glm::vec3(white_color);
        cam_light_color = glm::vec3(white_color);
        lamp1->set_color(white_color);
        lamp2->set_color(white_color);
        std::cout << "ON!" << std::endl;
    }

    void disable_lighting()
    {
        // set light color to black
        lamp_light_color = glm::vec3(black_color);
        cam_light_color = glm::vec3(black_color);
        lamp1->set_color(black_color);
        lamp2->set_color(black_color);
        std::cout << "OFF!" << std::endl;
    }

    Camera* get_camera()
    {
        return camera;
    }

    void set_viewport_size(int width, int height)
    {
        viewport_width = width;
        viewport_height = height;
    }

    void do_lighting(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_pos, float ambient_light_level)
    {
        lamp1->draw(view, projection);
        lamp2->draw(view, projection);

        col_lighting_shader->use();
        GLint view_pos_uloc = glGetUniformLocation(col_lighting_shader->program, "viewPos");
        glUniform3f(view_pos_uloc, camera_pos.x, camera_pos.y, camera_pos.z);

        GLint ambient_strength_uloc = glGetUniformLocation(col_lighting_shader->program, "ambientStrength");
        glUniform1f(ambient_strength_uloc, ambient_light_level);
        GLint ambient_light_color_uloc = glGetUniformLocation(col_lighting_shader->program, "ambientLightColor");
        glUniform3f(ambient_light_color_uloc, ambient_light_color.r, ambient_light_color.g, ambient_light_color.b);
        GLint lamp_light_color_uloc = glGetUniformLocation(col_lighting_shader->program, "lampLightColor");
        glUniform3f(lamp_light_color_uloc, lamp_light_color.r, lamp_light_color.g, lamp_light_color.b);
        GLint cam_light_color_uloc = glGetUniformLocation(col_lighting_shader->program, "cameraLightColor");
        glUniform3f(cam_light_color_uloc, cam_light_color.r, cam_light_color.g, cam_light_color.b);

        GLint lamp1_light_strength_uloc = glGetUniformLocation(col_lighting_shader->program, "lamp1LightStrength");
        glUniform1f(lamp1_light_strength_uloc, lamp1_light_strength);
        GLint lamp2_light_strength_uloc = glGetUniformLocation(col_lighting_shader->program, "lamp2LightStrength");
        glUniform1f(lamp2_light_strength_uloc, lamp2_light_strength);
        GLint cam_light_strength_uloc = glGetUniformLocation(col_lighting_shader->program, "cameraLightStrength");
        glUniform1f(cam_light_strength_uloc, cam_light_strength);

        GLint lamp1_pos_uloc = glGetUniformLocation(col_lighting_shader->program, "lamp1Pos");
        glm::vec3 lamp1_pos = lamp1->get_position();
        glUniform3f(lamp1_pos_uloc, lamp1_pos.x, lamp1_pos.y, lamp1_pos.z);
        GLint lamp2_pos_uloc = glGetUniformLocation(col_lighting_shader->program, "lamp2Pos");
        glm::vec3 lamp2_pos = lamp2->get_position();
        glUniform3f(lamp2_pos_uloc, lamp2_pos.x, lamp2_pos.y, lamp2_pos.z);

        GLint specular_strength_uloc = glGetUniformLocation(col_lighting_shader->program, "specularStrength");
        glUniform1f(specular_strength_uloc, specular_strength);
        GLint shininess_uloc = glGetUniformLocation(col_lighting_shader->program, "shininess");
        glUniform1i(shininess_uloc, shininess);
    }

    void reset()
    {
        // TODO ?
    }

private:
    Camera* camera = nullptr;
    bool lights_on = true;

    glm::vec4 dark_green_color;
    glm::vec4 black_color;
    glm::vec4 white_color;
    glm::vec4 brown_color;
    glm::vec4 red_color;
    glm::vec4 blue_color;

    GLfloat ambient_light_level;
    glm::vec3 ambient_light_color;
    glm::vec3 lamp_light_color;
    GLfloat lamp1_light_strength;
    GLfloat lamp2_light_strength;
    glm::vec3 cam_light_color;
    GLfloat cam_light_strength;
    GLfloat specular_strength;
    GLint shininess;

    int viewport_height;
    int viewport_width;

    Shader* col_lighting_shader = nullptr;
    Shader* no_shade_shader = nullptr;
    Plane* ground = nullptr;
    Cube* lamp1 = nullptr;
    Cube* lamp2 = nullptr;

    Model* walls = nullptr;
    Model* floor = nullptr;
    Model* chair1 = nullptr;

};


#endif  // COMP371_PROJECT_WORLD_H
