// file: global.h

#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>

const int SCREEN_WIDHT = 1280;
const int SCREEN_HIGHT = 920;


extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;

enum Colors { one_col = 255, two_col = 255, three_col = 255, four_col = 255 };


extern const char *gOnePathImage;
extern const char *gTwoPathImage;
extern const char *gThreePathImage;
extern const char *gFourPathImage;
extern const char *gFivePathImage;

#endif

