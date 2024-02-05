#pragma once
#include <chrono>
#include <random>
#include <vector>

#include "components/simple_scene.h"

#include "Shapes/Shape.h"
#include "Shapes/Heart.h"
#include "Shapes/Square.h"
#include "Shapes/Rectangle.h"
#include "Shapes/Star.h"
#include "Shapes/Cannon.h"
#include "Shapes/Enemy.h"

#define Is_it_a_star(shape) dynamic_cast<Star *>(shape)
#define Is_it_a_cannon(shape) dynamic_cast<Cannon *>(shape)
#define Is_it_a_enemy(shape) dynamic_cast<Enemy *>(shape)

#define distanceBetweenPoints(location1, location2) sqrt(pow(location1[0] - location2[0], 2) + pow(location1[1] - location2[1], 2))
#define isFree(BoardSquare) (BoardSquare[2] != -1)
#define thereIs(shape) shape->getNameShape() != ""

namespace m1
{
    class homework1 : public gfxc::SimpleScene
    {
    public:
        homework1();
        ~homework1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        bool timeCheckStars();
        bool timesCheckEnemy();

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        
        std::chrono::time_point<std::chrono::high_resolution_clock> startTimeStars;
        std::chrono::time_point<std::chrono::high_resolution_clock> startTimeEnemy;

        struct Board {

            static glm::vec3 BoardTopLeft, BoardTopMiddle, BoardTopRight;
            static glm::vec3 BoardMiddleLeft, BoardMiddle, BoardMiddleRight;
            static glm::vec3 BoardDownLeft, BoardDownMiddle, BoardDownRight;

            static glm::vec3 EmptySquareLeft, EmptySquareMiddleLeft, EmptySquareMiddleRight, EmptySquareRight;

            static glm::vec3 StartStarsWallet;

            static bool isOnEmptiesSquares(glm::vec3 location){

                if(distanceBetweenPoints(location, EmptySquareLeft) < 60) return true;
                if(distanceBetweenPoints(location, EmptySquareMiddleLeft) < 60) return true;
                if(distanceBetweenPoints(location, EmptySquareMiddleRight) < 60) return true;
                if(distanceBetweenPoints(location, EmptySquareRight) < 60) return true;

                return false;
            }

            static bool isOnBoard(glm::vec3 location){

                if(distanceBetweenPoints(location, BoardTopLeft) < 60) return true;
                if(distanceBetweenPoints(location, BoardTopMiddle) < 60) return true;
                if(distanceBetweenPoints(location, BoardTopRight) < 60) return true;
                if(distanceBetweenPoints(location, BoardMiddleLeft) < 60) return true;
                if(distanceBetweenPoints(location, BoardMiddle) < 60) return true;
                if(distanceBetweenPoints(location, BoardMiddleRight) < 60) return true;
                if(distanceBetweenPoints(location, BoardDownLeft) < 60) return true;
                if(distanceBetweenPoints(location, BoardDownMiddle) < 60) return true;
                if(distanceBetweenPoints(location, BoardDownRight) < 60) return true;

                return false;
            }

            static bool checkPutOnBoard(glm::vec3 location){

                if(distanceBetweenPoints(location, BoardTopLeft) < 60 && isFree(BoardTopLeft)) return true;
                if(distanceBetweenPoints(location, BoardTopMiddle) < 60 && isFree(BoardTopMiddle)) return true;
                if(distanceBetweenPoints(location, BoardTopRight) < 60 && isFree(BoardTopRight)) return true;
                if(distanceBetweenPoints(location, BoardMiddleLeft) < 60 && isFree(BoardMiddleLeft)) return true;
                if(distanceBetweenPoints(location, BoardMiddle) < 60 && isFree(BoardMiddle)) return true;
                if(distanceBetweenPoints(location, BoardMiddleRight) < 60 && isFree(BoardMiddleRight)) return true;
                if(distanceBetweenPoints(location, BoardDownLeft) < 60 && isFree(BoardDownLeft)) return true;
                if(distanceBetweenPoints(location, BoardDownMiddle) < 60 && isFree(BoardDownMiddle)) return true;
                if(distanceBetweenPoints(location, BoardDownRight) < 60 && isFree(BoardDownRight)) return true;

                return false;
            }

