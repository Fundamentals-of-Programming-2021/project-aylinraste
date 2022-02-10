#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H

struct markaz
{
    double x;
    double y;
    int soldiers;
    uint32_t color;
    int rate;
    int speed;
    int max;
    int r;
    bool majoon;
    int type;
    bool on;
    int target;
};

struct sarbaz
{
    double x;
    double y;
    struct sarbaz *next;
};

struct fight
{
    struct markaz start, end;
    int s, e;
    double shib;
    int nsarbaz;
    int counter;
    struct sarbaz *head;
};

struct potion
{
    double x;
    double y;
    uint32_t color;
    int type;
    int whichone;
};

struct active
{
    int type;
    int color;
    int time;
};

struct users
{
    char name[40];
    int win;
    int lose;
    int draw;
    int score;
};
extern const int SCREEN_WIDTH ;
extern const int SCREEN_HEIGHT;
extern const int s;
extern int chosenbackground;
extern int check[50];
extern uint32_t colors[100];
extern uint32_t color[9];
extern int numberofareas, numberofplayers, number;
extern struct markaz *center;
extern struct fight *bazi;
extern struct sarbaz *soldier;
extern struct potion majoon;
extern struct active potion1, potion2;
extern bool mutee;
extern bool nist;
extern int mokhtasat[900][600];
extern int maps;
extern bool running;
extern Mix_Music *music1 ;
extern Mix_Music *music2 ;
extern bool win, lose;
extern char name[40];
extern bool hmenu, hmap, hsettings, hranking, hstart, hpause, hend;

void init();

void text(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A);

void generate_random(SDL_Renderer *renderer, double x, double y);

void makecolors ();

void find_center( double x, double y, uint32_t target);

void m0(int i, int k);

void m00(int i, int k);

void m1(int i, int k);

void m11(int i, int k);

void m2(int i, int k);

void m22(int i, int k);

void m3(int i, int k);

void m33(int i, int k);

void qheyrfaal();

void active_potion();

void bekesh (SDL_Renderer *renderer, struct markaz center[]);

void draw (SDL_Renderer *renderer, double x, double y);

void generate_random(SDL_Renderer *renderer, double x, double y);

void saveclick(double x, double y , int *start, int *end);

void faal(int i);

void generate_soldier(int c);

void addattail(struct sarbaz *head, double x0, double y0, int i);

struct sarbaz* delete_from_head(struct sarbaz* head, int i);

void ziadkon(struct sarbaz *head, int i);

int checkkon(struct sarbaz *head, int i);

int checknakon(struct sarbaz *head, int i);

void hamle(SDL_Renderer *renderer, int c, int i);

void is_same(int i, int j, struct sarbaz *headi, struct sarbaz *headj);

void randomareas (SDL_Renderer *renderer);

void makemajoon(SDL_Renderer *renderer);

void startfight(int *start, int *end);

void barkhord(SDL_Renderer *renderer, int c);

int halat0(int aval);

int halat1(int aval);

int halat2(int aval);

int halat3(int aval);

int halat4(int aval);

void enemy(int *start, int *end);

int readfile (struct users carbar[]);

void sort(FILE *scores);

void map0(SDL_Renderer *renderer);

void map1();

void map2();

void map3();

void insialize();

int map(SDL_Window *window);

#endif //UNTITLED_FUNCTIONS_H
