#pragma once
#include "lab_m1/homework1/transform2D.h"
#include "core/gpu/mesh.h"
#include<iostream>
#include "Shape.h"

namespace shape {

    class Star : public Shape{

    private:
        int side;
        float angle;
    public:
        static int nrStarsWallet;
        static int nrStarsCannon;
        static int nrStarsToCollect;

        Star();
        Star(std::string nameMesh, glm::vec3 location, glm::vec3 color, int side);
        Mesh* create();
        glm::mat3 animation(float deltaTimeSeconds);
        void collision();
        bool distance(int x, int y);
        void mouseClickOnMe();
        static void deleteStarsWallet(int nr);

        enum starSide{
            SMALL = 1,
            BIG = 2
        };

    };
}