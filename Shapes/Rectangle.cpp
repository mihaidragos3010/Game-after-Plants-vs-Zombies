#include <string>
#include <vector>
#include <iostream>
#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "lab_m1/Homework1/transform2D.h"
#include "Shape.h"
#include "Rectangle.h"

using namespace shape;
using namespace std;

    
Rectangle::Rectangle() {}

Rectangle::Rectangle(std::string nameMesh, glm::vec3 location, glm::vec3 color, float width, float height) : Shape(nameMesh, location , color) {
    
    this->width = width;
    this->height = height;
    this->nameShape = nameMesh;
    this->corner = glm::vec3(0, 0, -1);

}

Mesh* Rectangle::create(){
    
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),//0 
        VertexFormat(corner + glm::vec3(width, 0, 0), color),//1
        VertexFormat(corner + glm::vec3(width, height, 0), color),//2
        VertexFormat(corner + glm::vec3(0, height, 0), color)//3
    };

    Mesh* rectangle = new Mesh(nameMesh);
    std::vector<unsigned int> indices = {
                                            0, 1, 2, 
                                            2, 3, 0
                                        };

    rectangle->InitFromData(vertices, indices);
    return rectangle;

}
