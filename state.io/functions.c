#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "menus.h"
#include "functions.h"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int s=50;
int chosenbackground=1;
int check[50]={0};
uint32_t colors[100];
uint32_t color[9]={0xffffc75f ,0xffaaaa00  , 0xff5fc7ff , 0xffff00ff,0xffccb5fc , 0xffff6f91, 0xffff9671, 0xff916fff, 0xff9b9d9e};
int numberofareas, numberofplayers, number;
struct markaz *center;
struct fight *bazi;
struct sarbaz *soldier;
struct potion majoon;
struct active potion1, potion2;
bool mutee=false;
bool nist=true;
int mokhtasat[SCREEN_WIDTH][SCREEN_HEIGHT]={0};
int maps;
bool running=true;
Mix_Music *music1 = NULL;
Mix_Music *music2 = NULL;
bool win=false, lose=false;
char name[40]="";
bool hmenu=true, hmap=false, hsettings=false, hranking=false, hstart=false, hpause=false, hend=false;

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |TTF_Init() | SDL_INIT_AUDIO) < 0)
        return;
}

void text(SDL_Renderer *renderer,int x,int y,const char * text,int font_size,int R,int G,int B, int A)

{
    TTF_Init();
    SDL_Color text_color = { R, G, B, A};
    const char * Font ="font.ttf";
    int mWidth = 0;
    int mHeight = 0;
    SDL_Rect* clip = NULL;
    TTF_Font *gFont = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture* mTexture = NULL;
    gFont = TTF_OpenFont(Font, font_size );

    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont,text, text_color );

    mWidth = textSurface->w;
    mHeight = textSurface->h;
    mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
    SDL_FreeSurface( textSurface );
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
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
    }
}

void find_center( double x, double y, uint32_t target)
{
    center[number].x=x+0.5*s* sqrt(3);
    center[number].y=y+0.5*s;
    center[number].color=target;
    mokhtasat[(int)x][(int)y]++;
}

void m0(int i, int k)
{
    if (k==1)
        if (potion1.color==center[i].color)
            center[i].speed=8;
    if (k==2)
        if (potion2.color==center[i].color)
            center[i].speed=8;
    if (center[i].color!=potion1.color && center[i].color!=potion2.color)
        center[i].speed=4;
}

void m00(int i, int k)
{
    center[i].speed=4;
}

void m1(int i, int k)
{
    if (k==1)
        if (potion1.color!=center[i].color)
            center[i].speed=2;
    if (k==2)
        if (potion2.color!=center[i].color)
            center[i].speed=2;
    if (center[i].color==potion1.color || center[i].color==potion2.color)
        center[i].speed=4;
}

void m11(int i, int k)
{
    center[i].speed=4;
}

void m2(int i, int k)
{
    if (k==1)
        if (potion1.color==center[i].color)
            center[i].max=10000;
    if (k==2)
        if (potion2.color==center[i].color)
            center[i].max=10000;
}

void m22(int i, int k)
{
    if (k==1)
        if (potion1.color==center[i].color)
            center[i].max=80;
    if (k==2)
        if (potion2.color==center[i].color)
            center[i].max=80;
}

void m3(int i, int k)
{
    if (k==1)
        if (potion1.color==center[i].color)
            center[i].rate=10;
    if (k==2)
        if (potion2.color==center[i].color)
            center[i].rate=10;
}

void m33(int i, int k)
{
    if (k==1)
        if (potion1.color==center[i].color)
            center[i].rate=20;
    if (k==2)
        if (potion2.color==center[i].color)
            center[i].rate=20;
}

void qheyrfaal()
{
    if (potion1.time>=300 && potion1.color!=0)
    {
        for (int i=0; i<numberofareas; i++)
        {
            if (potion1.type==0)
                m00(i, 1);
            if (potion1.type==1)
                m11(i, 1);
            if (potion1.type==2)
                m22(i, 1);
            if (potion1.type==3)
                m33(i, 1);
        }
        potion1.color=0;
        potion1.type=20;
        potion1.time=0;
    }
    if (potion2.time>=300 && potion2.color!=0)
    {
        for (int i=0; i<numberofareas; i++)
        {
            if (potion2.type==0)
                m00(i, 2);
            if (potion2.type==1)
                m11(i, 2);
            if (potion2.type==2)
                m22(i, 2);
            if (potion2.type==3)
                m33(i, 2);
        }
        potion2.color = 0;
        potion2.type=20;
        potion2.time=0;
    }
}

