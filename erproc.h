#ifndef ERPROC_h
#define ERPROC_h


bool Init(); // start SDL and creat window
bool Init_IMG();
SDL_Surface* LoadOneSurface(const char *image); // Load one image
bool LoadAllMedia(); // Loads all media
void EventHandler(); // Обработчик событий
void Close(); // Free media and shuts down SDL

#endif