            static glm::vec3 getClosestBoard(glm::vec3 location){

                if(distanceBetweenPoints(location, BoardTopLeft) < 60){BoardTopLeft[2] = -1; return BoardTopLeft;}
                if(distanceBetweenPoints(location, BoardTopMiddle) < 60){BoardTopMiddle[2] = -1; return BoardTopMiddle;}
                if(distanceBetweenPoints(location, BoardTopRight) < 60){BoardTopRight[2] = -1; return BoardTopRight;}
                if(distanceBetweenPoints(location, BoardMiddleLeft) < 60){BoardMiddleLeft[2] = -1; return BoardMiddleLeft;}
                if(distanceBetweenPoints(location, BoardMiddle) < 60){BoardMiddle[2] = -1; return BoardMiddle;}
                if(distanceBetweenPoints(location, BoardMiddleRight) < 60){BoardMiddleRight[2] = -1; return BoardMiddleRight;}
                if(distanceBetweenPoints(location, BoardDownLeft) < 60){BoardDownLeft[2] = -1; return BoardDownLeft;}
                if(distanceBetweenPoints(location, BoardDownMiddle) < 60){BoardDownMiddle[2] = -1; return BoardDownMiddle;}
                if(distanceBetweenPoints(location, BoardDownRight) < 60){BoardDownRight[2] = -1; return BoardDownRight;}

                return glm::vec3(-1, -1, -1);
            }

            static void updateBoard(std::vector<shape::Shape*> &shapes){

                BoardTopLeft[2] = 0;
                BoardTopMiddle[2] = 0;
                BoardTopRight[2] = 0;
                BoardMiddleLeft[2] = 0;
                BoardMiddle[2] = 0;
                BoardMiddleRight[2] = 0;
                BoardDownLeft[2] = 0;
                BoardDownMiddle[2] = 0;
                BoardDownRight[2] = 0;

                for(shape::Shape *shape : shapes){
                    
                    if(distanceBetweenPoints(shape->getLocation(), BoardTopLeft) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardTopLeft[2] = -1;
                    if(distanceBetweenPoints(shape->getLocation(), BoardTopMiddle) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardTopMiddle[2] = -1;
                    if(distanceBetweenPoints(shape->getLocation(), BoardTopRight) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardTopRight[2] = -1;
                    if(distanceBetweenPoints(shape->getLocation(), BoardMiddleLeft) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardMiddleLeft[2] = -1;
                    if(distanceBetweenPoints(shape->getLocation(), BoardMiddle) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardMiddle[2] = -1;
                    if(distanceBetweenPoints(shape->getLocation(), BoardMiddleRight) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardMiddleRight[2] = -1;
                    if(distanceBetweenPoints(shape->getLocation(), BoardDownLeft) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardDownLeft[2] = -1;
                    if(distanceBetweenPoints(shape->getLocation(), BoardDownMiddle) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardDownMiddle[2] = -1;
                    if(distanceBetweenPoints(shape->getLocation(), BoardDownRight) < 60 && dynamic_cast<shape::Cannon*>(shape)) BoardDownRight[2] = -1;

                }
            }

        };
        
        struct Random {

            static glm::vec3 lineTop;
            static glm::vec3 lineMiddle;
            static glm::vec3 lineDown;

            static glm::vec3 orange;
            static glm::vec3 blue;
            static glm::vec3 yellow;
            static glm::vec3 purple;

            static glm::vec3 randomLine(){

                int random = rand()%3;
                if(random == 2) return lineTop;
                if(random == 1) return lineMiddle;
                return lineDown;

            }

            static glm::vec3 randomColor(){

                int random = rand()%4;
                if(random == 3) return orange;
                if(random == 2) return blue;
                if(random == 1) return yellow;
                return purple;

            }

            static glm::vec3 randomOnMap(){
                return glm::vec3(rand()%1100, rand()%500, 0);
            }

        };

    };
}   // namespace m1
