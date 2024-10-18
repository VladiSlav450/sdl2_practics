#include "global.h"

SDL_Window* gWindow = NULL; // Окно в котором будем выполнять рендеринг
SDL_Surface* gScreenSurface = NULL; // Surface contained by the window
SDL_Surface* gCurrentSurface = NULL; // Cureent displayed image
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL] = { NULL };

const char *gOnePathImage = "/home/vlad/Изображения/first_blood.jpg";
const char *gTwoPathImage = "/home/vlad/Изображения/Dasha_Travel.jpg";
const char *gThreePathImage = "/home/vlad/Изображения/Look_me.jpg";
const char *gFourPathImage = "/home/vlad/Изображения/Apple.jpg";
const char *gFivePathImage = "/home/vlad/Изображения/Durov.jpg";

