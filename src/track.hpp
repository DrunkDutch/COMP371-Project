//
// Created by Jeremy Brown on 2017-06-02.
//

#ifndef COMP371_PROJECT_TRACK_H
#define COMP371_PROJECT_TRACK_H

#include "geo_obj.hpp"
#include "shader.hpp"

class Track : public GeometricObject
{
public:
    Track(glm::vec3 initial_location, Shader shader, glm::vec3 dimensions = glm::vec3(12.0f, 1.0f, 2.0f));

    virtual void draw(glm::mat4 &view, glm::mat4 &projection);

    virtual void reset();

private:
    GLfloat vertices[6 * 6 * 6];  // 6 sides * 6 vertices per side * 6 values per vertice (x,y,z for position & x,y,z for normal)
    GLuint vao;
};


#endif  // COMP371_PROJECT_TRACK_H