void active_potion()
{
    qheyrfaal();
    for (int i=0; i<numberofareas; i++)
    {
        if (potion1.color==center[i].color)
        {
            center[i].majoon = true;
            center[i].type = potion1.type;
        }
        else if (potion2.color==center[i].color)
        {
            center[i].majoon = true;
            center[i].type = potion2.type;
        }
        else
            center[i].majoon = false;
        if (potion1.type==0 && potion1.color!=0)
            m0(i, 1);
        if (potion1.type==1 && potion1.color!=0)
            m1(i, 1);
        if (potion1.type==2 && potion1.color!=0)
            m2(i, 1);
        if (potion1.type==3 && potion1.color!=0)
            m3(i, 1);
        if (potion2.type==0 && potion2.color!=0)
            m0(i, 2);
        if (potion2.type==1 && potion2.color!=0)
            m1(i, 2);
        if (potion2.type==2 && potion2.color!=0)
            m2(i, 2);
        if (potion2.type==3 && potion2.color!=0)
            m3(i, 2);
    }
    potion1.time++;
    potion2.time++;
}

void bekesh (SDL_Renderer *renderer, struct markaz center[])
{
    int man=0, to=0;
    for (int i=0; i<numberofareas; i++)
    {
        double x=center[i].x-0.5*s*sqrt(3), y=center[i].y-0.5*s;
        char numberofs[1000];
        sprintf(numberofs, "%d", center[i].soldiers);
        SDL_Rect test = {center[i].x-10 , center[i].y-10 , 20 , 20};
        SDL_Color col = {0,0,0,255};
        TTF_Font * font = TTF_OpenFont("font.ttf" , 26);
        SDL_Surface *adads= TTF_RenderText_Solid(font , numberofs , col);
        SDL_Texture *tex= SDL_CreateTextureFromSurface(renderer , adads);
        uint32_t target=center[i].color;
        if (target!=color[0] && target!=color[8])
            to++;
        if (target==color[0])
            man++;
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
        aaellipseRGBA(renderer, center[i].x, center[i].y, center[i].r, center[i].r, 255, 255, 255, 255);
        aaellipseRGBA(renderer, center[i].x, center[i].y, center[i].r-3, center[i].r-3, 255, 255, 255, 255);
        SDL_RenderCopy(renderer , tex, NULL, &test);
        SDL_FreeSurface(adads);
        SDL_DestroyTexture(tex);
        TTF_CloseFont(font);
//        majoonfaal(i);
        if (center[i].majoon)
        {
            SDL_Rect size = {center[i].x, center[i].y + 15, 20, 20};
            SDL_Surface *m;
            if (center[i].type==0)
                m = SDL_LoadBMP("m0.bmp");
            if (center[i].type==1)
                m = SDL_LoadBMP("m1.bmp");
            if (center[i].type==2)
                m = SDL_LoadBMP("m2.bmp");
            if (center[i].type==3)
                m = SDL_LoadBMP("m3.bmp");
            SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, m);
            SDL_RenderCopy(renderer, img, NULL, &size);
            SDL_FreeSurface(m);
            SDL_DestroyTexture(img);
        }
    }
    if (man==0)
        lose=true;
    if (to==0)
        win=true;
}

void draw (SDL_Renderer *renderer, double x, double y)
{
    if (number>=numberofareas)
        return;
    srand(time(0));
    int r=rand()%numberofareas;
    while(check[r]!=0)
        r = rand() % numberofareas;
    check[r]=1;
    uint32_t target;
    target=colors[r];
    center[number].target=r;
    find_center(x,y, target);
    number++;
    if(number<numberofareas)
        generate_random(renderer, x, y);
    else
        return;
}

