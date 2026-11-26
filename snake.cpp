#include <raylib.h>
#include "snake.hpp"
#include <string>

void game(){
    std::vector<Food> foods(5);
    Snake snake;
    double LastTime = GetTime();
    double TimeInterval=0.15;
    while (!WindowShouldClose()){
        if (!snake.gameOver){
            snake.CheckCollision();
            if (IsKeyDown(KEY_W) && !snake.turnedThisStep){
                snake.Up();
                snake.turnedThisStep=true;
            }
            if (IsKeyDown(KEY_S)&& !snake.turnedThisStep){
                snake.Down();
                snake.turnedThisStep=true;
            }
            if (IsKeyDown(KEY_A)&& !snake.turnedThisStep){
                snake.Left();
                snake.turnedThisStep=true;
            }
            if (IsKeyDown(KEY_D)&& !snake.turnedThisStep){
                snake.Right();
                snake.turnedThisStep=true;
            }
            if ((GetTime()-LastTime)>=TimeInterval){
                snake.Move();
                snake.turnedThisStep=false;
                LastTime=GetTime();
            }
            for (auto& food: foods){
                checkEaten(food,snake);
            }
            BeginDrawing();
            ClearBackground({100, 156, 27,255});
            for (auto& food: foods){
                food.Draw();
            }
            snake.Draw();
            EndDrawing();
        }
        if (snake.gameOver){
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("GAME OVER!",80,150,100,RED);
            DrawText("SCORE",200,250,100,BLUE);
            Rectangle retrybutton={240,500,300,100};
            Vector2 mousepos = GetMousePosition();
            DrawRectangle(240,500,300,100,GREEN);
            DrawText("RETRY",260,520,75,YELLOW);
            DrawText(std::to_string(snake.length).c_str(),350,350,100,ORANGE);
            if (CheckCollisionPointRec(mousepos,retrybutton) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                EndDrawing();
                return;
            }
            else{
                EndDrawing();
            }
        }
    }

    CloseWindow();
}

int main(){
    InitWindow(25*30,25*30,"Snake Game");
    SetTargetFPS(144);
    while (true){
        game();
    }
}