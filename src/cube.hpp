//
// Created by Jeremy Brown on 2017-06-06.
//

#ifndef COMP371_PROJECT_CUBE_H
#define COMP371_PROJECT_CUBE_H

#include <glm/vec3.hpp>

#include "shader.hpp"
#include "track.hpp"

class Cube : public Track
{
public:
    Cube(glm::vec3 initial_location, Shader shader, float side_length = 5)
    : Track(initial_location, shader, glm::vec3(side_length, side_length, side_length)) {};
};


#endif //COMP371_PROJECT_CUBE_H
