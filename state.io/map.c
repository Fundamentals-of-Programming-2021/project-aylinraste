#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct markaz
{
    double x;
    double y;
    int soldiers;
    uint32_t color;
    int rate;
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
    int rate;
    struct sarbaz current;
    struct sarbaz *head;
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
struct fight *bazi;
struct sarbaz *soldier;
int mokhtasat[SCREEN_WIDTH][SCREEN_HEIGHT]={0};
bool running=true;

#ifdef main
#undef main
#endif
void init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |TTF_Init()) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
}

void generate_random(SDL_Renderer *renderer, double x, double y);

void txtRGBA(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A)
{
    TTF_Init();
    SDL_Color text_color = { 0, 0, 0, 255};
    const char * font_address_01="font.ttf";
    const char * Font =NULL;
    Font =font_address_01;
    int mWidth=0;
    int mHeight=0;
    SDL_Rect *clip = NULL;
    TTF_Font *gFont = NULL;
    double angle = 0.0;
    SDL_Point *c = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture* mTexture = NULL;
    gFont = TTF_OpenFont(Font, font_size );
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont,text, text_color );
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, c, flip );

    SDL_DestroyTexture( mTexture );
    TTF_CloseFont(gFont);
}

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
//        printf("%x\n", colors[i]);
    }
}

void find_center( double x, double y, uint32_t target)
{
    center[number].x=x+0.5*s* sqrt(3);
    center[number].y=y+0.5*s;
    center[number].color=target;
    mokhtasat[(int)x][(int)y]++;
}

