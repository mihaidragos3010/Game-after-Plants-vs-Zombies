#include "lab_m1/Homework1/homework1.h"
#include "lab_m1/lab3/transform2D.h"

#include <vector>
#include <string.h>
#include <map>
#include <chrono>
#include <iostream>

#include "Shapes/Shape.h"
#include "Shapes/Heart.h"
#include "Shapes/Square.h"
#include "Shapes/Rectangle.h"
#include "Shapes/Star.h"
#include "Shapes/Cannon.h"
#include "Shapes/Enemy.h"

using namespace std;
using namespace m1;
using namespace shape;

glm::vec3 m1::homework1::Board::BoardTopLeft = glm::vec3(120, 330, 0);
glm::vec3 m1::homework1::Board::BoardTopMiddle = glm::vec3(270, 330, 0);
glm::vec3 m1::homework1::Board::BoardTopRight = glm::vec3(420, 330, 0);

glm::vec3 m1::homework1::Board::BoardMiddleLeft = glm::vec3(120,180,0);
glm::vec3 m1::homework1::Board::BoardMiddle = glm::vec3(270,180,0);
glm::vec3 m1::homework1::Board::BoardMiddleRight = glm::vec3(420,180,0);

glm::vec3 m1::homework1::Board::BoardDownLeft = glm::vec3(120,30,0);
glm::vec3 m1::homework1::Board::BoardDownMiddle = glm::vec3(270,30,0);
glm::vec3 m1::homework1::Board::BoardDownRight = glm::vec3(420,30,0);

glm::vec3 m1::homework1::Board::EmptySquareLeft = glm::vec3(100,560,0);
glm::vec3 m1::homework1::Board::EmptySquareMiddleLeft = glm::vec3(250,560,0);
glm::vec3 m1::homework1::Board::EmptySquareMiddleRight = glm::vec3(400,560,0);
glm::vec3 m1::homework1::Board::EmptySquareRight = glm::vec3(550,560,0);

glm::vec3 m1::homework1::Board::StartStarsWallet = glm::vec3(800,520,0);

glm::vec3 m1::homework1::Random::lineTop = glm::vec3(1300, 30, 1);
glm::vec3 m1::homework1::Random::lineMiddle = glm::vec3(1300, 180, 1);
glm::vec3 m1::homework1::Random::lineDown = glm::vec3(1300, 330, 1);

glm::vec3 m1::homework1::Random::orange = glm::vec3(0.949f, 0.553f, 0.09f);
glm::vec3 m1::homework1::Random::blue = glm::vec3(0.09f, 0.592f, 0.949f);
glm::vec3 m1::homework1::Random::yellow = glm::vec3(0.949f, 0.925f, 0.09f);
glm::vec3 m1::homework1::Random::purple = glm::vec3(0.58f, 0.09f, 0.949f);

vector<Shape*> shapes;
Cannon *cannonClone;
int nrHearts;

bool homework1::timeCheckStars(){

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeSeconds = endTime - startTimeStars;
    if(timeSeconds.count() > 6){
        startTimeStars = std::chrono::high_resolution_clock::now();
        return true;
    }
    return false;

}

bool homework1::timesCheckEnemy(){

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeSeconds = endTime - startTimeEnemy;

    if(timeSeconds.count() >= 9){
        startTimeEnemy = std::chrono::high_resolution_clock::now();
        return true;
    }
    return false;

}

homework1::homework1(){}

homework1::~homework1(){}