void generate_random(SDL_Renderer *renderer, double x, double y)
{
    for (int i=1; i<=6; i++)
    {
        bool halat=rand()%2;
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
            if (*start==-1 && center[i].color ==color[0])
                *start = i;
            else if (*start!=-1 && i!=*start)
                *end = i;
            else
            {
                *start = -1;
                *end= -1;
            }
            return;
        }
    }
    *start = -1;
    *end = -1;
}

void faal(int i)
{
    struct sarbaz *head=bazi[i].head;
    while (head!=NULL)
    {
        if (pow(head->x-majoon.x, 2) + pow(head->y-majoon.y, 2)<=64 && center[bazi[i].s].majoon==false)
        {
            nist=false;
            if (majoon.whichone==1)
            {
                potion1.type=majoon.type;
                potion1.color=center[bazi[i].s].color;
                potion1.time=0;
                majoon.whichone=2;
            }
            else if (majoon.whichone==2)
            {
                potion2.type=majoon.type;
                potion2.color=center[bazi[i].s].color;
                potion2.time=0;
                majoon.whichone=1;
            }
            majoon.x=0;
            majoon.y=0;
            return;
        }
        head=head->next;
    }
}

void generate_soldier(int c)
{
    for (int i=0; i<numberofareas; i++)
    {
        if (center[i].soldiers<center[i].max && center[i].rate!=0 && c%center[i].rate==0)
            center[i].soldiers++;
    }
}

void addattail(struct sarbaz *head, double x0, double y0, int i)
{
    if (bazi[i].counter==bazi[i].nsarbaz|| center[bazi[i].s].color!=bazi[i].start.color || center[bazi[i].s].soldiers<=0)
    {
        bazi[i].halat=false;
        return;
    }
    while(head->next != NULL)
        head = head->next;
    head->next = (struct sarbaz*)(malloc(sizeof(struct sarbaz)));
    head->next->x = bazi[i].start.x;
    head->next->y = bazi[i].start.y;
    head->next->next = NULL;
    bazi[i].counter++;
    if (center[bazi[i].s].soldiers>0 && center[bazi[i].s].color==bazi[i].start.color)
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
            if (center[bazi[i].e].soldiers>0)
                center[bazi[i].e].soldiers--;
            if (center[bazi[i].e].soldiers<=0)
            {
                center[bazi[i].e].color = bazi[i].start.color;
                if(bazi[i].end.color==color[8])
                    center[bazi[i].e].max=80;
            }
        }
        return new_head;
    }
}

void ziadkon(struct sarbaz *head, int i)
{
    while(head != NULL )
    {
        if (bazi[i].start.x-bazi[i].end.x<-1)
        {
            head->x += center[bazi[i].s].speed * 1/sqrt(pow(bazi[i].shib,2)+1);
            head->y += center[bazi[i].s].speed * 1/sqrt(pow(bazi[i].shib,2)+1) * bazi[i].shib;
        }
        else if (bazi[i].start.x-bazi[i].end.x>1)
        {
            head->x -= center[bazi[i].s].speed * 1/sqrt(pow(bazi[i].shib,2)+1);
            head->y -= center[bazi[i].s].speed * 1/sqrt(pow(bazi[i].shib,2)+1) * bazi[i].shib;
        }
        else
        {
            if (bazi[i].start.y<bazi[i].end.y)
                head->y += center[bazi[i].s].speed;
            if (bazi[i].start.y>bazi[i].end.y)
                head->y -= center[bazi[i].s].speed;
        }
        head = head->next;
    }
}

int checkkon(struct sarbaz *head, int i)
{
    while (head->next !=NULL)
        head=head->next;
    if (pow(head->x-bazi[i].start.x,2)+pow(head->y-bazi[i].start.y,2)<=220)
        return 0;
    return 1;
}

int checknakon(struct sarbaz *head, int i)
{
    if (pow(head->x-bazi[i].end.x,2)+pow(head->y-bazi[i].end.y,2)<=64)
        return 0;
    return 1;
}