void bekesh (SDL_Renderer *renderer, struct markaz center[])
{
    for (int i=0; i<numberofareas; i++)
    {
        double x=center[i].x-0.5*s*sqrt(3), y=center[i].y-0.5*s;
        char numberofs[1000];
        sprintf(numberofs, "%d", center[i].soldiers);
        SDL_Rect test = {center[i].x-10 , center[i].y-10 , 20 , 20};
        SDL_Color col = {0,0,0,255};
        TTF_Font * font = TTF_OpenFont("font.ttf" , 26);
        if (!font)
            printf("Failed to load image at%s", SDL_GetError());
        SDL_Surface *adads= TTF_RenderText_Solid(font , numberofs , col);
        SDL_Texture *tex= SDL_CreateTextureFromSurface(renderer , adads);
        uint32_t target=center[i].color;
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
        aaellipseRGBA(renderer, center[i].x, center[i].y, 20, 20, 255, 255, 255, 255);
        aaellipseRGBA(renderer, center[i].x, center[i].y, 17, 17, 255, 255, 255, 255);
        SDL_RenderCopy(renderer , tex, NULL, &test);
        SDL_FreeSurface(adads);
        SDL_DestroyTexture(tex);
        TTF_CloseFont(font);
    }
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
    target=colors[r];
    find_center(x,y, target);
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
//        printf("i%d halat%d\n", i, halat);
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

void saveclick(double x, double y , int *start, int *end)
{
    for (int i=0; i<numberofareas; i++)
    {
        if (pow(x-center[i].x, 2)+ pow(y-center[i].y, 2)<=400)
        {
            if (*start==-1 && center[i].color !=color[8])
                *start = i;
            else if (*start!=-1 && i!=*start)
                *end = i;
            else
            {
                *start = -1;
                *end= -1;
            }
            printf("%d %d\n", *start, *end);
            return;
        }
    }
    *start = -1;
    *end = -1;
}

void generate_soldier(int c)
{
    for (int i=0; i<numberofareas; i++)
    {
        if (center[i].color != color[8] && center[i].soldiers<80 && center[i].rate!=0 && c%center[i].rate==0)
            center[i].soldiers++;
    }
}

void addattail(struct sarbaz *head, double x0, double y0, int i)
{
    while(head->next != NULL)
    {
        head = head->next;
        printf ("1 you\n");
    }
    head->next = (struct sarbaz*)(malloc(sizeof(struct sarbaz)));
    head->next->x = bazi[i].start.x;
    head->next->y = bazi[i].start.y;
    printf("%lf %lf\n", head-> x, head->y );
    head->next->next = NULL;
    bazi[i].counter++;
    bazi[i].current=*head;
    center[bazi[i].s].soldiers--;
}

struct sarbaz* delete_from_head(struct sarbaz* head, int i)
{
    if(head != NULL )
    {
        struct sarbaz* new_head = head->next;
        free(head);
        if (center[bazi[i].e].color==bazi[i].start.color)
        {
            center[bazi[i].e].soldiers++;
        }
        else
        {
            center[bazi[i].e].soldiers--;
            if (center[bazi[i].e].soldiers==0)
            {
                center[bazi[i].e].color = bazi[i].start.color;
            }
        }
        return new_head;
    }
}

void ziadkon(struct sarbaz *head, int i)
{
    while(head != NULL )
    {
        if (bazi[i].start.x<bazi[i].end.x)
        {
            head->x += bazi[i].rate;
            head->y += bazi[i].rate * bazi[i].shib;
        }
        else if (bazi[i].start.x>bazi[i].end.x)
        {
            head->x -= bazi[i].rate;
            head->y -= bazi[i].rate * bazi[i].shib;
        }
        else
            head->y += bazi[i].rate;
        printf ("mmmm%lf %lf\n", head->x, head->y);
        head = head->next;
    }
}

int checkkon(struct sarbaz *head, int i)
{
//    printf("c%lf %lf %lf %lf\n",bazi[i].start.x, bazi[i].start.y, head->x, head->y);
    while (head->next !=NULL)
        head=head->next;
    if ((head->x-bazi[i].start.x<10 && head->x-bazi[i].start.x>-10))
        return 0;
//    if (bazi[i].current.x-bazi[i].start.x <10 || bazi[i].current.y-bazi[i].start.y <10)
//        return 0;
    printf("abc\n");
    return 1;
}

int checknakon(struct sarbaz *head, int i)
{
    if (pow(head->x-bazi[i].end.x,2)+ pow(head->y-bazi[i].end.y,2)<=64)
    {
        return 0;
    }
    return 1;
}

void hamle(SDL_Renderer *renderer, int c, int i)
{
    printf("a%d b%d\n", bazi[i].nsarbaz, bazi[i].counter);
    if (!center[bazi[i].s].soldiers)
    {
        bazi[i].nsarbaz=0;
        center[bazi[i].s].rate=20;
        return;
    }
    if (bazi[i].counter==0)
    {
        bazi[i].head = (struct sarbaz*)(malloc(sizeof(struct sarbaz)));
        bazi[i].head->x = bazi[i].start.x;
        bazi[i].head->y = bazi[i].start.y;
        printf("%lf %lf\n", bazi[i].head-> x, bazi[i].head->y );
        bazi[i].head->next = NULL;
        bazi[i].counter++;
        bazi[i].current=*bazi[i].head;
    }
    else if (checkkon(bazi[i].head, i))
    {
        addattail(bazi[i].head, bazi[i].start.x, bazi[i].start.y, i);
        printf("fuck\n");
    }
    if (!checkkon(bazi[i].head, i))
        printf("gav\n");
    if (!checknakon(bazi[i].head, i))
    {
        bazi[i].head= delete_from_head(bazi[i].head, i);
    }

    ziadkon(bazi[i].head, i);
    printf("khar\n");
}

int main()
{
    srand(time(NULL));
    init();
    //window
    SDL_Window *window = SDL_CreateWindow("Maps",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    //map
    int a = rand() % (SCREEN_WIDTH - s * 2), b = rand() % (SCREEN_HEIGHT - 2 * s) + s * 0.5, c=0, start=-1, end=-1;
    double x = a * 1.0, y = b * 1.0;
    scanf("%d %d", &numberofareas, &numberofplayers);
    center = malloc(sizeof(struct markaz) * numberofareas);
    for (int i=0; i<numberofareas; i++)
    {
        center[i].soldiers = 20;
        center[i].rate=20;
    }
    makecolors(color);
    while (number<numberofareas)
    {
        draw(renderer, x, y);
        a = rand() % (SCREEN_WIDTH - s * 2), b = rand() % (SCREEN_HEIGHT - 2 * s) + s * 0.5;
        x = a * 1.0, y = b * 1.0;
    }
    //background
    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background = SDL_LoadBMP("background.bmp");
    if (!background)
        printf("Failed to load image at%s", SDL_GetError());
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);
    SDL_Event event;
    bazi = malloc(sizeof (struct fight)*100);
    for (int i=0; i<100; i++)
    {
        bazi[i].head = NULL;
        bazi[i].nsarbaz=0;
    }
    //running
    while (running)
    {
        c++;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &andaze);
        bekesh(renderer, center);
        SDL_PollEvent(&event);
        SDL_RenderPresent(renderer);
        generate_soldier(c);
        if (event.type == SDL_QUIT)
            running=false;
        if (event.type == SDL_MOUSEBUTTONDOWN)
            saveclick(event.motion.x, event.motion.y, &start, &end);
        if (start!=-1 && end!=-1)
        {
            printf("start:%d end:%d\n", start, end);
            int i=0;
            while (bazi[i].nsarbaz!=0)
                i++;
            bazi[i].start=center[start];
            bazi[i].end=center[end];
            bazi[i].s=start;
            bazi[i].e=end;
            if (!center[end].x-center[start].x)
                bazi[i].shib=(center[end].y-center[start].y)/(center[end].x-center[start].x);
            else
                bazi[i].shib=0;
            bazi[i].nsarbaz=center[start].soldiers;
            bazi[i].counter=0;
            bazi[i].rate=4;
            center[start].rate=0;
            printf("%lf %lf %lf %lf\n",center[start].x, center[start].y, bazi[i].start.x, bazi[i].start.y);
//            if (bazi[i].nsarbaz==0)
            start = -1;
            end = -1;
            printf("1\n");
        }
        for (int i=0; i<100; i++)
        {
            if (bazi[i].nsarbaz!=0)
                hamle(renderer, c, i);
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