void homework1::Init(){

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    startTimeStars = std::chrono::high_resolution_clock::now();
    startTimeEnemy = std::chrono::high_resolution_clock::now();

    // Add squares for the board
    float length = 120;
    shapes.push_back(new Square("SquareGreen", Board::BoardDownLeft, GREEN, length, true));
    shapes.push_back(new Square("SquareGreen", Board::BoardMiddleLeft, GREEN, length, true));
    shapes.push_back(new Square("SquareGreen", Board::BoardTopLeft, GREEN, length, true));
    shapes.push_back(new Square("SquareGreen", Board::BoardDownMiddle, GREEN, length, true));
    shapes.push_back(new Square("SquareGreen", Board::BoardMiddle, GREEN, length, true));
    shapes.push_back(new Square("SquareGreen", Board::BoardTopMiddle, GREEN, length, true));
    shapes.push_back(new Square("SquareGreen", Board::BoardDownRight, GREEN, length, true));
    shapes.push_back(new Square("SquareGreen", Board::BoardMiddleRight, GREEN, length, true));
    shapes.push_back(new Square("SquareGreen", Board::BoardTopRight, GREEN, length, true));
    AddMeshToList(shapes.back()->create());

    // Add squares empty
    shapes.push_back(new Square("SquareEmpty", Board::EmptySquareLeft, BLACK, length, false));
    shapes.push_back(new Square("SquareEmpty", Board::EmptySquareMiddleLeft, BLACK, length, false));
    shapes.push_back(new Square("SquareEmpty", Board::EmptySquareMiddleRight, BLACK, length, false));
    shapes.push_back(new Square("SquareEmpty", Board::EmptySquareRight, BLACK, length, false));
    AddMeshToList(shapes.back()->create());

    // Add stars which mean the price for the cannons
    shapes.push_back(new Star("StarGray", glm::vec3(100,520,1), GRAY, Star::SMALL));
    shapes.push_back(new Star("StarGray", glm::vec3(250,520,1), GRAY, Star::SMALL));
    shapes.push_back(new Star("StarGray", glm::vec3(290,520,1), GRAY, Star::SMALL));
    shapes.push_back(new Star("StarGray", glm::vec3(400,520,1), GRAY, Star::SMALL));
    shapes.push_back(new Star("StarGray", glm::vec3(440,520,1), GRAY, Star::SMALL));
    shapes.push_back(new Star("StarGray", glm::vec3(550,520,1), GRAY, Star::SMALL));
    shapes.push_back(new Star("StarGray", glm::vec3(590,520,1), GRAY, Star::SMALL));
    shapes.push_back(new Star("StarGray", glm::vec3(630,520,1), GRAY, Star::SMALL));
    AddMeshToList(shapes.back()->create());

    // Add rectangle
    float width = 70;
    float height = 420;
    shapes.push_back(new Rectangle("Rectangle", glm::vec3(20,30,-1), RED, width, height));
    AddMeshToList(shapes.back()->create());

    // Add hearts
    shapes.push_back(new Heart("Heart", glm::vec3(800,560,0), RED));
    shapes.push_back(new Heart("Heart", glm::vec3(950,560,0), RED));
    shapes.push_back(new Heart("Heart", glm::vec3(1100,560,0), RED));
    AddMeshToList(shapes.back()->create());
    nrHearts = 3;

    // Add cannons
    shapes.push_back(new Cannon("Cannon",  Board::EmptySquareLeft, ORANGE));
    AddMeshToList(shapes.back()->create());
    shapes.push_back(new Cannon("Cannon",  Board::EmptySquareMiddleLeft, BLUE));
    AddMeshToList(shapes.back()->create());
    shapes.push_back(new Cannon("Cannon",  Board::EmptySquareMiddleRight, YELLOW));
    AddMeshToList(shapes.back()->create());
    shapes.push_back(new Cannon("Cannon",  Board::EmptySquareRight, PURPLE));
    AddMeshToList(shapes.back()->create());

    Star *star;
    star = new Star("Star", glm::vec3(0, 0, 0), ORANGE, Star::BIG);
    AddMeshToList(star->create());
    star = new Star("Star", glm::vec3(0, 0, 0), BLUE, Star::BIG);
    AddMeshToList(star->create());
    star = new Star("Star", glm::vec3(0, 0, 0), YELLOW, Star::BIG);
    AddMeshToList(star->create());
    star = new Star("Star", glm::vec3(0, 0, 0), PURPLE, Star::BIG);
    AddMeshToList(star->create());
}

