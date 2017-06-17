//
// Created by Jeremy Brown on 2017-06-17.
//

#ifndef COMP371_PROJECT_LAMP_H
#define COMP371_PROJECT_LAMP_H

#include "cube.hpp"

class Lamp : public Cube
{
public:
    Lamp(glm::vec3 initial_location, Shader shader, float side_length = 3)
            : Cube(initial_location, shader, side_length) {};

    void set_enabled(bool enabled)
    {
        this->enabled = enabled;
        update_frag_color();
    }

    void toggle()
    {
        this->enabled = !this->enabled;
        update_frag_color();
    }

    bool is_enabled()
    {
        return enabled;
    }

private:
    void update_frag_color()
    {
        if (this->is_enabled()) {
            frag_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        } else {
            frag_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }

    bool enabled;
};

#endif //COMP371_PROJECT_LAMP_H
