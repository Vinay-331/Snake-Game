#pragma once
#include <raylib.h>
#include <vector>

class Snake;
class Food;

class Food{
    public:
    int x;
    int y;
    Texture2D apple;
    void Draw(){
        DrawTexture(apple,x*30,(y*30)-2,WHITE);
    }

    void FoodRandomise(Snake& snake);

    Food(){
        x=GetRandomValue(1,24);
        y=GetRandomValue(1,24);
        Image image = LoadImage("Graphics/Apple.png");
        ImageResize(&image,30,30);
        apple = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~Food(){
        UnloadTexture(apple);
    }
};


class Snake{
    public:
    int x;
    int y;
    int left;
    int right;
    int up;
    int down;
    int length;
    bool gameOver;
    bool turnedThisStep;
    Texture2D target;
    std::vector<std::vector<int>> body;
    void Draw(){
        DrawTexture(target,body[0][0]*30,body[0][1]*30,WHITE);
        DrawRectangle(body[1][0]*30,body[1][1]*30,30,30,YELLOW);
        for (int i=2;i<=length;i++){
            DrawRectangle(body[i][0]*30,body[i][1]*30,30,30,BLUE);
        }
    }
    void Up(){
        if (down!=1){
            right=0;
            left=0;
            up=1;
            down=0;
        }
    }
    void Down(){
        if (up!=1){
            right=0;
            left=0;
            up=0;
            down=1;
        }
    }
    void Left(){
        if (right!=1){
            right=0;
            left=1;
            up=0;
            down=0;
        }
    }
    void Right(){
        if (left!=1){
            right=1;
            left=0;
            up=0;
            down=0;
        }
    }

    void Move(){
        for (int i = length;i>=1;i--){
            body[i][0]=body[i-1][0];
            body[i][1]=body[i-1][1];
        }
        body[0][0]+=right;
        body[0][0]-=left;
        body[0][1]+=down;
        body[0][1]-=up;

    }
    bool CheckCollision(){
        int index=2;
        for (index;index<=length;index++){
            if ( (body[index][0]==body[1][0] && body[index][1]==body[1][1]) || ( (body[1][0]>=25) || (body[1][0]<=0) ) || ( (body[1][1]>=25) || (body[1][1]<=0) ) ) {
                gameOver=true;
                return true;
            }
        }
        return false;
    }
    Snake(){
        right=1;
        left=0;
        up=0;
        down=0;
        length=3;
        x=13;
        y=13;
        turnedThisStep=false;
        gameOver=false;
        body = {{14,13},{13,13},{12,13},{11,13}};
        Image image=LoadImage("Graphics/Target.png");
        ImageResize(&image,30,30);
        target=LoadTextureFromImage(image);
        UnloadImage(image);
    }
    ~Snake(){
        UnloadTexture(target);
    }
};
void checkEaten(Food& food, Snake& snake){
    if (food.x==snake.body[1][0] && food.y==snake.body[1][1]){
        snake.body.push_back(snake.body.back());
        snake.length++;
        food.FoodRandomise(snake);
    }
}

void Food::FoodRandomise(Snake& snake){
    bool onSnake;
    do {
        onSnake=false;
        x=GetRandomValue(1,24);
        y=GetRandomValue(1,24);
        for (const auto& segment:snake.body){
            if (segment[0]==x && segment[1]==y){
                onSnake=true;
                break;
            }
        }
    } while (onSnake);
}
