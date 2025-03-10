#include <raylib.h>
#include <iostream>
#include <raymath.h>
#include <cmath>
#include <vector>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
int star_number = 47;
int star_size = 50;  //since the star png is 50x50

//this vector aka list will contain all the star postions
std::vector<Vector2> star_coordinates;

class Stars
{
  public:
    Vector2 coordinates;
    static Texture2D star_texture;

    
    

    Stars(){ 
      coordinates = generate_random_star_coordinates();
    }

    static void load_star_texture(){
      Image star_image = LoadImage("assets/images/star.png");
      star_texture = LoadTextureFromImage(star_image);
      UnloadImage(star_image);
    }
    static void unload_star_texture(){
      UnloadTexture(star_texture);
    }

    Vector2 generate_random_coordinates()
    {
      float x = GetRandomValue(0, WINDOW_WIDTH-star_size);
      float y = GetRandomValue(0, WINDOW_HEIGHT-star_size);
      return {x,y};
    }
    
    bool is_overlapping(Vector2 star_position){
      for(const auto &star: star_coordinates){
        float dx = star_position.x - star.x;
        float dy = star_position.y - star.y;

         if(sqrt(dx*dx+dy*dy)<star_size) //this is the distance formula
          return true;

     
    }
    return false;
  }
      
    

    Vector2 generate_random_star_coordinates(){
      Vector2 position;
      do{
        position = generate_random_coordinates();
      } while (is_overlapping(position));
      
      star_coordinates.push_back(position);
      return position;
    }


    void draw_stars(){
      DrawTexture(star_texture, coordinates.x, coordinates.y, WHITE);
    }
};
Texture2D Stars::star_texture;




class Player{
public:
  const int player_width = 112;
  const int player_height = 75;
  Vector2 position = {(float)(WINDOW_WIDTH-player_width)/2,(float)(WINDOW_HEIGHT-player_height)*3/4};
  Vector2 direction = {0,0};
  static Texture2D player_texture;

  static void load_player_texture(){
    Image player_image = LoadImage("assets/images/player.png");
    player_texture = LoadTextureFromImage(player_image);
    UnloadImage(player_image);
  }

  static void unload_player_texture(){
    UnloadTexture(player_texture);
  }

  void draw_player(){
    DrawTexture(player_texture, position.x, position.y, WHITE);
  }

  
  void update_state(){
    position = Vector2Add(position,direction);
  }

  void check_for_key_events(){
    if(IsKeyDown(KEY_W) && !(position.y<=0)){direction.y = -5;}
    if(IsKeyDown(KEY_A) && !(position.x <= 0)){direction.x = -5;}
    if(IsKeyDown(KEY_D) && !(position.x+player_width >= WINDOW_WIDTH)){direction.x = 5;}
    if(IsKeyDown(KEY_S) && !(position.y+player_height >= WINDOW_HEIGHT)){direction.y = 5;}

  }
  
  bool wall_collisions(){
    if(position.x <= 0 || position.x+player_width >= WINDOW_WIDTH){return true;}
    if(position.y <= 0 || position.y+player_height >= WINDOW_HEIGHT){return true;}
    return false;
  }

};
Texture2D Player::player_texture;

int main()
{
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space shooter");
  SetTargetFPS(60);

  Stars::load_star_texture();
  Stars star[star_number]; //this creates 47 stars *wink*

  //for(int i = 0; i<(sizeof(star)/sizeof(star[0]));i++){ 
  //star[i].coordinates = star[i].generate_random_star_coordinates();
  ///}
  Player player;
  Player::load_player_texture();

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    for(int i = 0; i<(sizeof(star)/sizeof(star[0]));i++) star[i].draw_stars();
    player.draw_player();
    player.check_for_key_events();
    player.update_state();
    player.direction = {0,0};
    EndDrawing();
  }
  Stars::unload_star_texture(); 
  Player::unload_player_texture();
  
  
  CloseWindow();

  return 0;

}

