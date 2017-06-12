//
// Created by Jeremy Brown on 2017-06-02.
//

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "track.hpp"

Track::Track(glm::vec3 initial_location, Shader shader, glm::vec3 dimensions) : GeometricObject(shader, initial_location)
{
    GLfloat half_width = dimensions.x / 2;
    GLfloat half_height = dimensions.y / 2;
    GLfloat half_depth = dimensions.z / 2;

    // back (-z facing side)
    int prefix = 0;
    int side_size = 36;
    vertices[prefix * side_size + 0] = -half_width;
    vertices[prefix * side_size + 1] = -half_height;
    vertices[prefix * side_size + 2] = -half_depth;
    vertices[prefix * side_size + 3] = 0.0f;
    vertices[prefix * side_size + 4] = 0.0f;
    vertices[prefix * side_size + 5] = -1.0f;

    vertices[prefix * side_size + 6] = half_width;
    vertices[prefix * side_size + 7] = -half_height;
    vertices[prefix * side_size + 8] = -half_depth;
    vertices[prefix * side_size + 9] = 0.0f;
    vertices[prefix * side_size + 10] = 0.0f;
    vertices[prefix * side_size + 11] = -1.0f;

    vertices[prefix * side_size + 12] = -half_width;
    vertices[prefix * side_size + 13] = half_height;
    vertices[prefix * side_size + 14] = -half_depth;
    vertices[prefix * side_size + 15] = 0.0f;
    vertices[prefix * side_size + 16] = 0.0f;
    vertices[prefix * side_size + 17] = -1.0f;

    vertices[prefix * side_size + 18] = half_width;
    vertices[prefix * side_size + 19] = -half_height;
    vertices[prefix * side_size + 20] = -half_depth;
    vertices[prefix * side_size + 21] = 0.0f;
    vertices[prefix * side_size + 22] = 0.0f;
    vertices[prefix * side_size + 23] = -1.0f;

    vertices[prefix * side_size + 24] = -half_width;
    vertices[prefix * side_size + 25] = half_height;
    vertices[prefix * side_size + 26] = -half_depth;
    vertices[prefix * side_size + 27] = 0.0f;
    vertices[prefix * side_size + 28] = 0.0f;
    vertices[prefix * side_size + 29] = -1.0f;

    vertices[prefix * side_size + 30] = half_width;
    vertices[prefix * side_size + 31] = half_height;
    vertices[prefix * side_size + 32] = -half_depth;
    vertices[prefix * side_size + 33] = 0.0f;
    vertices[prefix * side_size + 34] = 0.0f;
    vertices[prefix * side_size + 35] = -1.0f;

    // front (+z facing side)
    prefix = 1;
    vertices[prefix * side_size + 0] = -half_width;
    vertices[prefix * side_size + 1] = -half_height;
    vertices[prefix * side_size + 2] = half_depth;
    vertices[prefix * side_size + 3] = 0.0f;
    vertices[prefix * side_size + 4] = 0.0f;
    vertices[prefix * side_size + 5] = 1.0f;

    vertices[prefix * side_size + 6] = half_width;
    vertices[prefix * side_size + 7] = -half_height;
    vertices[prefix * side_size + 8] = half_depth;
    vertices[prefix * side_size + 9] = 0.0f;
    vertices[prefix * side_size + 10] = 0.0f;
    vertices[prefix * side_size + 11] = 1.0f;

    vertices[prefix * side_size + 12] = -half_width;
    vertices[prefix * side_size + 13] = half_height;
    vertices[prefix * side_size + 14] = half_depth;
    vertices[prefix * side_size + 15] = 0.0f;
    vertices[prefix * side_size + 16] = 0.0f;
    vertices[prefix * side_size + 17] = 1.0f;

    vertices[prefix * side_size + 18] = half_width;
    vertices[prefix * side_size + 19] = -half_height;
    vertices[prefix * side_size + 20] = half_depth;
    vertices[prefix * side_size + 21] = 0.0f;
    vertices[prefix * side_size + 22] = 0.0f;
    vertices[prefix * side_size + 23] = 1.0f;

    vertices[prefix * side_size + 24] = -half_width;
    vertices[prefix * side_size + 25] = half_height;
    vertices[prefix * side_size + 26] = half_depth;
    vertices[prefix * side_size + 27] = 0.0f;
    vertices[prefix * side_size + 28] = 0.0f;
    vertices[prefix * side_size + 29] = 1.0f;

    vertices[prefix * side_size + 30] = half_width;
    vertices[prefix * side_size + 31] = half_height;
    vertices[prefix * side_size + 32] = half_depth;
    vertices[prefix * side_size + 33] = 0.0f;
    vertices[prefix * side_size + 34] = 0.0f;
    vertices[prefix * side_size + 35] = 1.0f;

    // top
    prefix = 2;
    vertices[prefix * side_size + 0] = -half_width;
    vertices[prefix * side_size + 1] = half_height;
    vertices[prefix * side_size + 2] = half_depth;
    vertices[prefix * side_size + 3] = 0.0f;
    vertices[prefix * side_size + 4] = 1.0f;
    vertices[prefix * side_size + 5] = 0.0f;

    vertices[prefix * side_size + 6] = half_width;
    vertices[prefix * side_size + 7] = half_height;
    vertices[prefix * side_size + 8] = half_depth;
    vertices[prefix * side_size + 9] = 0.0f;
    vertices[prefix * side_size + 10] = 1.0f;
    vertices[prefix * side_size + 11] = 0.0f;

    vertices[prefix * side_size + 12] = -half_width;
    vertices[prefix * side_size + 13] = half_height;
    vertices[prefix * side_size + 14] = -half_depth;
    vertices[prefix * side_size + 15] = 0.0f;
    vertices[prefix * side_size + 16] = 1.0f;
    vertices[prefix * side_size + 17] = 0.0f;

    vertices[prefix * side_size + 18] = half_width;
    vertices[prefix * side_size + 19] = half_height;
    vertices[prefix * side_size + 20] = half_depth;
    vertices[prefix * side_size + 21] = 0.0f;
    vertices[prefix * side_size + 22] = 1.0f;
    vertices[prefix * side_size + 23] = 0.0f;

    vertices[prefix * side_size + 24] = -half_width;
    vertices[prefix * side_size + 25] = half_height;
    vertices[prefix * side_size + 26] = -half_depth;
    vertices[prefix * side_size + 27] = 0.0f;
    vertices[prefix * side_size + 28] = 1.0f;
    vertices[prefix * side_size + 29] = 0.0f;

    vertices[prefix * side_size + 30] = half_width;
    vertices[prefix * side_size + 31] = half_height;
    vertices[prefix * side_size + 32] = -half_depth;
    vertices[prefix * side_size + 33] = 0.0f;
    vertices[prefix * side_size + 34] = 1.0f;
    vertices[prefix * side_size + 35] = 0.0f;

    // bottom
    prefix = 3;
    vertices[prefix * side_size + 0] = -half_width;
    vertices[prefix * side_size + 1] = -half_height;
    vertices[prefix * side_size + 2] = half_depth;
    vertices[prefix * side_size + 3] = 0.0f;
    vertices[prefix * side_size + 4] = -1.0f;
    vertices[prefix * side_size + 5] = 0.0f;

    vertices[prefix * side_size + 6] = half_width;
    vertices[prefix * side_size + 7] = -half_height;
    vertices[prefix * side_size + 8] = half_depth;
    vertices[prefix * side_size + 9] = 0.0f;
    vertices[prefix * side_size + 10] = -1.0f;
    vertices[prefix * side_size + 11] = 0.0f;

    vertices[prefix * side_size + 12] = -half_width;
    vertices[prefix * side_size + 13] = -half_height;
    vertices[prefix * side_size + 14] = -half_depth;
    vertices[prefix * side_size + 15] = 0.0f;
    vertices[prefix * side_size + 16] = -1.0f;
    vertices[prefix * side_size + 17] = 0.0f;

    vertices[prefix * side_size + 18] = half_width;
    vertices[prefix * side_size + 19] = -half_height;
    vertices[prefix * side_size + 20] = half_depth;
    vertices[prefix * side_size + 21] = 0.0f;
    vertices[prefix * side_size + 22] = -1.0f;
    vertices[prefix * side_size + 23] = 0.0f;

    vertices[prefix * side_size + 24] = -half_width;
    vertices[prefix * side_size + 25] = -half_height;
    vertices[prefix * side_size + 26] = -half_depth;
    vertices[prefix * side_size + 27] = 0.0f;
    vertices[prefix * side_size + 28] = -1.0f;
    vertices[prefix * side_size + 29] = 0.0f;

    vertices[prefix * side_size + 30] = half_width;
    vertices[prefix * side_size + 31] = -half_height;
    vertices[prefix * side_size + 32] = -half_depth;
    vertices[prefix * side_size + 33] = 0.0f;
    vertices[prefix * side_size + 34] = -1.0f;
    vertices[prefix * side_size + 35] = 0.0f;

    // left
    prefix = 4;
    vertices[prefix * side_size + 0] = -half_width;
    vertices[prefix * side_size + 1] = -half_height;
    vertices[prefix * side_size + 2] = half_depth;
    vertices[prefix * side_size + 3] = -1.0f;
    vertices[prefix * side_size + 4] = 0.0f;
    vertices[prefix * side_size + 5] = 0.0f;

    vertices[prefix * side_size + 6] = -half_width;
    vertices[prefix * side_size + 7] = -half_height;
    vertices[prefix * side_size + 8] = -half_depth;
    vertices[prefix * side_size + 9] = -1.0f;
    vertices[prefix * side_size + 10] = 0.0f;
    vertices[prefix * side_size + 11] = 0.0f;

    vertices[prefix * side_size + 12] = -half_width;
    vertices[prefix * side_size + 13] = half_height;
    vertices[prefix * side_size + 14] = half_depth;
    vertices[prefix * side_size + 15] = -1.0f;
    vertices[prefix * side_size + 16] = 0.0f;
    vertices[prefix * side_size + 17] = 0.0f;

    vertices[prefix * side_size + 18] = -half_width;
    vertices[prefix * side_size + 19] = -half_height;
    vertices[prefix * side_size + 20] = -half_depth;
    vertices[prefix * side_size + 21] = -1.0f;
    vertices[prefix * side_size + 22] = 0.0f;
    vertices[prefix * side_size + 23] = 0.0f;

    vertices[prefix * side_size + 24] = -half_width;
    vertices[prefix * side_size + 25] = half_height;
    vertices[prefix * side_size + 26] = half_depth;
    vertices[prefix * side_size + 27] = -1.0f;
    vertices[prefix * side_size + 28] = 0.0f;
    vertices[prefix * side_size + 29] = 0.0f;

    vertices[prefix * side_size + 30] = -half_width;
    vertices[prefix * side_size + 31] = half_height;
    vertices[prefix * side_size + 32] = -half_depth;
    vertices[prefix * side_size + 33] = -1.0f;
    vertices[prefix * side_size + 34] = 0.0f;
    vertices[prefix * side_size + 35] = 0.0f;

    // right
    prefix = 5;
    vertices[prefix * side_size + 0] = half_width;
    vertices[prefix * side_size + 1] = -half_height;
    vertices[prefix * side_size + 2] = half_depth;
    vertices[prefix * side_size + 3] = 1.0f;
    vertices[prefix * side_size + 4] = 0.0f;
    vertices[prefix * side_size + 5] = 0.0f;

    vertices[prefix * side_size + 6] = half_width;
    vertices[prefix * side_size + 7] = -half_height;
    vertices[prefix * side_size + 8] = -half_depth;
    vertices[prefix * side_size + 9] = 1.0f;
    vertices[prefix * side_size + 10] = 0.0f;
    vertices[prefix * side_size + 11] = 0.0f;

    vertices[prefix * side_size + 12] = half_width;
    vertices[prefix * side_size + 13] = half_height;
    vertices[prefix * side_size + 14] = half_depth;
    vertices[prefix * side_size + 15] = 1.0f;
    vertices[prefix * side_size + 16] = 0.0f;
    vertices[prefix * side_size + 17] = 0.0f;

    vertices[prefix * side_size + 18] = half_width;
    vertices[prefix * side_size + 19] = -half_height;
    vertices[prefix * side_size + 20] = -half_depth;
    vertices[prefix * side_size + 21] = 1.0f;
    vertices[prefix * side_size + 22] = 0.0f;
    vertices[prefix * side_size + 23] = 0.0f;

    vertices[prefix * side_size + 24] = half_width;
    vertices[prefix * side_size + 25] = half_height;
    vertices[prefix * side_size + 26] = half_depth;
    vertices[prefix * side_size + 27] = 1.0f;
    vertices[prefix * side_size + 28] = 0.0f;
    vertices[prefix * side_size + 29] = 0.0f;

    vertices[prefix * side_size + 30] = half_width;
    vertices[prefix * side_size + 31] = half_height;
    vertices[prefix * side_size + 32] = -half_depth;
    vertices[prefix * side_size + 33] = 1.0f;
    vertices[prefix * side_size + 34] = 0.0f;
    vertices[prefix * side_size + 35] = 0.0f;

    reset();
}

void Track::draw(glm::mat4 &view, glm::mat4 &projection)
{
    apply_transformations();

    shader.use();
    glBindVertexArray(vao);

    glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shader.program, "objectColor"), frag_color.r, frag_color.g, frag_color.b);

    // draw line
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(transform_matrix));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Track::reset()
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