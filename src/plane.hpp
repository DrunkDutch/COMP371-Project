//
// Created by Jeremy Brown on 2017-06-03.
//

#ifndef COMP371_PROJECT_PLANE_H
#define COMP371_PROJECT_PLANE_H


#include "geo_obj.hpp"

class Plane : public GeometricObject {

public:
    Plane(glm::vec3 initial_location, GLfloat width, GLfloat length, Shader shader);

    virtual void draw(glm::mat4 &view, glm::mat4 &projection);

    virtual void reset();

private:
    GLfloat vertices[6 * 6];  // 6 vertices per side * 6 values per vertice (x,y,z for position & x,y,z for normal)
    GLfloat line[6];
    GLuint vao;
};


#endif  // COMP371_PROJECT_PLANE_H