void hamle(SDL_Renderer *renderer, int c, int i)
{
    if ((bazi[i].counter==bazi[i].nsarbaz ) && bazi[i].head==NULL)
    {
        bazi[i].nsarbaz=0;
        center[bazi[i].s].on=false;
        return;
    }
    if ((bazi[i].counter==0 || bazi[i].head==NULL) && bazi[i].halat )
    {
        bazi[i].head = (struct sarbaz*)(malloc(sizeof(struct sarbaz)));
        bazi[i].head->x = bazi[i].start.x;
        bazi[i].head->y = bazi[i].start.y;
        bazi[i].head->next = NULL;
        bazi[i].counter++;
        center[bazi[i].s].soldiers--;
    }
    if (bazi[i].halat && checkkon(bazi[i].head, i) )
        addattail(bazi[i].head, bazi[i].start.x, bazi[i].start.y, i);
    if (bazi[i].head!=NULL && !checknakon(bazi[i].head, i))
        bazi[i].head= delete_from_head(bazi[i].head, i);
    ziadkon(bazi[i].head, i);
    faal(i);
    struct sarbaz *h=bazi[i].head;
    while (h != NULL)
    {
        aaellipseRGBA(renderer, h->x, h->y, 5, 5, 0,0,0,255);
        filledEllipseColor(renderer, h->x, h->y, 4, 4, bazi[i].start.color);
        h=h->next;
    }
}

void is_same(int i, int j, struct sarbaz *headi, struct sarbaz *headj)
{
    while (headj->next!=NULL && bazi[i].head !=NULL)
    {
        if (pow(bazi[i].head->x-headj->next->x, 2)+pow(bazi[i].head->y-headj->next->y, 2)<100 && bazi[i].start.color != bazi[j].start.color)
        {
            free(headj->next);
            headj->next=headj->next->next;
            free(bazi[i].head);
            bazi[i].head=bazi[i].head->next;
            return;
        }
        headj=headj->next;
    }
}

void randomareas (SDL_Renderer *renderer)
{
    nist=true;
    srand(time(NULL));
    int one, two;
    one = rand()%numberofareas;
    two =rand()%numberofareas;
    while (two==one || (center[one].color==center[two].color && center[one].color==color[8]))
        two =rand()%numberofareas;
    majoon.type=rand()%4;
    majoon.x= (center[one].x+center[two].x)/2;
    majoon.y= (center[one].y+center[two].y)/2;
}

void makemajoon(SDL_Renderer *renderer)
{
    if (nist)
    {
        SDL_Rect size = {majoon.x - 25, majoon.y - 25, 50, 50};
        SDL_Surface *m;
        if (majoon.type==0)
            m = SDL_LoadBMP("m0.bmp");
        if (majoon.type==1)
            m = SDL_LoadBMP("m1.bmp");
        if (majoon.type==2)
            m = SDL_LoadBMP("m2.bmp");
        if (majoon.type==3)
            m = SDL_LoadBMP("m3.bmp");
        SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, m);
        SDL_RenderCopy(renderer, img, NULL, &size);
        SDL_FreeSurface(m);
        SDL_DestroyTexture(img);
    }
}

void startfight(int *start, int *end)
{
    int i=0;
    while (bazi[i].nsarbaz!=0)
        i++;
    bazi[i].start=center[*start];
    bazi[i].end=center[*end];
    bazi[i].s=*start;
    bazi[i].e=*end;
    bazi[i].halat=true;
    if (!center[*end].x-center[*start].x)
        bazi[i].shib=(center[*end].y-center[*start].y)/(center[*end].x-center[*start].x);
    else
        bazi[i].shib=0;
    bazi[i].nsarbaz=center[*start].soldiers;
    bazi[i].counter=0;
    center[bazi[i].s].on= true;
    *start = -1;
    *end = -1;
}

