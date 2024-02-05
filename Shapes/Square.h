#pragma once
#include "lab_m1/homework1/transform2D.h"
#include "core/gpu/mesh.h"
#include "Shape.h"


namespace shape {

    class Square : public Shape{
    
    private:
        float length;
        bool fill;
        int isFree;

    public:
        Square();
        Square(std::string nameMesh, glm::vec3 location, glm::vec3 color, float length, bool fill);
        Mesh* Square::create();
        bool checkIsFree();
        void takePlace();
        void ReleasePlace();
    };

}