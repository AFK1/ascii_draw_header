
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include <cmath>
#include <cstring>
#include <stdio.h>

#include "assets.hpp"
#include "draw_utils.hpp"

int curs_x, curs_y;
int menu_selected = 0, menu_clicked = 0;
V2 contex_menu_pos, contex_menu_size;

int map[CHARW_IN_SCREEN][CHARH_IN_SCREEN];
Entitys entitys;


App app;
bool quit = false, menu = true, contex_menu = false, clicked, rclicked, contex_menu_content[8];
TTF_Font *font;
SDL_Texture* menu_texture[9];

int menu_scene();
void draw_back(int x, int y, SDL_Color color);
void open_contex_menu();

void doInput(void){
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT){
      quit = true;
      exit(0);
    }else
      if (event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_ESCAPE){
          menu_selected = 0; menu_clicked = 0;
          menu = true;
          menu_scene();
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

void doMenuInput(void){
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
          menu_selected--;
        }
        else if(event.key.keysym.sym == SDLK_s){
          menu_selected++;
        }
        else if(event.key.keysym.sym == SDLK_SPACE){
          menu_clicked = menu_selected;
        }
    }else
      if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == SDL_BUTTON_LEFT)
        if (!clicked) {
          clicked = true;
          SDL_GetMouseState(&curs_x,&curs_y);
          if(curs_x/CHARW > 0 && curs_x/CHARW < 13){
            if (curs_y/CHARH == 1) {
              if (menu_selected == 1) menu_clicked = 1; else menu_selected = 1;
            }else if (curs_y/CHARH == 2) {
              if (menu_selected == 2) menu_clicked = 2; else menu_selected = 2;
            }else if (curs_y/CHARH == 3) {
              if (menu_selected == 3) menu_clicked = 3; else menu_selected = 3;
            }else if (curs_y/CHARH == 5) {
              if (menu_selected == 4) menu_clicked = 4; else menu_selected = 4;
            }else menu_selected = 0;
          } else menu_selected = 0;
        }
    }else
      if (event.type == SDL_MOUSEBUTTONUP){
        if (event.button.button == SDL_BUTTON_LEFT)
          clicked = false;
    }else
      if (event.type == SDL_MOUSEMOTION){
        SDL_GetMouseState(&curs_x,&curs_y);
    }
  }
}

void open_contex_menu(){
  contex_menu_size.x = 5;
  contex_menu_size.y = 2;
  contex_menu = true;
  contex_menu_pos.x = curs_x / CHARW;
  contex_menu_pos.y = curs_y / CHARH;
}

int menu_scene(){
  int start_state = 0;
  while(!quit && menu){
    prepare_scene();
    doMenuInput();

    if (menu_selected == 1) {
      draw_rect_back(White, 0, 1, strlen(">ascii drawer")+2, 1);
      draw_string(menu_texture[1], ">ascii drawer", 1, 1);
    } else draw_string(menu_texture[0], "ascii drawer", 1, 1);

    if (menu_selected == 2) {
      draw_rect_back(White, 0, 2, strlen(">start")+2, 1);
      draw_string(menu_texture[3], ">start", 1, 2);
    } else draw_string(menu_texture[2], "start", 1, 2);

    if (menu_selected == 3) {
      draw_rect_back(White, 0, 3, strlen(">load")+2, 1);
      draw_string(menu_texture[5], ">load", 1, 3);
    } else draw_string(menu_texture[4], "load", 1, 3);

    if (menu_selected == 4) {
      draw_rect_back(White, 0, 5, strlen(">exit")+2, 1);
      draw_string(menu_texture[7], ">exit", 1, 5);
    } else draw_string(menu_texture[6], "exit", 1, 5);
    
    draw_string(menu_texture[8], "by sergwest", CHARW_IN_SCREEN-strlen("by sergwest"),CHARH_IN_SCREEN-1);
    draw_back(White, curs_x/CHARW, curs_y/CHARH);

    if (menu_clicked != 0) {
      if (menu_clicked == 1) {
        menu_clicked = 0;
      } else if (menu_clicked == 2) {
        start_state = 1;
        menu = false;
      } else if (menu_clicked == 3) {
        start_state = 2;
        //Load script here
        menu = false;
      } else if (menu_clicked == 4) {
        quit = true;
        menu = false;
      }
    }

    present_scene();
  }
  return menu_clicked;
}

int main(int argc, char* argv[]) { // if windows - main() => WinMain()
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  TTF_Init();

  app.window = SDL_CreateWindow("ascii drawer",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREENW,SCREENH,0);
  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
  font = TTF_OpenFont("assets/C64_Pro_Mono-STYLE.ttf", 48);
    
#ifdef DEBUG
  if (app.window == NULL) {
    return 1;
  }
  if (app.renderer == NULL) {
    return 1;
  }
#endif
  SDL_ShowCursor(SDL_DISABLE);

  //===============Load Textures==================
  SDL_Texture* quest_texture = renderText("!", Yellow);
  SDL_Texture* player_texture = renderText("@", Yellow);
  SDL_Texture* dot_texture = renderText(".", Grey);
  //==============================================
  //=================Load Text====================
  menu_texture[0] = renderText("ascii drawer", White);
  menu_texture[1] = renderText(">ascii drawer", Black);
  menu_texture[2] = renderText("start", White);
  menu_texture[3] = renderText(">start", Black);
  menu_texture[4] = renderText("load", White);
  menu_texture[5] = renderText(">load", Black);
  menu_texture[6] = renderText("exit", White);
  menu_texture[7] = renderText(">exit", Black);
  menu_texture[8] = renderText("by sergwest", Grey);
  //=============================================
    
  int start = menu_scene(); // open main menu
  if (start == 4) { // if select exit
    quit = true;
  }else{
    for (int i = 0; i < 10; ++i) {
      map[i][0] = map_state::wall;
    }
  }

  while(!quit){ //main loop
    prepare_scene();
    doInput(); //check inputs

    draw_line(Whiteless, 0,0,10,0);               //draw line
    draw_rect_char(dot_texture, 1, 1, 8, 3);      //draw all "."
    erase_char(2,2);                              //erase "."
    draw_char(player_texture, 15, 10);            //draw "@"
    draw_back(Black_Blue, 10, 10);                //draw bg of "!"
    draw_char(quest_texture, 10, 10);             //draw "!"

    if (contex_menu)
      draw_contex_menu();                         //draw context menu

    draw_back(White, curs_x/CHARW, curs_y/CHARH); //draw cursor

    present_scene();
  }

  // Clean up
  SDL_DestroyWindow(app.window);
  TTF_CloseFont(font);
  SDL_Quit();
  return 0;
}