void barkhord(SDL_Renderer *renderer, int c)
{
    for (int i=0; i<100; i++)
    {
        if (bazi[i].nsarbaz!=0)
        {
            hamle(renderer, c, i);

            for (int j=0; j<100; j++)
            {
                if (i!=j)
                {
                    if (bazi[j].nsarbaz != 0)
                    {
                        struct sarbaz *h= (struct sarbaz*)malloc(sizeof (struct sarbaz)), *m=(struct sarbaz*)malloc(sizeof (struct sarbaz));
                        h->next = bazi[j].head;
                        m->next  =bazi[i].head;
                        is_same(i, j, m, h);
                        bazi[j].head = h->next;
                    }
                }
            }
        }
    }
}

int halat0(int aval)
{
    srand(time(NULL));
    int akhar=rand()%numberofareas;
    while (center[akhar].color==center[aval].color || akhar==aval)
        akhar=rand()%numberofareas;
    return akhar;
}

int halat1(int aval)
{
    srand(time(NULL));
    int akhar=rand()%numberofareas, k=0;
    while (akhar==aval)
    {
        akhar=rand()%numberofareas;
        k++;
        if (k>numberofareas)
        {
            akhar= halat0(aval);
            break;
        }
    }
    return akhar;
}

int halat2(int aval)
{
    srand(time(NULL));
    int akhar=rand()%numberofareas, k=0;
    while (center[akhar].color!=color[0])
    {
        akhar=rand()%numberofareas;
        k++;
        if (k>=numberofareas)
        {
            akhar= halat1(aval);
            break;
        }
    }
    return akhar;
}

int halat3(int aval)
{
    int min=1000000, akhar=-1;
    for (int i=0; i<numberofareas; i++)
    {
        if (center[i].soldiers<min && i!=aval && center[i].color!=center[aval].color)
        {
            min=center[i].soldiers;
            akhar=i;
        }
    }
    return akhar;
}

int halat4(int aval)
{
    srand(time(NULL));
    int akhar=rand()%numberofareas;
    for (int i=0; i<numberofareas; i++)
    {
        if (center[i].color==color[8])
        {
            akhar=i;
            break;
        }
//        if (majoon.x!=0 && majoon.y!=0 && (int)(center[aval].x+center[i].x) % (int)majoon.x==0 && (int)(center[aval].y+center[i].y) % (int)majoon.y==0)
//        {
//            akhar=i;
//            break;
//        }
    }
    return akhar;
}

void enemy(int *start, int *end)
{
    int ehtemal=rand()%100, halat=rand()%4;
    int m=*start;
    if(ehtemal<80 && halat==1)
    {
        int aval=rand()%numberofareas;
        while (center[aval].color==color[8] || center[aval].color==color[0])
            aval=rand()%numberofareas;
        *start=aval;
        *end = halat1(*start);
        startfight(start, end);
    }
    if(ehtemal<90 && halat==2)
    {
        int aval=rand()%numberofareas;
        while (center[aval].color==color[8] || center[aval].color==color[0] )
            aval=rand()%numberofareas;
        *start=aval;
        *end = halat2(*start);
        startfight(start, end);
    }
    if(ehtemal<90 && halat==3)
    {
        int aval=rand()%numberofareas;
        while (center[aval].color==color[8] || center[aval].color==color[0])
            aval=rand()%numberofareas;
        *start=aval;
        *end = halat3(*start);
        startfight(start, end);
    }
    if(ehtemal<95 && halat==4)
    {
        int aval=rand()%numberofareas;
        while (center[aval].color==color[8] || center[aval].color==color[0] || center[aval].on)
            aval=rand()%numberofareas;
        *start=aval;
        *end = halat4(*start);
        startfight(start, end);
    }
    *start=m;
}

int readfile (struct users carbar[])
{
    FILE *scores= fopen("scores.md", "r");
    char harf= fgetc(scores);
    int j=-1;
    while (harf != EOF)
    {
        j++;
        for (int m=0; m<40; m++)
            carbar[j].name[m]='\0';
        int i=0;
        while (harf!=EOF && harf!='/')
        {
            carbar[j].name[i++]=harf;
            harf= fgetc(scores);
        }
        if (harf=='/')
        {
            fscanf(scores, "%d %d %d %d ", &carbar[j].win, &carbar[j].lose, &carbar[j].draw, &carbar[j].score);
            harf= fgetc(scores);
        }
    }
    return j;
}

