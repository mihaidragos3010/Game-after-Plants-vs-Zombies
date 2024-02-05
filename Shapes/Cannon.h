#pragma once
#include <chrono>
#include "lab_m1/homework1/transform2D.h"
#include "core/gpu/mesh.h"
#include "Cannon.h"

#define distanceFromCannon glm::vec3(30, 30, 0)

namespace shape {

    class Cannon : public Shape{

    private:
        static int nrCannons;
        glm::vec3 translateCannon;
        int price;
        bool onShooting;

        std::chrono::time_point<std::chrono::high_resolution_clock> startAnimation;
        std::chrono::time_point<std::chrono::high_resolution_clock> endAnimation;

    public:
        Cannon();
        Cannon(std::string nameMesh, glm::vec3 location, glm::vec3 color);
        int getPrice();

        Mesh* Cannon::create();
        glm::mat3 Cannon::animation(float deltaTimeSeconds);
        void startShooting();
        void stopShooting();
        void collision();
    };

}