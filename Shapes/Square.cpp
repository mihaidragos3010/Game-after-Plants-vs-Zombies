#include <string>
#include <vector>
#include <iostream>
#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "lab_m1/Homework1/transform2D.h"
#include "Shape.h"
#include "Square.h"

using namespace shape;
using namespace std;

    
Square::Square() {}

Square::Square(std::string nameMesh, glm::vec3 location, glm::vec3 color, float length, bool fill) : Shape(nameMesh, location , color) {
    
    this->length = length;
    this->corner = glm::vec3(0, 0, -1);
    this->nameShape = nameMesh;
    this->fill = fill;
    this->isFree = true;
}

Mesh* Square::create(){
    
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(nameMesh);
    std::vector<unsigned int> indices = { 0, 3, 2, 1 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }
    
    square->InitFromData(vertices, indices);
    return square;

}

bool Square::checkIsFree(){
    return isFree;
}
void Square::takePlace(){
    this->isFree = false;
}

void Square::ReleasePlace(){
    this->isFree = true;
}

