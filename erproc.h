#ifndef ERPROC_h
#define ERPROC_h

void Init_SDL();
void Create_Window();
void Create_RenderColors();
void Init_IMG();
void LoadMedia();
void EventHandler();
void Close();
SDL_Texture* loadTexture(const char *imagePath);

class FuExeption
{
    int err_code;
    char *comment;
    char *get_errorSDL;
public:
    FuExeption(const char *comment, const char *get_errorSDL);
    FuExeption(const FuExeption& other);
    ~FuExeption();
    const char *GetComment() const { return comment; }
    const char *Get_ErrorSDL() const { return get_errorSDL; }
    int GetErrno() const { return err_code; }
    static char *strdup(const char *str);
};

#endif
