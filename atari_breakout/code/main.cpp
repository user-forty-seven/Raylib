#include <raylib.h>
#include <random> // because the raylib random numeber generator is "biased"
#include <iostream>
#include <raymath.h>


float BRICK_WIDTH = 50.0f;
float BRICK_HEIGHT = 20.0f;
float WINDOW_WIDTH = BRICK_WIDTH*BRICK_HEIGHT; //1000
float WINDOW_HEIGHT = WINDOW_WIDTH - 10*BRICK_WIDTH;// 500
int ROWS = 20;
int COLUMNS = 10;
float PADDLE_WIDTH = 50.0f;
float PADDLE_HEIGHT = 20.0f; //20,15

float last_update_time = 0;

bool interval(float time){
  float current_time = GetTime();

  if(current_time- last_update_time > time){
    last_update_time = current_time;
    return true;
  }
  return false;
  
}


class Brick{
public:

  //this is the colour array's index
  int color;

  //the colour array
  Color Red = {255,0,0,255};
  Color Orange = {255,165,0,255};
  Color Yellow = {255,255,0,255};
  Color Green = {0,255,0,255};
  Color Blue = {0,0,255,255};
  Color colors[5] = {Red, Orange, Yellow, Green, Blue};
  Vector2 position;
  

 int generate_random_color(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, (sizeof(colors)/sizeof(colors[0]))-1);
    int random_index = distrib(gen);
    return random_index;
  }
  
  Brick(){
        color = generate_random_color();
  }

};

void draw_bricks(Vector2 brick_position, Color color){
 //DrawRectangle(brick_position.x*BRICK_WIDTH + 5, brick_position.y*BRICK_HEIGHT +5, BRICK_WIDTH-10, BRICK_HEIGHT-10, color);
  DrawRectangleRounded(Rectangle{brick_position.x*BRICK_WIDTH + 3, brick_position.y*BRICK_HEIGHT +3, (float)BRICK_WIDTH-6, (float)BRICK_HEIGHT-6}, 0.77, 30, color);
}



class Paddle{
public:
  Vector2 position = {10.00,18.75}; //10.00 for the 1/2 of the screen width 18.75 for the 3/4 of the screen height
  float direction_x = 0.0f;  //since we only need to move the paddle horizontally



  void draw(){
    //DrawRectangle(WINDOW_WIDTH/2-PADDLE_WIDTH, 3*WINDOW_HEIGHT/4, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
    DrawRectangleRounded({position.x*PADDLE_WIDTH-PADDLE_WIDTH/2.0f,
      //(float)WINDOW_WIDTH/2.0f-PADDLE_WIDTH,
      //(float)3.0f*WINDOW_HEIGHT/4.0f, 
      position.y*PADDLE_HEIGHT,
      PADDLE_WIDTH, PADDLE_HEIGHT},2, 2, WHITE);
  
  }
  

  void update_state(){
   position.x += direction_x; 
  }

};



class Ball{
  public:
  Vector2 position = {10.0f,5.0f};
  Vector2 direction = {1.0f,1.0f};

  float radius = 10.0f;
  Color ball_color = WHITE;


  void draw_ball(){
    DrawCircle(position.x*50.0f,position.y*50.0f, radius, ball_color);
    
  }

  void update_state(){
    position = Vector2Add(position, direction);
  }
  
  void check_collisions_with_wall(){
    //if(position.x<= 1.0f|| position.x >= 20.0f){
    //  std::cout << "Out of bounds, x axis" << std::endl;
    //  direction.x *= -1.0f; //reverses the direction
    //}
    //if(position.y <= 1.0f || position.y >= 10.0f){
    //  std::cout << "Out of bounds, y axis" << std::endl;
    //  direction.y *= -1.0f; //again, reverses the direction
    //}
    if(position.x < 1.0f){direction.x = 1.0f;}
    if(position.x >= 20.0f){direction.x = -1.0f;}
    if(position.y < 1.0f){direction.y = 1.0;}
    if(position.y >= 10.0f){direction.y = -1.0f;}
  std::cout << "{" << position.x << "," << position.y << "}" << std::endl;
  }
};


int main(){
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Atari Breakout");
  SetTargetFPS(60);
  Brick brick[ROWS][COLUMNS];
  Paddle paddle;
  Ball ball;
  //assign the position of the bricks to the position vector and assign a random colour to each (the constructor takes care of that part)
  for(int row=0;row<ROWS;row++){
    for(int col=0;col<COLUMNS;col++){
      brick[row][col].position = {(float)row,(float)col};
    }
  }

  while(!WindowShouldClose()){
      BeginDrawing();
      ClearBackground(BLACK);

      //iterate over the bricks and draw them
      for(int row=0;row<ROWS;row++){
        for(int col=0;col<COLUMNS;col++){
            draw_bricks(brick[row][col].position, brick[row][col].colors[brick[row][col].color]);
        }
      }
    paddle.draw();
    if(interval(0.1)){
      paddle.update_state();
      ball.update_state();
 //     std::cout << paddle.position.x <<std::endl;

    }
    ball.draw_ball();
    
    //get input
    if(IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT) || paddle.position.x <= 1.0f || paddle.position.x >= 20.0f){
      paddle.direction_x = 0;
    }
    if(IsKeyDown(KEY_LEFT) && !(paddle.position.x <= 1.0f)){
        paddle.direction_x = -0.5f;
    }
    if(IsKeyDown(KEY_RIGHT) && !(paddle.position.x >= 20.0f)){
      paddle.direction_x = 0.5f;
    }

    //check for ball collions with the wall
    ball.check_collisions_with_wall();
     EndDrawing();
  }






  CloseWindow();
  return 0;
} 



