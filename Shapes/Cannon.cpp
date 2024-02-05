#include <string>
#include <vector>
#include <iostream>
#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "lab_m1/Homework1/transform2D.h"
#include "Shape.h"
#include "Cannon.h"
#include "Star.h"

using namespace shape;
using namespace std;

extern vector<Shape*> shapes;

int Cannon::nrCannons = 0;
Cannon::Cannon() {}

Cannon::Cannon(std::string nameMesh, glm::vec3 location, glm::vec3 color) : Shape(nameMesh, location , color) {

    nrCannons++;
    this->onShooting = false; 
    this->animationType = ACTION;

    if(color == ORANGE){ this->nameMesh += "Orange"; this->price = 1;} 
    if(color == BLUE){ this->nameMesh += "Blue"; this->price = 2;}
    if(color == YELLOW){ this->nameMesh += "Yellow"; this->price = 2;}
    if(color == PURPLE){ this->nameMesh += "Purple"; this->price = 3;}

    if(nrCannons > 4){ 
        startAnimation = std::chrono::high_resolution_clock::now();
        this->nameShape += nameMesh + to_string(nrCannons);
    }

    if(nameMesh.find("Clone") < 15) this->nameShape += nameMesh + to_string(nrCannons);

    translateCannon = glm::vec3(1, 1, 0);
}

int Cannon::getPrice(){ return price;}

Mesh* Cannon::create(){
    
    std::vector<VertexFormat> vertices =
    {   
        VertexFormat(corner + glm::vec3(40, 60, 0), color),//0
        VertexFormat(corner + glm::vec3(60, 10, 0), color),//1
        VertexFormat(corner + glm::vec3(60, 60, 0), color),//2
        VertexFormat(corner + glm::vec3(80, 60, 0), color),//3
        VertexFormat(corner + glm::vec3(60, 110, 0), color),//4
        VertexFormat(corner + glm::vec3(60, 50, 0), color),//5
        VertexFormat(corner + glm::vec3(110, 50, 0), color),//6
        VertexFormat(corner + glm::vec3(110, 70, 0), color),//7
        VertexFormat(corner + glm::vec3(60, 70, 0), color),//8
    };

    Mesh* cannon  = new Mesh(nameMesh);
    std::vector<unsigned int> indices = {
                                            2, 0, 1,
                                            2, 1, 3,
                                            2, 4, 0,
                                            2, 3, 4, 
                                            5, 6, 7,
                                            5, 7, 8
                                        };

    cannon->InitFromData(vertices, indices);
    return cannon;

}

glm::mat3 Cannon::animation(float deltaTimeSeconds){

    glm::mat3 modelMatrix;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(location[0], location[1]);

    if(animationType == DESTRUCTION){

        if(translateCannon[0] < 0.2f) animationType=COMPLETED;

        modelMatrix *= transform2D::Translate(60, 60);
        modelMatrix *= transform2D::Scale(translateCannon[0], translateCannon[1]);
        modelMatrix *= transform2D::Translate(-60, -60);
        translateCannon *= glm::vec3(0.97f, 0.97f,0);

    }

    if(animationType == ACTION && onShooting){

        auto endAnimation = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> timeSeconds = endAnimation - startAnimation;

        if(timeSeconds.count() > 4){

            startAnimation = std::chrono::high_resolution_clock::now();
            shapes.push_back(new Star("Star", this->location+distanceFromCannon, this->color, Star::BIG));

        }
        
    }
    
    return modelMatrix;

}

void Cannon::startShooting(){ 
    onShooting = true;
}

void Cannon::stopShooting(){ 
    onShooting = false;
}

void Cannon::collision(){ 
    animationType = DESTRUCTION;
}