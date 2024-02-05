#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "lab_m1/Homework1/transform2D.h"
#include "../homework1.h"
#include "Shape.h"
#include "Star.h"

using namespace shape;
using namespace std;

int Star::nrStarsWallet = 0;
int Star::nrStarsCannon = 0;
int Star::nrStarsToCollect = 0;

extern vector<Shape*> shapes;

Star::Star() {}

Star::Star(std::string nameMesh, glm::vec3 location, glm::vec3 color, int side) : Shape(nameMesh, location , color) {

    this->side = side;
    this->angle = 0;

    if(color == GOLD){
        
        nrStarsWallet++;
        this->nameMesh += "Wallet";
        this->nameShape = this->nameMesh + to_string(nrStarsWallet);

    }else if(color == ORANGE){
        nrStarsCannon++;
        this->nameMesh += "Orange";
        this->nameShape = this->nameMesh + to_string(nrStarsCannon);

    }else if(color == BLUE){
        nrStarsCannon++;
        this->nameMesh += "Blue";
        this->nameShape = this->nameMesh + to_string(nrStarsCannon);

    }else if(color == YELLOW){
        nrStarsCannon++;
        this->nameMesh += "Yellow";
        this->nameShape = this->nameMesh + to_string(nrStarsCannon);

    }else if(color == PURPLE){
        nrStarsCannon++;
        this->nameMesh += "Purple";
        this->nameShape = this->nameMesh + to_string(nrStarsCannon);

    }else if(color == ROSE){
        
        nrStarsToCollect++;
        this->nameMesh += "Collected ";
        this->nameShape = this->nameMesh + to_string(nrStarsToCollect);
    
    }else{

        this->nameShape = nameMesh;

    }


}

Mesh* Star::create(){

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(side * 20.0f, side * 40.0f, 0), color),//0
        VertexFormat(corner + glm::vec3(side * 0.0f, side * 25.0f, 0), color),//1
        VertexFormat(corner + glm::vec3(side * 5.0f, side * 0.0f, 0), color),//2
        VertexFormat(corner + glm::vec3(side * 20.0f, side * 10.0f, 0), color),//3
        VertexFormat(corner + glm::vec3(side * 35.0f, side * 0.0f, 0), color),//4
        VertexFormat(corner + glm::vec3(side * 40.0f, side * 25.0f, 0), color),//5  
    };

    Mesh* star = new Mesh(nameMesh);

    star->SetDrawMode(GL_TRIANGLES); 

    std::vector<unsigned int> indices = {
                                            0, 2, 3,
                                            0, 3, 4,
                                            1, 3, 5,
                                        };

    star->InitFromData(vertices, indices);

    return star;
}

glm::mat3 Star::animation(float deltaTimeSeconds){

    glm::mat3 modelMatrix;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(location[0], location[1]);

    if(color == ORANGE || color == BLUE || color == YELLOW || color == PURPLE){
        
        if(location[0] > 1300) animationType = COMPLETED;

        modelMatrix *= transform2D::Translate(40, 35);
        modelMatrix *= transform2D::Rotate(angle);
        modelMatrix *= transform2D::Translate(-40, -35);
        location[0] += 100 * deltaTimeSeconds;
        angle += 3 * deltaTimeSeconds;

    }

    return modelMatrix;
}

bool Star::distance(int x, int y){
    
    float xCenter = location[0]+20*side;
    float yCenter = location[1]+20*side;
    double d = sqrt(pow(xCenter-x,2) + pow(yCenter-y,2));

    return d < 15*side;
}

void Star::mouseClickOnMe(){

    if(color == ROSE) animationType = COMPLETED;

}

void Star::deleteStarsWallet(int nrStarsToDelete) {

    for (int i = (int)shapes.size()-1; i>=0 && nrStarsToDelete>0; i--) {

        Shape *shape = shapes[i];
        if(shape->getNameShape().find("Wallet") < shape->getNameShape().size()){
            shape->setAnimationType(COMPLETED);
            nrStarsWallet--;
            nrStarsToDelete--;

        }

    }

}

void Star::collision(){
    animationType = COMPLETED;
}