void homework1::FrameStart(){

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.302f, 0.275f, 0.271f, 0.8f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    if(timeCheckStars()){

        for(int i=-1; i<rand()%4; i++){
            shapes.push_back(new Star("Star", Random::randomOnMap(), ROSE, Star::BIG));
        } 
        AddMeshToList(shapes.back()->create());   

    }

    if(timesCheckEnemy()){

        shapes.push_back(new Enemy("Enemy", Random::randomLine(), Random::randomColor()));
        AddMeshToList(shapes.back()->create());

    }

    for(int i = 0; i < shapes.size()-1; i++){
        for(int j = i+1; j < shapes.size(); j++){
            Shape *shape1 = shapes[i];
            Shape *shape2 = shapes[j];
 
            if(shape1->getColor() == shape2->getColor() && shape1->getLocation()[1] == shape2->getLocation()[1]){
                if(Is_it_a_cannon(shape1) && Is_it_a_enemy(shape2) && shape1->getLocation()[0] < shape2->getLocation()[0]){
                    Cannon *cannon = dynamic_cast<Cannon*>(shape1);
                    if(shape2->getAnimationType() == Shape::DESTRUCTION) cannon->stopShooting();
                    if(shape2->getAnimationType() == Shape::ACTION) cannon->startShooting();
                }

                if(Is_it_a_enemy(shape1) && Is_it_a_cannon(shape2) && shape1->getLocation()[0] > shape2->getLocation()[0]){
                    Cannon *cannon = dynamic_cast<Cannon*>(shape2);
                    if(shape1->getAnimationType() == Shape::DESTRUCTION) cannon->stopShooting();
                    if(shape1->getAnimationType() == Shape::ACTION) cannon->startShooting();
                }
            }

            if(distanceBetweenPoints(shape1->getLocation(), shape2->getLocation()) < 60 && thereIs(shape2)){

                if(Is_it_a_star(shape1) && Is_it_a_enemy(shape2) && shape1->getColor() == shape2->getColor()){
                    shape1->collision();
                    shape2->collision();
                    continue;
                }

                if(Is_it_a_star(shape2) && Is_it_a_enemy(shape1) && shape1->getColor() == shape2->getColor()){
                    shape1->collision();
                    shape2->collision();
                    continue;
                }

                if(Is_it_a_cannon(shape1) && Is_it_a_enemy(shape2)){
                    shape1->collision();
                    continue;
                }

                if(Is_it_a_enemy(shape1) && Is_it_a_cannon(shape2)){
                    shape2->collision();
                    continue;
                }

            }
        }
    }

}


void homework1::Update(float deltaTimeSeconds){

    if(cannonClone != NULL){
        modelMatrix = cannonClone->animation(deltaTimeSeconds);
        RenderMesh2D(cannonClone->create(),shaders["VertexColor"], modelMatrix);
    }

    for(int i = 0; i < shapes.size(); i++){

        Shape *shape = shapes[i];

        if(shape->drawOnScreen()){
            modelMatrix = shape->animation(deltaTimeSeconds);
            RenderMesh2D(meshes[shape->getNameMesh()], shaders["VertexColor"], modelMatrix);
            continue;
        }

        shapes.erase(shapes.begin()+i);
        
    }

    Board::updateBoard(shapes);
}


void homework1::FrameEnd()
{
    if(nrHearts == 0)
        exit(0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void homework1::OnInputUpdate(float deltaTime, int mods)
{
}


void homework1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void homework1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void homework1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if(cannonClone == nullptr) return;

    mouseY = 720 - mouseY;
    cannonClone->setLocation(glm::vec3(mouseX-OffsetShapesX, mouseY-OffsetShapesY, 0));

}


void homework1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    mouseY = 720 - mouseY;
    for(Shape *shape : shapes){

        if(shape->distance(mouseX, mouseY)){

            if(Is_it_a_star(shape) && shape->getColor() == ROSE && button == 1){

                shape->setAnimationType(Shape::COMPLETED);
                shapes.push_back(new Star("Star", Board::StartStarsWallet, GOLD, Star::SMALL));
                AddMeshToList(shapes.back()->create());
                Board::StartStarsWallet += glm::vec3(50, 0, 0);

            }

            if(Is_it_a_cannon(shape) && Board::isOnEmptiesSquares(shape->getLocation()) && button == 1){

                cannonClone = new Cannon("CannonClone", glm::vec3(mouseX-OffsetShapesX, mouseY-OffsetShapesY, 0), shape->getColor());

            }

            if(Is_it_a_cannon(shape) && Board::isOnBoard(shape->getLocation()) && button == 2){
                
                shape->setAnimationType(Shape::DESTRUCTION);

            }

        }

    }
    
}


void homework1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods){
    
    if(cannonClone == nullptr) return;

    if(cannonClone->getPrice() > Star::nrStarsWallet){ cannonClone = nullptr; return;}

    mouseY = 720 - mouseY;
    glm::vec3 location = glm::vec3(mouseX - OffsetShapesX, mouseY - OffsetShapesY, 0);
    if(!Board::checkPutOnBoard(location)){ cannonClone = nullptr; return;}

    Star::deleteStarsWallet(cannonClone->getPrice());
    Board::StartStarsWallet -= glm::vec3(50*cannonClone->getPrice(), 0, 0);

    shapes.push_back(new Cannon("Cannnon", Board::getClosestBoard(location), cannonClone->getColor()));
    AddMeshToList(shapes.back()->create());

    cannonClone->setAnimationType(Shape::COMPLETED);
    cannonClone = nullptr;
}


void homework1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void homework1::OnWindowResize(int width, int height)
{
}
