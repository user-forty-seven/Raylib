#include <raylib.h>
#include <deque> //for the snake body

int CELL_SIZE = 30;
int CELL_NUMBER = 30;
int WINDOW_HEIGHT = CELL_NUMBER*CELL_SIZE;
int WINDOW_WIDTH = CELL_NUMBER*CELL_SIZE;


class Food{

    public:
        Food(){
            position = generate_random_position();
        }

        Vector2 position;

        //methods
        Vector2 generate_random_position(){
            float x = GetRandomValue(0,CELL_NUMBER-1);
            float y = GetRandomValue(0, CELL_NUMBER-1);
            return {x, y};
        }

        void draw_food(){
            DrawRectangle(position.x*CELL_NUMBER, position.y*CELL_NUMBER, CELL_SIZE, CELL_SIZE, RED);
            
        }

};


class Snake{

    public:
        std::deque<Vector2> body = {Vector2{4,7}, Vector2{5,7}, Vector2{6,7}};

        
        //methods
        void draw_body(){
            for(unsigned int i = 0; i<body.size(); i++){
                //DrawRectangle(body[i].x*CELL_NUMBER, body[i].y*CELL_NUMBER, CELL_SIZE, CELL_SIZE, YELLOW);
                DrawRectangleRounded({body[i].x*CELL_NUMBER, body[i].y*CELL_NUMBER, (float) CELL_SIZE, (float) CELL_SIZE}, 0.5, 1, BLUE);
            }
        }

};

int main(){
    
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Snake game");
    SetTargetFPS(60);

    Food food;
    Snake snake;


    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        food.draw_food();
        snake.draw_body();
        EndDrawing();

    }
    
    CloseWindow();

}

//g++ -o main code/main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11