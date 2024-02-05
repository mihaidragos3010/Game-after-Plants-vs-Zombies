#pragma once
#include <string.h>
#include <iostream>
#include "lab_m1/homework1/transform2D.h"
#include "core/gpu/mesh.h"

#define ORANGE glm::vec3(0.949f, 0.553f, 0.09f)
#define BLUE glm::vec3(0.09f, 0.592f, 0.949f)
#define YELLOW glm::vec3(0.949f, 0.925f, 0.09f)
#define PURPLE glm::vec3(0.58f, 0.09f, 0.949f)
#define GREEN glm::vec3(0, 1, 0)
#define DARK_GREEN glm::vec3(0.055f, 0.302f, 0.078f)
#define BLACK glm::vec3(0,0,0)
#define RED glm::vec3(1,0,0)
#define ROSE  glm::vec3(1,0,1)
#define GRAY glm::vec3(0.631f,0.627f,0.588f)
#define GOLD glm::vec3(0.902f,0.722f,0.341f)

#define OffsetShapesX 60
#define OffsetShapesY 60

namespace shape {

    class Shape {

        public:

            enum AnimationType{
                COMPLETED = -1,
                DESTRUCTION = 0,
                ACTION = 1
            };

            Shape();
            Shape(std::string nameMesh, glm::vec3 location, glm::vec3 color);
            ~Shape();

            std::string getNameMesh();
            std::string getNameShape();
            glm::vec3 getColor();
            glm::vec3 getLocation();
            int getAnimationType();
            
            void setAnimationType(AnimationType animation);
            void setLocation(glm::vec3 newLocation);

            virtual Mesh* create() = 0;
            virtual glm::mat3 animation(float deltaTimeSeconds);
            virtual void collision();
            bool drawOnScreen();
            virtual bool distance(int x, int y);
            virtual void mouseClickOnMe();
            
        protected:
            glm::vec3 corner;
            glm::vec3 location;
            AnimationType animationType;
            std::string nameShape;
            std::string nameMesh;
            glm::vec3 color;

    };

}