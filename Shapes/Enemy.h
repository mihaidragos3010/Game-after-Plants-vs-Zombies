#pragma once
#include "lab_m1/homework1/transform2D.h"
#include "core/gpu/mesh.h"
#include "Enemy.h"

namespace shape {

    class Enemy : public Shape{
        
    private:
        static int nrEnemies;
        glm::vec3 translateEnemy;
        int hearts;
        
    public:

        Enemy();
        Enemy(std::string nameMesh, glm::vec3 location, glm::vec3 color);
        Mesh* Enemy::create();
        glm::mat3 animation(float deltaTimeSeconds);
        void collision();
    };

}