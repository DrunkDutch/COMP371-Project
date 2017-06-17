//
// Created by Jeremy Brown on 2017-06-17.
//

#ifndef COMP371_PROJECT_LAMP_H
#define COMP371_PROJECT_LAMP_H

#include "cube.hpp"

class Lamp : public Cube
{
public:
    Lamp(glm::vec3 initial_location, Shader shader, float side_length = 5)
            : Cube(initial_location, shader, side_length) {};

    void set_enabled(bool enabled)
    {
        this->enabled = enabled;
    }

    void toggle()
    {
        this->enabled = !this->enabled;
    }

    bool is_enabled()
    {
        return enabled;
    }

private:
    bool enabled;
};

#endif //COMP371_PROJECT_LAMP_H
