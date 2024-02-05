#pragma once
#include "lab_m1/homework1/transform2D.h"
#include "core/gpu/mesh.h"
#include "Rectangle.h"

namespace shape {

    class Rectangle : public Shape{
    
    private:
        float width;
        float height;

    public:
        Rectangle();
        Rectangle(std::string nameMesh, glm::vec3 location, glm::vec3 color, float width, float height);
        Mesh* Rectangle::create();
    };

}