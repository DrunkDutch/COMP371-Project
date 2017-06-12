//
// Created by Jeremy Brown on 2017-06-03.
//

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "plane.hpp"

Plane::Plane(glm::vec3 initial_location, GLfloat width, GLfloat length, Shader shader) :
        GeometricObject(shader, initial_location)
{
    GLfloat half_width = width / 2;
    GLfloat half_length = length / 2;
    vertices[0] = -half_width;
    vertices[1] = 0.0f;
    vertices[2] = -half_length;
    vertices[3] = 0.0f;
    vertices[4] = 1.0f;
    vertices[5] = 0.0f;

    vertices[6] = half_width;
    vertices[7] = 0.0f;
    vertices[8] = -half_length;
    vertices[9] = 0.0f;
    vertices[10] = 1.0f;
    vertices[11] = 0.0f;

    vertices[12] = -half_width;
    vertices[13] = 0.0f;
    vertices[14] = half_length;
    vertices[15] = 0.0f;
    vertices[16] = 1.0f;
    vertices[17] = 0.0f;

    vertices[18] = half_width;
    vertices[19] = 0.0f;
    vertices[20] = -half_length;
    vertices[21] = 0.0f;
    vertices[22] = 1.0f;
    vertices[23] = 0.0f;

    vertices[24] = -half_width;
    vertices[25] = 0.0f;
    vertices[26] = half_length;
    vertices[27] = 0.0f;
    vertices[28] = 1.0f;
    vertices[29] = 0.0f;

    vertices[30] = half_width;
    vertices[31] = 0.0f;
    vertices[32] = half_length;
    vertices[33] = 0.0f;
    vertices[34] = 1.0f;
    vertices[35] = 0.0f;

    reset();
}

void Plane::draw(glm::mat4 &view, glm::mat4 &projection)
{
    shader.use();
    glBindVertexArray(vao);

    glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shader.program, "objectColor"), frag_color.r, frag_color.g, frag_color.b);

    // draw line
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(transform_matrix));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Plane::reset()
{
    // reset line points in gl buffers
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // reset transformation vectors
    scale_vec = initial_scale;
    rotations = std::vector<glm::quat>();
    translate_vec = initial_translation;
}