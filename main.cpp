
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include <cmath>
#include <cstring>
#include <stdio.h>

#include "assets.hpp"
#include "draw_utils.hpp"

// Example vars
int curs_x, curs_y; // cursor pos
V2 contex_menu_pos, contex_menu_size;
bool quit = false, contex_menu = false, clicked, rclicked;


// Required vars
App app;
TTF_Font *font;

// Example function
void open_contex_menu(){
  contex_menu_size.x = 5;
  contex_menu_size.y = 3;
  contex_menu = true;
  contex_menu_pos.x = curs_x / CHARW;
  contex_menu_pos.y = curs_y / CHARH;
}

// Example function
void doInput(void){ //Simple SDL input system
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT){
      quit = true;
      exit(0);
    }else
      if (event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_ESCAPE){
          quit = true;
        }
        else if(event.key.keysym.sym == SDLK_w){
          printf("W pressed\n");
        }
    }else
      if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == SDL_BUTTON_LEFT){
          if (!clicked){
            if (contex_menu){
              contex_menu = false;
            }
          }
          clicked = true;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT){
          if (!rclicked){
            SDL_GetMouseState(&curs_x,&curs_y);
            open_contex_menu();
          }
          rclicked = true;
        }
    }else
      if (event.type == SDL_MOUSEBUTTONUP){
        if (event.button.button == SDL_BUTTON_LEFT)
          clicked = false;
        else if (event.button.button == SDL_BUTTON_RIGHT)
          rclicked = false;
    }else
      if (event.type == SDL_MOUSEMOTION){
        SDL_GetMouseState(&curs_x,&curs_y);
    }
  }
}

int main(int argc, char* argv[]) { // if windows - main() => WinMain()

  draw_init();

  app.window = SDL_CreateWindow("ascii drawer",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREENW,SCREENH,0);
  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
  font = TTF_OpenFont("path/to/file.ttf", 48);
  

  //=================Load Text====================
                                          /*text*/        /*Color*/
  SDL_Texture* quest_texture   = renderText("!",            Yellow);
  SDL_Texture* player_texture  = renderText("@",            Yellow);
  SDL_Texture* dot_texture     = renderText(".",            Grey  );
  SDL_Texture* text_texture    = renderText("text example", White );
  //=============================================
  

  while(!quit){                                   // main loop
    prepare_scene();                              // clear screen
    doInput();                                    // check inputs

    draw_line(Whiteless, 0,0,10,0);               // draw line
    draw_rect_char(dot_texture, 1, 1, 8, 3);      // draw all "."
    erase_char(2,2);                              // erase one "."
    draw_char(player_texture, 15, 10);            // draw "@"
    draw_back(Black_Blue, 10, 10);                // draw bg of "!"
    draw_char(quest_texture, 10, 10);             // draw "!"

    if (contex_menu)
      draw_contex_menu(contex_menu_pos, contex_menu_size);// draw context menu

    draw_back(White, curs_x/CHARW, curs_y/CHARH); // draw cursor

    present_scene();                              // draw next frame
  }

  
  draw_exit();                                    // clean up
  return 0;
}