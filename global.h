#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>

const int SCREEN_WIDHT = 1280;
const int SCREEN_HIGHT = 1360;

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gCurrentSurface;
enum KeyPressSurface {  KEY_PRESS_SURFACE_DEFULT,  // Key press surface constants
                        KEY_PRESS_SURFACE_UP, 
                        KEY_PRESS_SURFACE_DOWN, 
                        KEY_PRESS_SURFACE_LEFT, 
                        KEY_PRESS_SURFACE_RIGHT, 
                        KEY_PRESS_SURFACE_TOTAL  };
extern SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL]; // The image that correspond to a keypress

extern const char *gOnePathImage;
extern const char *gTwoPathImage;
extern const char *gThreePathImage;
extern const char *gFourPathImage;
extern const char *gFivePathImage;


#endif

