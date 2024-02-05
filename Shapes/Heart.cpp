#include <string>
#include <vector>
#include <iostream>
#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "lab_m1/Homework1/transform2D.h"
#include "Shape.h"
#include "Heart.h"

using namespace shape;
using namespace std;

int Heart::nrHearts = 0;

Heart::Heart() {}

Heart::Heart(std::string nameMesh, glm::vec3 location, glm::vec3 color) : Shape(nameMesh, location , color) {

    nrHearts++;
    this->nameShape = nameMesh + to_string(nrHearts);
    
}

Mesh* Heart::create(){
    
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(60, 75, 0), color),//0
        VertexFormat(corner + glm::vec3(50, 90, 0), color),//1
        VertexFormat(corner + glm::vec3(30, 90, 0), color),//2
        VertexFormat(corner + glm::vec3(20, 75, 0), color),//3
        VertexFormat(corner + glm::vec3(60, 10, 0), color),//4
        VertexFormat(corner + glm::vec3(100, 75, 0), color),//5  
        VertexFormat(corner + glm::vec3(90, 90, 0), color),//6
        VertexFormat(corner + glm::vec3(70, 90, 0), color),//7
    };

    Mesh* heart = new Mesh(nameMesh);

    heart->SetDrawMode(GL_TRIANGLES); 

    std::vector<unsigned int> indices = {
                                            0, 1, 2,
                                            0, 2, 3,
                                            0, 3, 4,
                                            0, 4, 5,
                                            0, 5, 6,
                                            0, 6, 7,
                                        };

    heart->InitFromData(vertices, indices);
    return heart;
}

