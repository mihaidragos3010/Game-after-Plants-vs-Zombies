// #include "object2D.h"

// #include <vector>

// #include "core/engine.h"
// #include "utils/gl_utils.h"


// Mesh* object2D::CreateSquare(
//     const std::string& name,
//     glm::vec3 leftBottomCorner,
//     float length,
//     glm::vec3 color,
//     bool fill)
// {
//     glm::vec3 corner = leftBottomCorner;

//     std::vector<VertexFormat> vertices =
//     {
//         VertexFormat(corner, color),
//         VertexFormat(corner + glm::vec3(length, 0, 0), color),
//         VertexFormat(corner + glm::vec3(length, length, 0), color),
//         VertexFormat(corner + glm::vec3(0, length, 0), color)
//     };

//     Mesh* square = new Mesh(name);
//     std::vector<unsigned int> indices = { 0, 1, 2, 3 };

//     if (!fill) {
//         square->SetDrawMode(GL_LINE_LOOP);
//     }
//     else {
//         // Draw 2 triangles. Add the remaining 2 indices
//         indices.push_back(0);
//         indices.push_back(2);
//     }

//     square->InitFromData(vertices, indices);
//     return square;
// }

// Mesh* object2D::CreateRectangle(
//     const std::string& name,
//     glm::vec3 leftBottomCorner,
//     float height,
//     float width,
//     glm::vec3 color,
//     bool fill)
// {
//     glm::vec3 corner = leftBottomCorner;

//     std::vector<VertexFormat> vertices =
//     {
//         VertexFormat(corner, color),
//         VertexFormat(corner + glm::vec3(width, 0, 0), color),
//         VertexFormat(corner + glm::vec3(width, height, 0), color),
//         VertexFormat(corner + glm::vec3(0, height, 0), color)
//     };

//     Mesh* rectangle = new Mesh(name);
//     std::vector<unsigned int> indices = { 0, 1, 2, 3 };

//     if (!fill) {
//         rectangle->SetDrawMode(GL_LINE_LOOP);
//     }
//     else {
//         // Draw 2 triangles. Add the remaining 2 indices
//         indices.push_back(0);
//         indices.push_back(2);
//     }

//     rectangle->InitFromData(vertices, indices);
//     return rectangle;
// }

// Mesh* object2D::CreateRhombus(
//     const std::string& name,
//     glm::vec3 leftBottomCorner,
//     glm::vec3 color)
// {
//     glm::vec3 corner = glm::vec3(0, 0, 0);

//     std::vector<VertexFormat> vertices =
//     {   
//         VertexFormat(corner + glm::vec3(40, 60, 0), color),//0
//         VertexFormat(corner + glm::vec3(60, 10, 0), color),//1
//         VertexFormat(corner + glm::vec3(60, 60, 0), color),//2
//         VertexFormat(corner + glm::vec3(80, 60, 0), color),//3
//         VertexFormat(corner + glm::vec3(60, 110, 0), color),//4
//         VertexFormat(corner + glm::vec3(60, 50, 0), color),//5
//         VertexFormat(corner + glm::vec3(110, 50, 0), color),//6
//         VertexFormat(corner + glm::vec3(110, 70, 0), color),//7
//         VertexFormat(corner + glm::vec3(60, 70, 0), color),//8
//     };

//     Mesh* rhombus = new Mesh(name);
//     std::vector<unsigned int> indices = {2, 0 ,1,
//                                          2, 1, 3,
//                                          2, 4, 0,
//                                          2, 3, 4, 
//                                          5, 6, 7,
//                                          5, 7, 8
//                                                 };

//     //rectangle->SetDrawMode(GL_TRIANGLES);

//     rhombus->InitFromData(vertices, indices);
//     return rhombus;
// }

// Mesh* object2D::CreateStar(
//     const std::string& name,
//     glm::vec3 leftBottomCorner,
//     float starSide,
//     glm::vec3 color)
// {
//     glm::vec3 corner = glm::vec3(0, 0, 0);

//     std::vector<VertexFormat> vertices =
//     {
//         VertexFormat(corner + glm::vec3(starSide *20, starSide *40, 0), color),//0
//         VertexFormat(corner + glm::vec3(starSide *0, starSide *25, 0), color),//1
//         VertexFormat(corner + glm::vec3(starSide *5, starSide * 0, 0), color),//2
//         VertexFormat(corner + glm::vec3(starSide * 20, starSide * 10, 0), color),//3
//         VertexFormat(corner + glm::vec3(starSide * 35, starSide * 0, 0), color),//4
//         VertexFormat(corner + glm::vec3(starSide * 40, starSide * 25, 0), color),//5  
//     };

