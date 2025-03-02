#include <raylib.h>
#include <iostream>

int BRICK_WIDTH = 50;
int BRICK_HEIGHT = 30;
int WINDOW_WIDTH = BRICK_WIDTH*BRICK_HEIGHT;
int WINDOW_HEIGHT = WINDOW_WIDTH - 10*BRICK_WIDTH;
int ROWS = 30;
int COLUMNS = 20;



class Brick{
public:



  int color;

  Color Red = {255,0,0,255};
  Color Orange = {255,165,0,255};
  Color Yellow = {255,255,0,255};
  Color Green = {0,255,0,255};
  Color Blue = {0,0,255,255};
  Color colors[5] = {Red, Orange, Yellow, Green, Blue};
  Vector2 position;
  

 int generate_random_color(){
    int random_index = GetRandomValue(0, (sizeof(colors)/sizeof(colors[0]))-1);
    return random_index;
  }
  
  Brick(){
        color = generate_random_color();
  }

};

void draw_bricks(Vector2 brick_position, Color color){
 DrawRectangle(brick_position.x*BRICK_WIDTH + 5, brick_position.y*BRICK_HEIGHT +5, BRICK_WIDTH-10, BRICK_HEIGHT-10, color);
}



int main(){


  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Atari Breakout");
  SetTargetFPS(60);
  Brick brick[ROWS][COLUMNS];

  for(int row=0;row<ROWS;row++){
    for(int col=0;col<COLUMNS;col++){
      brick[row][col].position = {(float)row,(float)col};
    }
  }

  while(!WindowShouldClose()){
      BeginDrawing();
      ClearBackground(BLACK);
      for(int row=0;row<ROWS;row++){
        for(int col=0;col<COLUMNS;col++){
            draw_bricks(brick[row][col].position, brick[row][col].colors[brick[row][col].color]);
        }
      }
      EndDrawing();
    
  }



  CloseWindow();
  return 0;
} 



