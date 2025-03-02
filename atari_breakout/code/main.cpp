#include <raylib.h>


int main(){


  InitWindow(470, 470, "Atari Breakout");
  SetTargetFPS(60);

  while(!WindowShouldClose()){
      BeginDrawing();
      ClearBackground(RED);
      EndDrawing();
    
  }

  CloseWindow();
  return 0;
}