void sort(FILE *scores)
{
    FILE *new= fopen("new.md", "w");
    struct users carbar[100];
    char harf= fgetc(scores);
    int j=-1;
    while (harf != EOF)
    {
        j++;
        for (int m=0; m<40; m++)
            carbar[j].name[m]='\0';
        int i=0;
        while (harf!=EOF && harf!='/')
        {
            carbar[j].name[i++]=harf;
            harf= fgetc(scores);
        }
        if (harf=='/')
        {
            fscanf(scores, "%d %d %d %d ", &carbar[j].win, &carbar[j].lose, &carbar[j].draw, &carbar[j].score);
            harf= fgetc(scores);
        }
    }
    for (int i=1; i<=j; i++)
    {
        struct users key=carbar[i];
        int k=i-1;
        while (k>=0 && key.score>carbar[k].score)
        {
            carbar[k+1]=carbar[k];
            k--;
        }
        carbar[k+1]=key;
    }
    for (int i=0; i<=j; i++)
        fprintf(new, "%s/%d %d %d %d\n", carbar[i].name, carbar[i].win, carbar[i].lose, carbar[i].draw, carbar[i].score);
    fclose(new);
    remove("scores.md");
    rename("new.md", "scores.md");
}

void map0(SDL_Renderer *renderer)
{
    int a = rand() % (SCREEN_WIDTH-50 - s * 2), b = rand() % (SCREEN_HEIGHT-50 - 2 * s) + s * 0.5;
    int m=0;
    double x = a * 1.0, y = b * 1.0;
    center = malloc(sizeof(struct markaz) * numberofareas);
    makecolors(color);
    draw(renderer, x, y);
    while (number<numberofareas && m<100)
    {
        generate_random(renderer, x, y);
        m++;
    }
    if (m>=100 && number<numberofareas)
    {
        hmap=false;
        hstart=true;
    }
}

void map1()
{
    FILE *test= fopen("plans.md", "r");
    fscanf(test, "%*c%d %d", &numberofareas, &numberofplayers);
    center = malloc(sizeof(struct markaz) * numberofareas);
    for (int i=0; i<numberofareas; i++)
    {
        fscanf(test, "%lf %lf %d", &center[i].x, &center[i].y, &center[i].target);
        if (center[i].target>7)
            center[i].color=color[8];
        else
            center[i].color=color[center[i].target];
    }
}

void map2()
{
    FILE *test= fopen("plans.md", "r");
    char harf= fgetc(test);
    while ((harf=fgetc(test))!='/');
    fscanf(test, "%d %d", &numberofareas, &numberofplayers);
    center = malloc(sizeof(struct markaz) * numberofareas);
    for (int i=0; i<numberofareas; i++)
    {
        fscanf(test, "%lf %lf %d", &center[i].x, &center[i].y, &center[i].target);
        if (center[i].target>=7)
            center[i].color=color[8];
        else
            center[i].color=color[center[i].target];
    }
}

void map3()
{
    FILE *test= fopen("test.md", "r");
    fscanf(test, "%*c%d %d", &numberofareas, &numberofplayers);
    center = malloc(sizeof(struct markaz) * numberofareas);
    for (int i=0; i<numberofareas; i++)
    {
        fscanf(test, "%lf %lf %d", &center[i].x, &center[i].y, &center[i].target);
        center[i].color=color[center[i].target];
    }
}

void insialize()
{
    for (int i=0; i<numberofareas; i++)
    {
        center[i].soldiers = 20;
        center[i].rate=20;
        center[i].r=20;
        center[i].speed = 4;
        if (center[i].color==color[8])
            center[i].max=0;
        else
            center[i].max=80;
        center[i].majoon=false;
        center[i].on=false;
    }
    bazi = malloc(sizeof (struct fight)*100);
    for (int i=0; i<100; i++)
    {
        bazi[i].head = NULL;
        bazi[i].nsarbaz=0;
        bazi[i].halat=false;
    }
    majoon.whichone=1;
    potion1.color=0;
    potion2.color=0;
}

