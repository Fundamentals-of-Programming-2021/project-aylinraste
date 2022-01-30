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
    uint32_t color;
};

const int FPS = 60;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int s=50;
int check[50]={0};
uint32_t colors[100];
uint32_t color[9]={0xffffc75f ,0xffaaaa00  , 0xff5fc7ff , 0xffff00ff,0xffccb5fc , 0xffff6f91, 0xffff9671, 0xff916fff, 0xff9b9d9e};
int numberofareas, numberofplayers, number=0;
struct markaz *center;
int mokhtasat[SCREEN_WIDTH][SCREEN_HEIGHT]={0};
bool running=true;

#ifdef main
#undef main
#endif
void generate_random(SDL_Renderer *renderer, double x, double y);

//void txtRGBA(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A)
//{
//    TTF_Init();
//    SDL_Color text_color = { 0, 0, 0, 255};
//    const char * font_address_01="fontadad.ttf";
//    const char * Font =NULL;
//    Font =font_address_01;
//    int mWidth;
//    int mHeight;
//    SDL_Rect *clip = NULL;
//    TTF_Font *gFont = NULL;
//    double angle = 0.0;
//    SDL_Point *c = NULL;
//    SDL_RendererFlip flip = SDL_FLIP_NONE;
//    SDL_Texture* mTexture = NULL;
//    gFont = TTF_OpenFont(Font, font_size );
//
//    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont,text, text_color );
//
//    mWidth = textSurface->w;
//    mHeight = textSurface->h;
//    mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
//    SDL_FreeSurface( textSurface );
//
//
//    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, c, flip );
//
//    SDL_DestroyTexture( mTexture );
//
//}

void makecolors ()
{
    for (int i=0; i<numberofareas; i++)
    {
        if (i<numberofplayers)
        {
            colors[i]=color[i];
        }
        else
            colors[i]=color[8];
        printf("%x\n", colors[i]);
    }
}

void find_center( double x, double y, uint32_t target)
{
    center[number].x=x+0.5*s* sqrt(3);
    center[number].y=y+0.5*s;
    center[number].color=target;
    mokhtasat[(int)x][(int)y]++;
}

void draw (SDL_Renderer *renderer, double x, double y)
{
    if (number>=numberofareas)
        return;
    srand(time(0));
    int r=rand()%numberofareas;
    while(check[r]!=0)
        r = rand() % numberofareas;
    printf("%d %d\n", check[r], r);
    check[r]=1;
    uint32_t target;
    //if (!color[r][1] || r==0)
        target=colors[r];
    //else
        //target=color[0][0];
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
    find_center(x,y, target);
    aaellipseRGBA(renderer, center[number].x, center[number].y, 20, 20, 255, 255, 255, 255);
    aaellipseRGBA(renderer, center[number].x, center[number].y, 17, 17, 255, 255, 255, 255);
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
            if (i==1 && number<numberofareas && x <SCREEN_WIDTH- 1.5*s*sqrt(3) && y>2*s*sqrt(3) && mokhtasat[(int)(x+0.5 *s* sqrt(3))][(int)(y- 1.5*s)]==0 )
                draw(renderer, x+0.5 *s* sqrt(3), y- 1.5*s);
            else if (i==2 && number<numberofareas && x>0.5*s*sqrt(3) && y>2*s*sqrt(3) && mokhtasat[(int)(x-0.5 *s* sqrt(3))][(int)(y- 1.5*s)]==0)
                draw(renderer, x-0.5 *s* sqrt(3), y- 1.5*s);
            else if (i==3 && number<numberofareas && x<SCREEN_WIDTH- 2*s*sqrt(3) && mokhtasat[(int)(x+s* sqrt(3))][(int)y]==0 )
                draw(renderer, x+s* sqrt(3), y);
            else if (i==4 && number<numberofareas && x>s* sqrt(3) && mokhtasat[(int)(x-s* sqrt(3))][(int)y]==0 )
                draw(renderer, x - s * sqrt(3), y);
            else if (i==5 && number<numberofareas && x <SCREEN_WIDTH- 1.5*s*sqrt(3) && y<SCREEN_HEIGHT-3.5*s && mokhtasat[(int)(x+0.5 *s* sqrt(3))][(int)(y+ 1.5*s)]==0 )
                draw(renderer, x+0.5 *s* sqrt(3), y+ 1.5*s);
            else if (i==6 && number<numberofareas  && x>0.5*s*sqrt(3) && y<SCREEN_HEIGHT-3*s && mokhtasat[(int)(x-0.5 *s* sqrt(3))][(int)(y+ 1.5*s)]==0)
                draw(renderer, x-0.5 *s* sqrt(3), y+ 1.5*s);
        }
        if (number>=numberofareas)
            return;
    }
}

int main() {

    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Window *window = SDL_CreateWindow("Maps",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    int a = rand() % (SCREEN_WIDTH - s * 2), b = rand() % (SCREEN_HEIGHT - 2 * s) + s * 0.5, k = 0, h, w;
    double x = a * 1.0, y = b * 1.0;
    printf("x%lf y%lf\n", x, y);
    scanf("%d %d", &numberofareas, &numberofplayers);
    center = malloc(sizeof(struct markaz) * numberofareas);
    makecolors(color);
    SDL_Rect andaze;
    andaze.x = 0;
    andaze.y = 0;
    andaze.h = SCREEN_HEIGHT;
    andaze.w = SCREEN_WIDTH;
    SDL_Surface *background = SDL_LoadBMP("background.bmp");
    if (!background)
        printf("Failed to load image at%s", SDL_GetError());
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);
    int xx=0;
    int dx=5;
    SDL_Event event;
    SDL_RenderCopy(renderer, img, NULL, &andaze);

    while (running) {

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &andaze);
        draw(renderer, x, y);
        SDL_WaitEvent(&event);
        xx+=dx;
     //   filledCircleColor(renderer,xx,0,60,0xff000000);
        filledCircleColor(renderer,xx,0,60,0xff000000);
        //SDL_RenderClear(renderer);
       bool isquit = false;

        SDL_RenderPresent(renderer);
        //if(!isquit) {
           // SDL_RenderCopy(renderer, img, NULL, &andaze);
          //  draw(renderer, x, y);
          //  SDL_RenderPresent(renderer);
         //   SDL_RenderClear(renderer);
//            SDL_Event event;
            if (SDL_PollEvent(&event))
                if (event.type == SDL_QUIT) {
                    isquit = true;
                    running=false;
                }
        //}
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