//     Mesh* star = new Mesh(name);

//     // Modificăm modul de desenare la GL_TRIANGLES sau GL_TRIANGLE_FAN
//     star->SetDrawMode(GL_TRIANGLES); 

//     std::vector<unsigned int> indices = {0, 2, 3,
//                                          0, 3, 4,
//                                          1, 3, 5
//     };

//     star->InitFromData(vertices, indices);
//     return star;
// }

// Mesh* object2D::CreateHexagon(
//     const std::string& name,
//     glm::vec3 leftBottomCorner,
//     float hexagonSide,
//     glm::vec3 color)
// {
//     glm::vec3 corner = glm::vec3(0, 0, 0);
//     std::vector<VertexFormat> vertices;

//     if (hexagonSide == 1) {
//         float x = 1;
//         float y = 3;
//         hexagonSide = x/y;
//         vertices =
//         {
//             vertices = {
//             VertexFormat(corner + glm::vec3(60, 60, 0), color),//0
//             VertexFormat(corner + glm::vec3(47.5f, 90, 0), color),//1
//             VertexFormat(corner + glm::vec3(30, 72.5f, 0), color),//2
//             VertexFormat(corner + glm::vec3(30, 47.5f, 0), color),//3
//             VertexFormat(corner + glm::vec3(47.5f, 30, 0), color),//4
//             VertexFormat(corner + glm::vec3(72.5f, 30, 0), color),//5
//             VertexFormat(corner + glm::vec3(90, 47.5f, 0), color),//6
//             VertexFormat(corner + glm::vec3(90, 72.5f, 0), color),//7
//             VertexFormat(corner + glm::vec3(72.5f, 90, 0), color),//8  
//             }

//         };
//     }
//     else 
//     {
//         vertices = {
//             VertexFormat(corner + glm::vec3(60, 60, 0), color),//0
//             VertexFormat(corner + glm::vec3(30, 110, 0), color),//1
//             VertexFormat(corner + glm::vec3(10, 85, 0), color),//2
//             VertexFormat(corner + glm::vec3(10, 35, 0), color),//3
//             VertexFormat(corner + glm::vec3(35, 10, 0), color),//4
//             VertexFormat(corner + glm::vec3(85, 10, 0), color),//5
//             VertexFormat(corner + glm::vec3(110, 35, 0), color),//6
//             VertexFormat(corner + glm::vec3(110, 85, 0), color),//7
//             VertexFormat(corner + glm::vec3(85, 110, 0), color),//8
//         };
//     }

//     Mesh* hexagon = new Mesh(name);

//     // Modificăm modul de desenare la GL_TRIANGLES sau GL_TRIANGLE_FAN
//     hexagon->SetDrawMode(GL_TRIANGLES);
//     std::vector<unsigned int> indices = {0, 1, 2,
//                                          0, 2, 3,
//                                          0, 3, 4,
//                                          0, 4, 5,
//                                          0, 5, 6,
//                                          0, 6, 7,
//                                          0, 7, 8,
//                                          0, 8, 1,
//                                                  };

//     hexagon->InitFromData(vertices, indices);
//     return hexagon;
// }

// Mesh* object2D::CreateHeart(
//     const std::string& name,
//     glm::vec3 leftBottomCorner,
//     glm::vec3 color)
// {
//     glm::vec3 corner = glm::vec3(0, 0, 0);

//     std::vector<VertexFormat> vertices =
//     {
//         // VertexFormat(corner + glm::vec3(75, 60, 0), color),//1
//         VertexFormat(corner + glm::vec3(60, 75, 0), color),//0
//         VertexFormat(corner + glm::vec3(50, 90, 0), color),//1
//         VertexFormat(corner + glm::vec3(30, 90, 0), color),//2
//         VertexFormat(corner + glm::vec3(20, 75, 0), color),//3
//         VertexFormat(corner + glm::vec3(60, 10, 0), color),//4
//         VertexFormat(corner + glm::vec3(100, 75, 0), color),//5  
//         VertexFormat(corner + glm::vec3(90, 90, 0), color),//6
//         VertexFormat(corner + glm::vec3(70, 90, 0), color),//7
//     };

//     Mesh* heart = new Mesh(name);

//     // Modificăm modul de desenare la GL_TRIANGLES sau GL_TRIANGLE_FAN
//     heart->SetDrawMode(GL_TRIANGLES); 

//     std::vector<unsigned int> indices = {0, 1, 2,
//                                          0, 2, 3,
//                                          0, 3, 4,
//                                          0, 4, 5,
//                                          0, 5, 6,
//                                          0, 6, 7,
//     };

//     heart->InitFromData(vertices, indices);
//     return heart;
// }