void save(SDL_Renderer *renderer)
{
    if (win || lose)
    {
        hmap=false;
        hend=true;
        SDL_DestroyRenderer(renderer);
    }
    FILE *scoresf=fopen("scores1.md", "w"), *scoresi= fopen("scores.md", "r");

    char harf= fgetc(scoresi);
    int nwin, nlose, ndraw, score;
    bool nevesht=false;
    while (harf != EOF)
    {
        int i=0;
        char user[40]="";
        while (harf!=EOF && harf!='/')
        {
            user[i++]=harf;
            harf= fgetc(scoresi);
        }
        if (harf=='/')
        {
            fscanf(scoresi, "%d %d %d %d ", &nwin, &nlose, &ndraw, &score);
            if (!strcmp(user, name))
            {
                if (win)
                    nwin++;
                if (lose)
                    nlose++;
                else
                    ndraw++;
                score=nwin*2-nlose;
                nevesht=true;
            }
            fprintf(scoresf, "%s/%d %d %d %d\n", user, nwin, nlose, ndraw, score);
            harf= fgetc(scoresi);
        }
    }
    if (!nevesht)
    {
        if (win)
            fprintf(scoresf, "%s/%d %d %d %d\n", name, 1, 0, 0, 2);
        else if (lose)
            fprintf(scoresf, "%s/%d %d %d %d\n", name, 0, 1, 0, -1);
        else if (!hmap)
            fprintf(scoresf, "%s/%d %d %d %d\n", name, 0, 0, 1, 0);
    }
    fclose(scoresi);
    fclose(scoresf);
    remove("scores.md");
    rename("scores1.md", "scores.md");
    FILE *scores= fopen("scores.md", "r");
    sort(scores);
    fclose(scores);

}

int map(SDL_Window *window)
{
    srand(time(NULL));
    number=0;
    init();
    for (int i=0; i<50; i++)
        check[i]=0;
    //window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    //map
    int  c=0, start=-1, end=-1;
    if (maps==0)
        map0(renderer);
    if (maps==1)
        map1();
    if (maps==2)
        map2();
    if (maps==3)
        map3();
    insialize();

    //background
    double xpause=5, ypause=545, w=50;
    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background;
    if (chosenbackground==1)
        background= SDL_LoadBMP("background1.bmp");
    if (chosenbackground==2)
        background= SDL_LoadBMP("background2.bmp");
    if (chosenbackground==3)
        background= SDL_LoadBMP("background3.bmp");
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Rect size = {xpause, ypause , w , w};
    SDL_Surface *pause = SDL_LoadBMP("pause.bmp");
    SDL_Texture *aks = SDL_CreateTextureFromSurface(renderer, pause);
    SDL_Event event;
    //running
    while (running && hmap)
    {
        win=false;
        lose=false;
        c++;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &andaze);
        SDL_RenderCopy(renderer, aks, NULL, &size);
        bekesh(renderer, center);
        SDL_PollEvent(&event);
        if (start!=-1 && end!=-1)
            startfight(&start, &end);
        barkhord(renderer, c);
        if (c%400==0)
            randomareas(renderer);
        if (c%400>=0 && c%400<=300 && c>=400)
            makemajoon(renderer);
        active_potion();
        if (c%200==100)
            enemy(&start, &end);
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.motion.x>=xpause && event.motion.x<=xpause+w && event.motion.y>=ypause && event.motion.y<=ypause+w)
            {
                SDL_DestroyRenderer(renderer);
                int chi=pausemenu(window);
                if (chi==1)
                {
                    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
                    img = SDL_CreateTextureFromSurface(renderer, background);
                    aks = SDL_CreateTextureFromSurface(renderer, pause);
                }
                if (chi==0)
                {
                    hmap=false;
                    hend=true;
                }
            }
            else
                saveclick(event.motion.x, event.motion.y, &start, &end);
        }
        SDL_RenderPresent(renderer);
        if (event.type == SDL_QUIT )
            running=false;
        if ( win || lose || hend)
            save(renderer);
        generate_soldier(c);
    }
    SDL_DestroyTexture(img);
    SDL_FreeSurface(background);
    free(center);
    return 0;
}