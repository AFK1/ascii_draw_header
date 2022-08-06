
#ifndef ASSETS
#define ASSETS

#include <SDL2/SDL.h>

typedef struct V2 { 
  int x,y;
} V2;
typedef struct V3 { 
  int x,y,z;
} V3;
typedef struct V4 { 
  int x,y,z,w;
} V4;
typedef struct V5 { 
  int x,y,z,w,h;
} V5;

#ifndef CONSTS
#define CONSTS

const SDL_Color 
  White = {255, 255, 255},
  Whiteless = {200, 200, 200},
  Red = {255, 0, 0},
  Yellow = {255, 255, 0},
  Green = {0, 255, 0},
  Cyan = {0, 255, 255},
  Blue = {0, 0, 255},
  Purple = {255, 0, 255},
  Black = {0, 0, 0},
  Grey = {122, 122, 122},
  Black_Grey = {30, 30, 30},
  Black_Blue = {0, 0, 100},
  Orange = {255, 100, 0},
  Black_Orange = {100, 50, 0};


const int CHARW = 32; // symb width
const int CHARH = 48; // symb height

//line width
const int LINEW = (((CHARW/4)+((CHARW%4)!=0))<((CHARH/6)+((CHARH%6)!=0)))?(CHARW/4)+((CHARW%4)!=0):(CHARH/6)+((CHARH%6)!=0);

const int CHARW_IN_SCREEN = 45; // number of characters in width
const int CHARH_IN_SCREEN = 20; // number of characters in height

const int SCREENW = CHARW * CHARW_IN_SCREEN;
const int SCREENH = CHARH * CHARH_IN_SCREEN; // resolution in px

const int CLEAR_COLOR[4]{0, 0, 0, 255};
#endif

typedef struct App{
  SDL_Renderer *renderer;
  SDL_Window *window;
} App;

#endif