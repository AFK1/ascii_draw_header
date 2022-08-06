
#ifndef DRAW_UTILS
#define DRAW_UTILS
#include <cstring>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "assets.hpp"

extern App app;
extern TTF_Font *font;
extern V2 contex_menu_pos;
extern bool contex_menu_content[8];

SDL_Texture* renderText(const char *message, SDL_Color color){
  SDL_Surface *surf = TTF_RenderText_Solid(font, message, color);
  if (surf == nullptr){
    return nullptr;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, surf);
  SDL_FreeSurface(surf);
  return texture;
}

void draw_texture(SDL_Texture *texture, int x, int y, int w, int h){ //draw image with custom size
  SDL_Rect dest{x, y, w, h};
  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
void prepare_scene(void){
  SDL_SetRenderDrawColor(app.renderer, CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]);
  SDL_RenderClear(app.renderer);
}
void present_scene(void){
  SDL_RenderPresent(app.renderer);
}


void draw_line(SDL_Color color, int x, int y, int w, int h){
  SDL_SetRenderDrawColor( app.renderer, color.r, color.g, color.b, 255 );
  if(w == 0){
    SDL_Rect rect{x*CHARW+(CHARW/2)-(LINEW/2), y*CHARH+(CHARH/2)-(LINEW/2), LINEW, h*CHARH+LINEW};
    SDL_RenderFillRect(app.renderer, &rect);
  }else{
    SDL_Rect rect{x*CHARW+(CHARW/2)-(LINEW/2), y*CHARH+(CHARH/2)-(LINEW/2), w*CHARW+LINEW, LINEW};
    SDL_RenderFillRect(app.renderer, &rect);
  }
}
void draw_rect_char(SDL_Texture* texture, int x, int y, int w, int h){
  SDL_Rect rect{x*CHARW, y*CHARH, CHARW, CHARH};
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      SDL_RenderCopy(app.renderer, texture, NULL, &rect);
      rect.x += CHARW;
    }
    rect.y += CHARH;
    rect.x = x*CHARW;
  }
}
void erase_char(int x, int y){
  SDL_SetRenderDrawColor( app.renderer, CLEAR_COLOR[0], CLEAR_COLOR[1], CLEAR_COLOR[2], CLEAR_COLOR[3]);
  SDL_Rect rect{x*CHARW, y*CHARH, CHARW, CHARH};
  SDL_RenderFillRect(app.renderer, &rect);
}
void draw_back(SDL_Color color, int x, int y){
  SDL_SetRenderDrawColor( app.renderer, color.r, color.g, color.b, 255 );
  SDL_Rect rect{x*CHARW, y*CHARH, CHARW, CHARH};
  SDL_RenderFillRect(app.renderer, &rect);
}
void draw_char(SDL_Texture* texture, int x, int y){
  draw_texture(texture, x*CHARW, y*CHARH, CHARW, CHARH);
}
void draw_char(SDL_Texture* texture, SDL_Color color, int x, int y){
  SDL_SetRenderDrawColor( app.renderer, color.r, color.g, color.b, 255 );
  SDL_Rect rect{x*CHARW, y*CHARH, CHARW, CHARH};
  SDL_RenderFillRect(app.renderer, &rect);
  draw_texture(texture, x*CHARW, y*CHARH, CHARW, CHARH);
}
void draw_rect_back(SDL_Color color, int x, int y, int w, int h){
  SDL_SetRenderDrawColor( app.renderer, color.r, color.g, color.b, 255 );
  SDL_Rect rect{x*CHARW, y*CHARH, w*CHARW, h*CHARH};
  SDL_RenderFillRect(app.renderer, &rect);
}
void draw_string(SDL_Texture* texture, const char* message, int x, int y){
  draw_texture(texture, CHARW*x,CHARH*y,CHARW*strlen(message),CHARH);
}

void draw_contex_menu(){
  draw_rect_back(Black_Blue, contex_menu_pos.x+1, contex_menu_pos.y+1, 10, 5);
  draw_line(Grey, contex_menu_pos.x+1, contex_menu_pos.y+1, 9, 0);
  draw_line(Grey, contex_menu_pos.x+1, contex_menu_pos.y+1, 0, 4);
  draw_line(Grey, contex_menu_pos.x+1, contex_menu_pos.y+5, 9, 0);
  draw_line(Grey, contex_menu_pos.x+10, contex_menu_pos.y+1, 0, 4);
}

#endif