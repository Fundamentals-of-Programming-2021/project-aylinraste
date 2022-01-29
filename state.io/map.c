#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct markaz
{
    double x;
    double y;
    int color;
};

const int FPS = 60;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int s=50;
int numberofareas, numberofplayers, number=0;
struct markaz *center;
int mokhtasat[900][600]={0};

#ifdef main
#undef main
#endif
void generate_random(SDL_Renderer *renderer, double x, double y);

void find_center( double x, double y)
{
    center[number].x=x+0.5*s* sqrt(3);
    center[number].y=y-0.5*s;
    mokhtasat[(int)x][(int)y]++;
}

void draw (SDL_Renderer *renderer, double x, double y)
{
    uint32_t color[5]={0xffccb5fc , 0xffaaaa00 , 0xff00ffff , 0xffff00ff, 0xff6b6d6e};
    uint32_t target=color[rand()%5];
    boxColor(renderer, x, y, x+s* sqrt(3), y+s, target);
    filledTrigonColor(renderer, x, y, x+s/2* sqrt(3), y-s/2, x+s* sqrt(3), y, target);
    filledTrigonColor(renderer, x, y+s, x+s/2* sqrt(3), y+s+s/2, x+s* sqrt(3), y+s, target);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, x, y, x+s*0.5* sqrt(3), y-s/2);
    SDL_RenderDrawLine(renderer, x+s* sqrt(3), y, x+s*0.5* sqrt(3), y-s/2);
    SDL_RenderDrawLine(renderer, x, y, x, y+s);
    SDL_RenderDrawLine(renderer, x+s* sqrt(3), y, x+s* sqrt(3), y+s);
    SDL_RenderDrawLine(renderer, x, y+s, x+s/2* sqrt(3), y+1.5*s);
    SDL_RenderDrawLine(renderer, x+s* sqrt(3), y+s, x+s*0.5* sqrt(3), y+s*1.5);
    find_center(x,y);
    number++;
    printf("%lf %lf %d\n", x, y, number);
    if(number<numberofareas)
        generate_random(renderer, x, y);
    else
        return ;
}

void generate_random(SDL_Renderer *renderer, double x, double y)
{
    printf("%lf %lf %d\n", x, y, number);
    for (int i=1; i<=6; i++)
    {
        bool halat=rand()%2;
        printf("i%d halat%d\n", i, halat);
        if (halat)
        {
            if (i==1 && number<numberofareas && x <900- 1.5*s*sqrt(3) && y>2*s*sqrt(3) && mokhtasat[(int)(x+0.5 *s* sqrt(3))][(int)(y- 1.5*s)]==0 )
                draw(renderer, x+0.5 *s* sqrt(3), y- 1.5*s);
            else if (i==2 && number<numberofareas && x>0.5*s*sqrt(3) && y>2*s*sqrt(3) && mokhtasat[(int)(x-0.5 *s* sqrt(3))][(int)(y- 1.5*s)]==0)
                draw(renderer, x-0.5 *s* sqrt(3), y- 1.5*s);
            else if (i==3 && number<numberofareas && x<900- 2*s*sqrt(3) && mokhtasat[(int)(x+s* sqrt(3))][(int)y]==0 )
                draw(renderer, x+s* sqrt(3), y);
            else if (i==4 && number<numberofareas && x>s* sqrt(3) && mokhtasat[(int)(x-s* sqrt(3))][(int)y]==0 )
                draw(renderer, x - s * sqrt(3), y);
            else if (i==5 && number<numberofareas && x <900- 1.5*s*sqrt(3) && y<600-3.5*s && mokhtasat[(int)(x+0.5 *s* sqrt(3))][(int)(y+ 1.5*s)]==0 )
                draw(renderer, x+0.5 *s* sqrt(3), y+ 1.5*s);
            else if (i==6 && number<numberofareas  && x>0.5*s*sqrt(3) && y<600-3*s && mokhtasat[(int)(x-0.5 *s* sqrt(3))][(int)(y+ 1.5*s)]==0)
                draw(renderer, x-0.5 *s* sqrt(3), y+ 1.5*s);
        }
        if (number>=numberofareas)
            return;
    }
}

int main()
{
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Window *window = SDL_CreateWindow("Maps",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);

    int a = rand() % (900-s* 2), b = rand() % (600-2*s) + s*0.5, k = 0;
    double x = a * 1.0, y = b * 1.0;
    printf("x%lf y%lf\n", x, y);
    scanf ("%d %d", &numberofareas, &numberofplayers);
    center= malloc(sizeof (struct markaz )*numberofareas);
    draw(renderer, x, y);
    SDL_RenderPresent(renderer);
    bool isquit = false;
    SDL_Event event;
    while (!isquit)
        if (SDL_PollEvent( & event))
            if (event.type == SDL_QUIT)
                isquit = true;

    return 0;
}
