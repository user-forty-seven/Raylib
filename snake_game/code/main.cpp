#include <raylib.h>


int main(){

    InitWindow(300,300,"Window");
    SetTargetFPS(60);


    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();

    }
    
    CloseWindow();

}