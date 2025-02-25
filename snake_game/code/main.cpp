#include <raylib.h>


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
            int x = GetRandomValue(0,CELL_NUMBER);
            int y = GetRandomValue(0, CELL_NUMBER);
        
            return {x,y};
        }

        void draw_food(){
            DrawRectangle(position.x*CELL_NUMBER, position.y*CELL_NUMBER, CELL_SIZE, CELL_SIZE, RED);
        }

};


int main(){
    
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Snake game");
    SetTargetFPS(60);

    Food food;


    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        food.draw_food();
        EndDrawing();

    }
    
    CloseWindow();

}

//g++ -o main code/main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11