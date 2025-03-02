#include <deque> //for the snake body
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <iostream>

int CELL_SIZE = 30;
int CELL_NUMBER = 30;
int WINDOW_HEIGHT = CELL_NUMBER * CELL_SIZE;
int WINDOW_WIDTH = CELL_NUMBER * CELL_SIZE;
float offset = 50.0;

float initial_time = 0;
int score = 0;
bool is_paused = false;

// colours
Color snake = {102, 192, 33, 255};
Color background = {31, 51, 33, 255};

bool interval(float time_interval) {
  float current_time = GetTime();

  if (current_time - initial_time > time_interval) {
    initial_time = current_time;
    return true;
  }
  return false;
}

bool element_in_deque(std::deque<Vector2> user_deque, Vector2 vector) {
  for (unsigned int i = 0; i < user_deque.size(); i++) {
    if (Vector2Equals(user_deque[i], vector)) {
      return true;
    }
  }

  return false;
}

class Food {

public:
  Food() {
    position = generate_random_position();
    load_texture();
  }

  ~Food() { UnloadTexture(apple); }
  Vector2 position;

  Texture2D apple;

  // methods
  Vector2 generate_random_coordinates() {
    float x = GetRandomValue(0, CELL_NUMBER - 1);
    float y = GetRandomValue(0, CELL_NUMBER - 1);
    return {x, y};
  }

  Vector2 generate_random_position(std::deque<Vector2> snake_body = {
                                       Vector2{0, 0}}) {
    Vector2 position = generate_random_coordinates();
    while (element_in_deque(snake_body, position)) {
      position = generate_random_coordinates();
    }

    return position;
  }

  void draw_food() {
    // DrawRectangle(position.x * CELL_NUMBER, position.y * CELL_NUMBER,
    // CELL_SIZE,CELL_SIZE, RED);
    DrawTexture(apple, offset + position.x * CELL_NUMBER, offset+ position.y * CELL_NUMBER,
                snake);
  }

  void load_texture() {
    Image image_apple = LoadImage("assets/graphics/apple.png");
    apple = LoadTextureFromImage(image_apple);
    UnloadImage(image_apple);
  }
};

class Snake {

public:
  std::deque<Vector2> body = {Vector2{4, 7}, Vector2{5, 7}, Vector2{6, 7}};
  Vector2 direction = {1, 0};

  /*Snake(std::deque<Vector2> user_input = {Vector2{1,1},Vector2{2,1},
  Vector2{3,1}}){ for(unsigned int i=0; i<user_input.size();i++){
        user_input[i].x = body[i].x;
        user_input[i].y = body[i].y;
    }
  }*/

  // methods
  void draw_body() {
    for (unsigned int i = 0; i < body.size(); i++) {
      // DrawRectangle(body[i].x*CELL_NUMBER, body[i].y*CELL_NUMBER,
      // CELL_SIZE, CELL_SIZE, YELLOW);
      DrawRectangleRounded({offset + body[i].x * CELL_NUMBER, offset + body[i].y * CELL_NUMBER, (float)CELL_SIZE, (float)CELL_SIZE},0.5, 1, snake);
    }
  }

  void update_state() {
    body.pop_back();
    body.push_front(Vector2Add(direction, body[0]));
  }
  void add_segments(Vector2 food_position) {
    body.push_front(Vector2Add(direction, body[0]));
  }

  bool check_collision_food(Vector2 food_position) {
    if (Vector2Equals(food_position, body[0])) {
      return true;
    }
    return false;
  }

  bool check_collision_body() {
    std::deque<Vector2> headless_body = body;
    headless_body.pop_front();
    if (element_in_deque(headless_body, body[0]) && body.size()>=4) {
      return true;
    } else {
      return false;
    }
  }
};

class Game {
public:
  bool check_collision_wall(Vector2 snake_head) {
    if (snake_head.x < 0 || snake_head.x >= CELL_NUMBER || snake_head.y < 0 ||
        snake_head.y >= CELL_NUMBER) {
      std::cout << "body is {"  << snake_head.x <<  "," << snake_head.y << "}" << std::endl;
      return true;
    }
    return false;
  }

  void draw_score(const int &score) {
    std::string score_str = std::to_string(score);
    DrawText(score_str.c_str(), offset-2, WINDOW_HEIGHT+2*offset - 40, 20, WHITE);
  }

  void game_over(std::deque<Vector2> &snake_body, bool &is_paused) {
    snake_body = {Vector2{4, 7}, Vector2{5, 7}, Vector2{6, 7}};
    is_paused = true;
  }
};

int main() {

  InitWindow(WINDOW_WIDTH + 2*offset, WINDOW_HEIGHT + 2*offset, "Snake game");
  SetTargetFPS(60);

  Food food;
  Snake snake;
  Game game;

  while (!WindowShouldClose()) {
    BeginDrawing();
    food.draw_food();
    snake.draw_body();

    if(interval(0.2) && !is_paused){snake.update_state();}
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) &&
        snake.direction.y != 1) {
      snake.direction = {0, -1};
      is_paused = false;
    }
    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) &&
        snake.direction.y != -1) {
      snake.direction = {0, 1};
      is_paused = false;
    }
    if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) &&
        snake.direction.x != 1) {
      snake.direction = {-1, 0};
      is_paused = false;
    }
    if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) &&
        snake.direction.x != -1) {
      snake.direction = {1, 0};
      is_paused = false;
    }

    if (game.check_collision_wall(snake.body[0]) || snake.check_collision_body()) {
      game.game_over(snake.body, is_paused);
      score = 0;
    }
    if (snake.check_collision_food(food.position)) {
      snake.add_segments(food.position);
      food.position = food.generate_random_position(snake.body);
      score++;
    }
    DrawRectangleLinesEx(Rectangle{offset-5, offset-5, (float)WINDOW_WIDTH+10, (float)WINDOW_HEIGHT+10}, 5, RED);
    DrawText("Snake Game", offset-2, 15, 30, WHITE);
    game.draw_score(score);
    
    ClearBackground(background);
    EndDrawing();
  }

  CloseWindow();
}

// g++ -o main code/main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
