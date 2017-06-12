//
// Created by Jeremy Brown on 2017-05-22.
//

#ifndef COMP371_PROJECT_GEO_OBJ_H
#define COMP371_PROJECT_GEO_OBJ_H

#include <vector>

#include <glm/detail/type_mat.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

class GeometricObject
{
public:
    GeometricObject(Shader shader, glm::vec3 initial_translation = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 initial_scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
            shader(shader), initial_scale(initial_scale), initial_translation(initial_translation) {};

    virtual void draw(glm::mat4 &view, glm::mat4 &projection) = 0;

    virtual void apply_transformations()
    {
        // reset transformation matrix
        transform_matrix = glm::mat4();

        // apply translation
        transform_matrix = glm::translate(transform_matrix, translate_vec);

        // apply scaling
        transform_matrix = glm::scale(transform_matrix, scale_vec);

        // apply rotation (last rotation is applied first)
        glm::quat total_quat;

        for (auto it = rotations.rbegin(); it != rotations.rend(); it++) {
            total_quat = total_quat * (*it);
        }
        transform_matrix = transform_matrix * glm::toMat4(total_quat);

//        double dArray[16] = {0.0};
//        const float *pSource = (const float*)glm::value_ptr(transform_matrix);
//        for (int i = 0; i < 16; ++i)
//            std::cout << pSource[i] << " ";
//        std::cout << std::endl;
    }

    virtual void translate(glm::vec3 &translation_vec3)
    {
        translate_vec += translation_vec3;
    }

    virtual void scale(glm::vec3 &scale_vec3)
    {
        scale_vec *= scale_vec3;
    }

    virtual void rotate(float angle_degrees, glm::vec3 &axis_vector)
    {
        glm::quat quat = glm::angleAxis(glm::radians(angle_degrees), axis_vector);
        rotations.push_back(quat);
    }

    virtual void reset() = 0;

    void set_color(glm::vec4 &color_vec4)
    {
        frag_color = color_vec4;
    }

    glm::vec3 get_position()
    {
        return translate_vec;
    }

protected:
    // shader info
    glm::vec4 frag_color;
    Shader shader;

    // transformation info
    glm::mat4 transform_matrix;
    std::vector<glm::quat> rotations;
    glm::vec3 scale_vec;
    glm::vec3 translate_vec;

    glm::vec3 initial_scale;
    glm::vec3 initial_translation;
};

#endif  // COMP371_PROJECT_GEO_OBJ_H
