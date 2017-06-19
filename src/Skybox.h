//
// Created by Jeremy Brown on 2017-06-18.
//

#ifndef COMP371_PROJECT_SKYBOX_H
#define COMP371_PROJECT_SKYBOX_H

#include <vector>

#include <glm/vec3.hpp>

#include "shader.hpp"

class Skybox
{
public:
    Skybox(const std::string &path);

    void draw(float viewport_height, float viewport_width, Shader &shader);

    void reset();

private:
    GLuint loadCubemap(std::vector<const GLchar*> faces);

    const std::string path;

    GLuint skyboxVAO, skyboxVerticesVBO;
    std::vector<glm::vec3> skybox_vertices;
    std::vector<glm::vec3> skybox_normals;  // unused
    std::vector<glm::vec2> skybox_UVs;  // unused

};


#endif //COMP371_PROJECT_SKYBOX_H
