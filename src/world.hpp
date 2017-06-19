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
#include "objloader.hpp"
#include "lamp.h"
#include "Skybox.h"


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
        load_shaders();
        active_shader = col_lighting_shader;

        // initialize colors
        dark_green_color = glm::vec4(0.2f, 0.4f, 0.0f, 1.0f);
        white_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        // create camera
        camera = new Camera(glm::vec3(10.0f, 20.0f, 0.0f));

        // create ground
        ground = new Plane(glm::vec3(0.0f, 0.0f, 0.0f), 800, 800, *active_shader);
        ground->set_color(dark_green_color);

        // create lamps
        lamp1 = new Lamp(glm::vec3(22.0f, 15.0f, -185.0f), *no_shade_shader);
        lamp1->set_color(white_color);
        lamp1->set_enabled(true);
        lamp2 = new Lamp(glm::vec3(88.0f, 15.0f, -108.0f), *no_shade_shader);
        lamp2->set_color(white_color);
        lamp2->set_enabled(true);
        lamp3 = new Lamp(glm::vec3(53.0f, 15.0f, -72.0f), *no_shade_shader);
        lamp3->set_color(white_color);
        lamp3->set_enabled(true);

        active_shader->use();
        active_shader->set_int("material.diffuse", 0);
        active_shader->set_int("material.specular", 1);

        // create models
        std::cout << "Loading models..." << std::endl;
        walls = new Model("../../models/Project/walls/walls.obj");
        floor = new Model("../../models/Project/floor/floor.obj");
        chair1 = new Model("../../models/Project/chair1/chair1.obj");
        roof = new Model("../../models/Project/roof/roof.obj");
        chair1b = new Model("../../models/Project/chair1b/chair1b.obj");
        chair2 = new Model("../../models/Project/chair2/chair2.obj");
        chair2b = new Model("../../models/Project/chair2b/chair2b.obj");
        chair3 = new Model("../../models/Project/chair3/chair3.obj");
        chair3b = new Model("../../models/Project/chair3b/chair3b.obj");
        couch1 = new Model("../../models/Project/couch1/couch1.obj");
        couch2 = new Model("../../models/Project/couch2/couch2.obj");
        couch3 = new Model("../../models/Project/couch3/couch3.obj");
        shelf1 = new Model("../../models/Project/shelf1/shelf1.obj");
        shelf2 = new Model("../../models/Project/shelf2/shelf2.obj");
        shelf3 = new Model("../../models/Project/shelf3/shelf3.obj");
        table1 = new Model("../../models/Project/table1/table1.obj");
        table2 = new Model("../../models/Project/table2/table2.obj");
        table3 = new Model("../../models/Project/table3/table3.obj");

        std::cout << "Models loaded!" << std::endl;

        skybox = new Skybox("../../models/skybox/cube.obj");

        return 0;
    }

    void load_shaders()
    {
        // Shaders
        no_shade_shader = new Shader("../../shaders/no_shade.vert", "../../shaders/no_shade.frag");
        col_lighting_shader = new Shader("../../shaders/col_lighting.vert", "../../shaders/col_lighting.frag");
        texture_shader = new Shader("../../shaders/transformations.vert", "../../shaders/transformations.frag");
        col_lighting_shader_v2 = new Shader("../../shaders/col_lighting.vert", "../../shaders/col_lighting_v2.frag");
        skyboxShaderProgram = new Shader("../../shaders/skybox_vertex.shader", "../../shaders/skybox_fragment.shader");

    }

    void draw(GLfloat delta_time, GLenum polygon_mode)
    {
        // clear drawing surface
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);

        active_shader->use();
        active_shader->set_int("material.diffuse", 0);
        active_shader->set_int("material.specular", 1);
        ground = new Plane(glm::vec3(0.0f, 0.0f, 0.0f), 800, 800, *active_shader);


        // camera view
        glm::mat4 view = camera->GetViewMatrix();
        // camera projection
        glm::mat4 projection = glm::perspective(camera->Zoom, (float) viewport_width / viewport_height, 0.1f,
                                                1000.0f);

        // draw ground
        if (ground != nullptr) {
            ground->draw(view, projection);
        }

        // draw skybox
        skybox->draw(viewport_width, viewport_height, *skyboxShaderProgram);

        // set light levels & draw lamps
        do_lighting(view, projection, camera->Position);

        // draw objects
        active_shader->use();

        walls->Draw(*texture_shader);
        floor->Draw(*texture_shader);
        chair1->Draw(*texture_shader);
        roof->Draw(*texture_shader);
        chair1b->Draw(*texture_shader);
        chair2->Draw(*texture_shader);
        chair2b->Draw(*texture_shader);
        chair3->Draw(*texture_shader);
        chair3b->Draw(*texture_shader);
        couch1->Draw(*texture_shader);
        couch2->Draw(*texture_shader);
        couch3->Draw(*texture_shader);
        shelf1->Draw(*texture_shader);
        shelf2->Draw(*texture_shader);
        shelf3->Draw(*texture_shader);
        table1->Draw(*texture_shader);
        table2->Draw(*texture_shader);
        table3->Draw(*texture_shader);
        lamps->Draw(*texture_shader);

    }

    void toggle_lighting(int room_number)
    {
        switch (room_number) {
            case 1:
                lamp1->toggle();
                return;
            case 2:
                lamp2->toggle();
                return;
            case 3:
                lamp3->toggle();
                return;
            default:
            std::cout << "Room with specified number " << room_number << " does not exist." << std::endl;
                return;
        }
    }

    void toggle_shader() {
        if (shader_toggle == 0) {
            active_shader = col_lighting_shader_v2;
            shader_toggle = 1;
        } else {
            active_shader = col_lighting_shader;
            shader_toggle = 0;
        }
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

    void do_lighting(glm::mat4 view, glm::mat4 projection, glm::vec3 camera_pos)
    {
        lamp1->draw(view, projection);
        lamp2->draw(view, projection);
        lamp3->draw(view, projection);

        active_shader->use();
        active_shader->set_vec3("viewPos", camera_pos);

        // light positions
        active_shader->set_vec3("light1.position", lamp1->get_position());
        active_shader->set_vec3("light2.position", lamp2->get_position());
        active_shader->set_vec3("light3.position", lamp3->get_position());

        // light properties
        glm::vec3 ambient_vec = glm::vec3(0.2f, 0.2f, 0.2f);
        glm::vec3 diffuse_vec = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 specular_vec = glm::vec3(1.0f, 1.0f, 1.0f);

        active_shader->set_vec3("light1.ambient", ambient_vec);
        active_shader->set_vec3("light1.diffuse", diffuse_vec);
        active_shader->set_vec3("light1.specular", specular_vec);
        active_shader->set_bool("light1.enabled", lamp1->is_enabled());
        active_shader->set_vec3("light2.ambient", ambient_vec);
        active_shader->set_vec3("light2.diffuse", diffuse_vec);
        active_shader->set_vec3("light2.specular", specular_vec);
        active_shader->set_bool("light2.enabled", lamp2->is_enabled());
        active_shader->set_vec3("light3.ambient", ambient_vec);
        active_shader->set_vec3("light3.diffuse", diffuse_vec);
        active_shader->set_vec3("light3.specular", specular_vec);
        active_shader->set_bool("light3.enabled", lamp3->is_enabled());

        // material properties
        active_shader->set_float("material.shininess", 64.0f);
    }

    void reset()
    {
        // TODO ?
    }



private:
    Camera* camera = nullptr;

    glm::vec4 dark_green_color;
    glm::vec4 white_color;

    int viewport_height;
    int viewport_width;

    Shader* col_lighting_shader = nullptr;
    Shader* col_lighting_shader_v2 = nullptr;
    Shader* no_shade_shader = nullptr;
    Shader* texture_shader = nullptr;
    Shader* skyboxShaderProgram = nullptr;
    Shader* active_shader = nullptr;
    Plane* ground = nullptr;
    Lamp* lamp1 = nullptr;
    Lamp* lamp2 = nullptr;
    Lamp* lamp3 = nullptr;

    Model* walls = nullptr;
    Model* floor = nullptr;
    Model* chair1 = nullptr;
    Model* roof = nullptr;
    Model* chair1b = nullptr;
    Model* chair2 = nullptr;
    Model* chair2b = nullptr;
    Model* chair3 = nullptr;
    Model* chair3b = nullptr;
    Model* couch1 = nullptr;
    Model* couch2 = nullptr;
    Model* couch3 = nullptr;
    Model* shelf1 = nullptr;
    Model* shelf2 = nullptr;
    Model* shelf3 = nullptr;
    Model* table1 = nullptr;
    Model* table2 = nullptr;
    Model* table3 = nullptr;
    Model* lamps = nullptr;

    Skybox* skybox = nullptr;

    int shader_toggle = 0;

};


#endif  // COMP371_PROJECT_WORLD_H
