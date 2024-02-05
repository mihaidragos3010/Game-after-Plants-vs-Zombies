#include <string.h>
#include <cmath>
#include "utils/glm_utils.h"
#include "lab_m1/Homework1/transform2D.h"
#include "lab_m1/Homework1/Shapes/Shape.h"
#include "Shape.h"

using namespace shape;

Shape::Shape() {}

Shape::Shape(std::string nameMesh, glm::vec3 location, glm::vec3 color) {

    this->nameMesh = nameMesh;
    this->location = location;
    this->color = color;
    this->corner = glm::vec3(0, 0, 0);
    animationType = ACTION;
}

Shape::~Shape() {}

std::string Shape::getNameMesh(){ return nameMesh;}
std::string Shape::getNameShape(){ return nameShape;}
glm::vec3 Shape::getColor(){ return color;}
glm::vec3 Shape::getLocation(){ return location;}
int Shape::getAnimationType() { return animationType; }

void Shape::setAnimationType(AnimationType animation){ this->animationType = animation;}
void Shape::setLocation(glm::vec3 newLocation){ location = newLocation;}

glm::mat3 Shape::animation(float deltaTimeSeconds){

    glm::mat3 modelMatrix;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(location[0],location[1]);

    return modelMatrix;

}

void Shape::collision(){}

bool Shape::drawOnScreen(){ return animationType != COMPLETED;}

bool Shape::distance(int x, int y){ 
    float xCenter = location[0] + 60;
    float yCenter = location[1] + 60;
    double d = sqrt(pow(xCenter-x,2) + pow(yCenter-y,2));

    return d < 60;
}

void Shape::mouseClickOnMe(){}