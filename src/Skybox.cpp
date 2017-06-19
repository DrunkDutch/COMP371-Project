//
// Created by Jeremy Brown on 2017-06-18.
//


#include <string>

#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Skybox.h"
#include "objloader.hpp"

Skybox::Skybox(const std::string &path) : path(path)
{
    reset();
}

void Skybox::draw(float viewport_height, float viewport_width, Shader &shader)
{
    glm::mat4 view_matrix;

    GLint projectionLoc = glGetUniformLocation(shader.program, "projection_matrix");
    GLint viewMatrixLoc = glGetUniformLocation(shader.program, "view_matrix");
    GLint transformLoc = glGetUniformLocation(shader.program, "model_matrix");
    glm::mat4 projection_matrix = glm::perspective(45.0f, (GLfloat) viewport_height / (GLfloat) viewport_height, 0.1f, 100.0f);

    // draw skybox
    shader.use();
    glm::mat4 skybox_view = glm::mat4(glm::mat3(view_matrix)); //remove the translation data
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(skybox_view));

    glUniformMatrix4fv(glGetUniformLocation(shader.program, "view_matrix"), 1, GL_FALSE, glm::value_ptr(skybox_view));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix));

    glUniform1i(glGetUniformLocation(shader.program, "skyboxTexture"), 1);  // use texture unit 1

    glDepthMask(GL_FALSE);
    glBindVertexArray(skyboxVAO);
    glDrawArrays(GL_TRIANGLES, 0, skybox_vertices.size());
    glBindVertexArray(0);

    glDepthMask(GL_TRUE);
}

void Skybox::reset()
{
    loadOBJ(path.c_str(), skybox_vertices, skybox_normals, skybox_UVs);

    //prepare skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glBindVertexArray(skyboxVAO);

    glGenBuffers(1, &skyboxVerticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVerticesVBO);
    glBufferData(GL_ARRAY_BUFFER, skybox_vertices.size() * sizeof(glm::vec3), &skybox_vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    glBindVertexArray(0);

    std::vector<const GLchar*> faces;
    faces.push_back("../../models/skybox/right.jpg");
    faces.push_back("../../models/skybox/left.jpg");
    faces.push_back("../../models/skybox/top.jpg");
    faces.push_back("../../models/skybox/bottom.jpg");
    faces.push_back("../../models/skybox/back.jpg");
    faces.push_back("../../models/skybox/front.jpg");

    glActiveTexture(GL_TEXTURE1);
    GLuint cubemapTexture = loadCubemap(faces);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
}

GLuint Skybox::loadCubemap(std::vector<const GLchar*> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height;
    unsigned char* image;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (GLuint i = 0; i < faces.size(); i++)
    {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
        );

        SOIL_free_image_data(image);  // free resources
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}