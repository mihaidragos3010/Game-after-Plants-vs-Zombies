#include <string>
#include <vector>
#include <iostream>
#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "lab_m1/Homework1/transform2D.h"
#include "Shape.h"
#include "Enemy.h"

using namespace shape;
using namespace std;

int Enemy::nrEnemies = 0;

extern int nrHearts;
extern vector<Shape*> shapes;

Enemy::Enemy() {}

Enemy::Enemy(std::string nameMesh, glm::vec3 location, glm::vec3 color) : Shape(nameMesh, location , color) {

    nrEnemies++;
    this->translateEnemy = glm::vec3(1, 1, 0);
    this->hearts = 3;

    if(color == ORANGE) this->nameMesh += "Orange";
    if(color == BLUE) this->nameMesh += "Blue";
    if(color == YELLOW) this->nameMesh += "Yellow";
    if(color == PURPLE) this->nameMesh += "Purple";

    this->nameShape = nameMesh + to_string(nrEnemies);

}

Mesh* Enemy::create(){
    
    std::vector<VertexFormat> vertices;
        float hexagonSide = 1;
        glm::vec3 corner = glm::vec3(0,0,0);
        vertices = {
            VertexFormat(corner + glm::vec3(60, 60, 0), DARK_GREEN),//0
            VertexFormat(corner + glm::vec3(47.5f, 90, 0), DARK_GREEN),//1
            VertexFormat(corner + glm::vec3(30, 72.5f, 0), DARK_GREEN),//2
            VertexFormat(corner + glm::vec3(30, 47.5f, 0), DARK_GREEN),//3
            VertexFormat(corner + glm::vec3(47.5f, 30, 0), DARK_GREEN),//4
            VertexFormat(corner + glm::vec3(72.5f, 30, 0), DARK_GREEN),//5
            VertexFormat(corner + glm::vec3(90, 47.5f, 0), DARK_GREEN),//6
            VertexFormat(corner + glm::vec3(90, 72.5f, 0), DARK_GREEN),//7
            VertexFormat(corner + glm::vec3(72.5f, 90, 0), DARK_GREEN),//8  
            VertexFormat(corner + glm::vec3(30, 110, 0), color),//9
            VertexFormat(corner + glm::vec3(10, 85, 0), color),//10
            VertexFormat(corner + glm::vec3(10, 35, 0), color),//11
            VertexFormat(corner + glm::vec3(35, 10, 0), color),//12
            VertexFormat(corner + glm::vec3(85, 10, 0), color),//13
            VertexFormat(corner + glm::vec3(110, 35, 0), color),//14
            VertexFormat(corner + glm::vec3(110, 85, 0), color),//15
            VertexFormat(corner + glm::vec3(85, 110, 0), color),//16
        };


        Mesh* hexagon = new Mesh(nameMesh);
        
        std::vector<unsigned int> indices = {
                                                0, 1, 2,
                                                0, 2, 3,
                                                0, 3, 4,
                                                0, 4, 5,
                                                0, 5, 6,
                                                0, 6, 7,
                                                0, 7, 8,
                                                0, 8, 1,
                                                0, 9 ,10,
                                                0, 10, 11,
                                                0, 11, 12,
                                                0, 12, 13,
                                                0, 13, 14,
                                                0, 14, 15,
                                                0, 15, 16,
                                                0, 16, 9
                                            };

        hexagon->InitFromData(vertices, indices);
        return hexagon;
}

glm::mat3 Enemy::animation(float deltaTimeSeconds){

    glm::mat3 modelMatrix;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(location[0], location[1]);

    if(location[0] <= 0){
        
        animationType = COMPLETED;
        string searchHeart = "Heart" + to_string(nrHearts);
        for(Shape* shape : shapes)
            if(shape->getNameShape() == searchHeart)
                shape->setAnimationType(COMPLETED);
        nrHearts--;
    }

    if(animationType == ACTION){

        modelMatrix *= transform2D::Translate(60, 60);
        modelMatrix *= transform2D::Rotate(30);
        modelMatrix *= transform2D::Translate(-60, -60);
        location[0] -= 40 * deltaTimeSeconds;

    }

    if(animationType == DESTRUCTION){

        if(translateEnemy[0] < 0.2f) animationType=COMPLETED;
        modelMatrix *= transform2D::Translate(60, 60);
        modelMatrix *= transform2D::Scale(translateEnemy[0], translateEnemy[1]);
        modelMatrix *= transform2D::Translate(-60, -60);
        translateEnemy *= glm::vec3(0.97f, 0.97f,0);

    }

    return modelMatrix;

}

void Enemy::collision(){

    this->hearts--;
    if(this->hearts == 0){
        animationType = DESTRUCTION;
    }

}
