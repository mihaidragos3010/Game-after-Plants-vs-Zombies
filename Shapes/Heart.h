#pragma once
#include "lab_m1/homework1/transform2D.h"
#include "core/gpu/mesh.h"
#include "Shape.h"

namespace shape {

    class Heart : public Shape{

    private:
        static int nrHearts;
    public:
        Heart();
        Heart(std::string nameMesh, glm::vec3 location, glm::vec3 color);
        Mesh* Heart::create();
    };

}