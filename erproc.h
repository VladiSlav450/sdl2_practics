#ifndef ERPROC_h
#define ERPROC_h

void Init_SDL();
void Create_Window();
void Create_RenderColors();
void Init_IMG();
void LoadMedia();
void EventHandler(); // Work cycle
void Close();
SDL_Texture* loadTexture(const char *imagePath);

class GraphObject
{
protected:
    double x, y;
    int color;
public:
    GraphObject(double dx, double dy, int dcolor) : x(dx), y(dy), color(dcolor) {}
    virtual  ~GraphObject() {}
    virtual void Hide() = 0;
    virtual void Show() = 0;
    void Move(double nx, double ny); 
};

class Pixel : public GraphObject
{
public:
    Pixel(double x, double y, int col) : GraphObject(x, y, col) {} 
    virtual ~Pixel() {}
    virtual void Hide();
    virtual void Show();
};

class Circle : public GraphObject
{
    double radius;
public:
    Circle(double x, double y, double rad, int col) : GraphObject(x, y, col), radius(rad) {}
    virtual ~Circle() {}
    virtual void Hide();    
    virtual void Show();

};

class PolygonalCahin : public GraphObject
{
    struct Vertex
    {
        double dx, dy;
        Vertex *next;
    };
    Vertex *first;
public:
    PolygonalCahin(double x, double y, int col) : GraphObject( x, y, col), first(0) { AddVertex(x, y); }
    virtual ~PolygonalCahin();    
    void AddVertex(double adx, double ady);
    virtual void Show();
    virtual void Hide();
};

class Squre : public PolygonalCahin
{
public:
    Squre(double x, double y, double a, int color) : PolygonalCahin(x, y, color)
    {
        AddVertex(x, y + a);
        AddVertex(x + a, y + a);
        AddVertex(x + a, y);
        AddVertex(x, y);
    }
};

class Ractangle : public PolygonalCahin
{
    double wight, hight;
public:
    Ractangle(double x, double y, double w, double h, int color) : PolygonalCahin(x, y, color), wight(w), hight(h)
    {
        AddVertex(x, y + hight);
        AddVertex(x + wight, y + hight);
        AddVertex(x + wight, y);
        AddVertex(x, y);
    } 
};

class FillRactange : public Ractangle
{
public:
    SDL_Rect fillrect;
    FillRactange(double x, double y, double w, double h, int color) : Ractangle(x, y, w, h, color)
    {
        fillrect = { x, y, w, h};
    } 
    virtual void Show();
};

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
