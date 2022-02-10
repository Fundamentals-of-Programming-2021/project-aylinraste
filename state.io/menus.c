#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"
#include "menus.h"

void first(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background = SDL_LoadBMP("background first.bmp");
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);
    SDL_Event event;
    int c=0;
    while(c<400 && running)
    {
        printf("1\n");
        c++;
        SDL_RenderClear(renderer);
        SDL_PollEvent(&event);
        SDL_RenderCopy(renderer, img, NULL, &andaze);
        SDL_RenderPresent(renderer);
        if (event.type == SDL_QUIT)
            running=false;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(img);
    SDL_FreeSurface(background);
}

int pausemenu(SDL_Window *window)
{
//    bool mutee=false;
    int xresum=135, yresum=200, w=120;
    int xrestart=390, yrestart=200;
    int xexit=645, yexit=200;
    int xmute=250, ymute=390;
    int xsave=530, ysave=390;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background = SDL_LoadBMP("backgroundpause.bmp");
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Rect size = {xmute, ymute , w , w};
    SDL_Surface *mute = SDL_LoadBMP("mute.bmp");
    SDL_Texture *aks = SDL_CreateTextureFromSurface(renderer, mute);

    SDL_Rect sizee = {xresum, yresum , w , w};
    SDL_Surface *resume = SDL_LoadBMP("resume.bmp");
    SDL_Texture *akss = SDL_CreateTextureFromSurface(renderer, resume);

    SDL_Rect sizeee = {xrestart, yrestart , w , w};
    SDL_Surface *restart = SDL_LoadBMP("restart.bmp");
    SDL_Texture *aksss = SDL_CreateTextureFromSurface(renderer, restart);

    SDL_Rect sizeeee = {xexit, yexit , w , w};
    SDL_Surface *exit = SDL_LoadBMP("exit.bmp");
    SDL_Texture *akssss = SDL_CreateTextureFromSurface(renderer, exit);

    SDL_Rect sizeeeee = {xsave, ysave , w , w};
    SDL_Surface *save = SDL_LoadBMP("save.bmp");
    SDL_Texture *aksssss = SDL_CreateTextureFromSurface(renderer, save);

    SDL_Rect sizeeeeee = {xmute, ymute, w , w};
    SDL_Surface *unmute = SDL_LoadBMP("unmute.bmp");
    SDL_Texture *akssssss = SDL_CreateTextureFromSurface(renderer, unmute);

    SDL_Event event;
    int c=0;

    while (running)
    {
        c++;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &andaze);
        if (!mutee)
            SDL_RenderCopy(renderer, aks, NULL, &size);
        else
            SDL_RenderCopy(renderer, akssssss, NULL, &sizeeeeee);
        SDL_RenderCopy(renderer, akss, NULL, &sizee);
        SDL_RenderCopy(renderer, aksss, NULL, &sizeee);
        SDL_RenderCopy(renderer, akssss, NULL, &sizeeee);
        SDL_RenderCopy(renderer, aksssss, NULL, &sizeeeee);
        if (c%30<=15)
            text(renderer, 320, 70, "GAME PAUSED!", 56, 90, 100, 255, 255);
        else
            text(renderer, 320, 70, "GAME PAUSED!", 56, 230, 170, 255, 255);
        SDL_PollEvent(&event);
        SDL_RenderPresent(renderer);
        if (event.type == SDL_QUIT)
            running=false;
        if (event.type==SDL_MOUSEBUTTONDOWN)
        {
            double x=event.motion.x;
            double y=event.motion.y;
            if (x>=xresum && x<=xresum+w && y>=yresum && y<=yresum+w) //resume
            {
                SDL_DestroyRenderer(renderer);
                SDL_FreeSurface(background);
                SDL_DestroyTexture(img);
                return 1;
            }
            else if (x>=xrestart && x<=xrestart+w && y>=yrestart && y<=yrestart+w)
            {
                SDL_DestroyRenderer(renderer);
                SDL_FreeSurface(background);
                SDL_DestroyTexture(img);
                return 0;
            }
            else if (x>=xexit && x<=xexit+w && y>=yexit && y<=yexit+w) //quit
                running=false;
            else if (x>=xsave && x<=xsave+w && y>=ysave && y<=ysave+w) //save
            {
                FILE *planc=fopen("plansc.md", "w"), *plan= fopen("plans.md", "r");
                char harf;
                char x[4], y[4], r[3], nofa[5], nofp[5];
                sprintf(nofa, "%d", numberofareas);
                sprintf(nofa, "%d", numberofplayers);
                fprintf(planc, "/%d %d\n", numberofareas, numberofplayers);
                for (int i=0; i<numberofareas; i++)
                {
                    fprintf(planc, "%lf %lf %d\n", center[i].x, center[i].y, center[i].target);
                }
                while ((harf=fgetc(plan)) != EOF)
                {
                    fprintf(planc, "%c", harf);
                }
                fclose(plan);
                fclose(planc);
                remove("plans.md");
                rename("plansc.md", "plans.md");
            }
            else if (x>=xmute && x<=xmute+w && y>=ymute && y<=ymute+w)//sound
            {
                if(!mutee)
                {
                    mutee=true;
                    Mix_PauseMusic();
                }
                else
                {
                    mutee=false;
                    Mix_ResumeMusic();
                }
            }
        }
    }
    return 0;
}

void menu(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background = SDL_LoadBMP("backgroundstart.bmp");
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Rect size = {315, 70 , 250 , 250};
    SDL_Surface *start = SDL_LoadBMP("start1.bmp");
    SDL_Texture *aks = SDL_CreateTextureFromSurface(renderer, start);

    SDL_Rect size1 = {90, 350 , 180 , 120};
    SDL_Surface *ranking = SDL_LoadBMP("ranking.bmp");
    SDL_Texture *aks1 = SDL_CreateTextureFromSurface(renderer, ranking);

    SDL_Rect size2 = {610, 350 , 180 , 120};
    SDL_Surface *settings = SDL_LoadBMP("settings.bmp");
    SDL_Texture *aks2 = SDL_CreateTextureFromSurface(renderer, settings);

    SDL_Rect size3 = {235, 490 , 420 , 70};
    SDL_Surface *username = SDL_LoadBMP("username.bmp");
    SDL_Texture *aks3 = SDL_CreateTextureFromSurface(renderer, username);

    SDL_Event event;
    bool type=false;
    bool capslock=false;
    bool quit=false;
    int i;
    bool menuu=true;
    while (running && hmenu)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &andaze);
        SDL_RenderCopy(renderer, aks, NULL, &size);
        SDL_RenderCopy(renderer, aks1, NULL, &size1);
        SDL_RenderCopy(renderer, aks2, NULL, &size2);
        SDL_RenderCopy(renderer, aks3, NULL, &size3);
        SDL_PollEvent(&event);
        if ( event.type==SDL_MOUSEBUTTONDOWN )
        {
            int x=event.motion.x;
            int y=event.motion.y;
            if (pow(x-440, 2)+pow(y-195, 2)<= 125 * 125 && strlen(name)!=0 ) // start
            {
                hmenu=false;
                hstart=true;
            }
            else if (pow(x-445, 2)<= 210 * 210 && pow(y-525, 2)<= 35 * 35) // username
            {
                i=0;
                type=true;
            }
            else if (pow(x-700, 2)<=90*90 && pow(y-410, 2)<=60*60)//setting
            {
                hmenu=false;
                hsettings=true;
            }
            else if (pow(x-180, 2)<=90*90 && pow(y-410, 2)<=60*60)//ranking
            {
                hmenu=false;
                hranking=true;
            }
        }
        if(type && !quit)
        {
            char ch='0';
            if ( event.type==SDL_KEYUP ) {
                if(event.key.keysym.sym==SDLK_CAPSLOCK)
                {
                    if (!capslock)
                        capslock=true;
                    else if (capslock)
                        capslock=false;
                }
                else if(event.key.keysym.sym==SDLK_BACKSPACE && i>0) { //irad dare!
                    name[i-1]='\0';
                    i--;
                }
                else if(event.key.keysym.sym==SDLK_RETURN)
                    quit=true;
                else
                    ch=event.key.keysym.sym;

                if ( (ch>='A' && ch <= 'Z') || (ch>='a' && ch <= 'z') || ch ==' ')
                {
                    if (capslock)
                        name[i++]=ch+'A'-'a';
                    else
                        name[i++]=ch;
                }
            }
        }
        if(strlen(name)!=0)
        {
            text(renderer, 330, 510, name, 56, 0, 0,0, 255);
        }
        SDL_RenderPresent(renderer);
        if (event.type == SDL_QUIT)
            running=false;
    }
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(background);
    SDL_DestroyTexture(img);
}

void endmenu(SDL_Window *window)
{
    int xhappy=235, yhappy=157, ww=442, hh=275;
    int xrestart=250, yrestart=450, w=100;
    int xexit=550, yexit=450;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background = SDL_LoadBMP("backgroundend.bmp");
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Rect size = {xrestart, yrestart , w , w};
    SDL_Surface *restart = SDL_LoadBMP("restart.bmp");
    SDL_Texture *aks = SDL_CreateTextureFromSurface(renderer, restart);

    SDL_Rect size1 = {xexit, yexit , w , w};
    SDL_Surface *exit = SDL_LoadBMP("exit.bmp");
    SDL_Texture *aks1 = SDL_CreateTextureFromSurface(renderer, exit);

    SDL_Rect size2 = {xhappy, yhappy , ww , hh};
    SDL_Surface *happy = SDL_LoadBMP("happy.bmp");
    SDL_Texture *aks2 = SDL_CreateTextureFromSurface(renderer, happy);

    SDL_Surface *sad = SDL_LoadBMP("sad.bmp");
    SDL_Texture *aks3 = SDL_CreateTextureFromSurface(renderer, sad);

    SDL_Surface *nothing = SDL_LoadBMP("nothing.bmp");
    SDL_Texture *aks4 = SDL_CreateTextureFromSurface(renderer, nothing);

    SDL_Event event;
    int c=0;
    while (running && hend)
    {
        c++;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &andaze);
        SDL_RenderCopy(renderer, aks, NULL, &size);
        SDL_RenderCopy(renderer, aks1, NULL, &size1);
        if (win)
        {
            SDL_RenderCopy(renderer, aks2, NULL, &size2);
            text(renderer, 360, 50, "YOU WON!", 56, 40, 70, 200, 255);
        }
        else if (lose)
        {
            SDL_RenderCopy(renderer, aks3, NULL, &size2);
            text(renderer, 360, 50, "YOU LOST!", 56, 40, 70, 200, 255);
        }
        else
        {
            SDL_RenderCopy(renderer, aks4, NULL, &size2);
            text(renderer, 345, 50, "GAME ENDED!", 56, 40, 70, 200, 255);
        }
        SDL_PollEvent(&event);
        SDL_RenderPresent(renderer);
        if (event.type == SDL_QUIT)
            running=false;
        if (event.type==SDL_MOUSEBUTTONDOWN)
        {
            double x = event.motion.x;
            double y = event.motion.y;
            if (x >= xrestart && x <= xrestart + w && y >= yrestart && y <= yrestart + w)
            {
                hend=false;
                hmenu=true;
            }
            else if (x >= xexit && x <= xexit + w && y >= yexit && y <= yexit + w) //quit
                running = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(background);
    SDL_DestroyTexture(img);
}

void settingsmenu(SDL_Window *window)
{
    int xbackicon=0, ybackicon=495, hbackicon=70, wbackicon=70;
    double a=1, ax=0, ay=0;
    double b=1, bx=0, by=0;
    double c=1, cx=0, cy=0;
    double d=1, dx=0, dy=0;
    double e=1, ex=0, ey=0;
    int xback1=45, yback1=120, hback1=150, wback1=240;
    int xback2=330, yback2=120, hback2=150, wback2=240;
    int xback3=615, yback3=120, hback3=150, wback3=240;
    int xsound1=205, ysound1=380, hsound1=80, wsound1=500;
    int xsound2=205, ysound2=450, hsound2=80, wsound2=500;
    int xmute=800, ymute=495, w=70;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background = SDL_LoadBMP("backgroundsettings.bmp");
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Rect size = {xbackicon, ybackicon , wbackicon , hbackicon};
    SDL_Surface *backicon = SDL_LoadBMP("backicon.bmp");
    SDL_Texture *aks = SDL_CreateTextureFromSurface(renderer, backicon);

    SDL_Rect size6 = {xmute, ymute , w , w};
    SDL_Surface *mute = SDL_LoadBMP("mute.bmp");
    SDL_Texture *aks6 = SDL_CreateTextureFromSurface(renderer, mute);

    SDL_Rect size7 = {xmute, ymute, w , w};
    SDL_Surface *unmute = SDL_LoadBMP("unmute.bmp");
    SDL_Texture *aks7 = SDL_CreateTextureFromSurface(renderer, unmute);

    SDL_Event event;
    {
        while (running && hsettings)
        {
            SDL_PollEvent(&event);
            SDL_RenderPresent(renderer);
            if (event.type == SDL_QUIT)
                running=false;
            if(event.type== SDL_MOUSEBUTTONDOWN)
            {
                double x=event.motion.x;
                double y=event.motion.y;
                if (x>=xbackicon && x<=xbackicon+wbackicon && y>=ybackicon && y<= ybackicon+hbackicon)
                {
                    hsettings=false;
                    hmenu=true;
                }
                else if (x>=xback1 && x<=xback1+wback1 && y>=yback1 && y<= yback1+hback1)
                {
                    a=1.2;ax=24;ay=15;
                    b=1;bx=0;by=0;
                    c=1;cx=0;cy=0;
                    chosenbackground=1;
                }
                else if (x>=xback2 && x<=xback2+wback2 && y>=yback2 && y<= yback2+hback2)
                {
                    a=1;ax=0;ay=0;
                    b=1.2;bx=24;by=15;
                    c=1;cx=0;cy=0;
                    chosenbackground=2;
                }
                else if (x>=xback3 && x<=xback3+wback3 && y>=yback3 && y<= yback3+hback3)
                {
                    a=1;ax=0;ay=0;
                    b=1;bx=0;by=0;
                    c=1.2;cx=24;cy=15;
                    chosenbackground=3;
                }
                else if (x>=xsound1 && x<=xsound1+wsound1 && y>=ysound1 && y<= ysound1+hsound1)
                {
                    e=1;ex=0;ey=0;
                    d=1.2;dx=50;dy=8;
                    Mix_PlayMusic( music1, -1 );
                }
                else if (x>=xsound2 && x<=xsound2+wsound2 && y>=ysound2 && y<= ysound2+hsound2)
                {
                    d=1;dx=0;dy=0;
                    e=1.2;ex=50;ey=8;
                    Mix_PlayMusic( music2, -1 );
                }
                else if (x>=xmute && x<=xmute+w && y>=ymute && y<=ymute+w)//sound
                {
                    if(!mutee)
                    {
                        mutee=true;
                        Mix_PauseMusic();
                    }
                    else
                    {
                        mutee=false;
                        Mix_ResumeMusic();
                    }
                }
            }
            SDL_Rect size1 = {xback1-ax, yback1-ay , wback1*a , hback1*a};
            SDL_Surface *back1 = SDL_LoadBMP("background1.bmp");
            SDL_Texture *aks1 = SDL_CreateTextureFromSurface(renderer, back1);

            SDL_Rect size2 = {xback2-bx, yback2-by , wback2*b , hback2*b};
            SDL_Surface *back2 = SDL_LoadBMP("background2.bmp");
            SDL_Texture *aks2 = SDL_CreateTextureFromSurface(renderer, back2);

            SDL_Rect size3 = {xback3-cx, yback3-cy , wback3*c , hback3*c};
            SDL_Surface *back3 = SDL_LoadBMP("background3.bmp");
            SDL_Texture *aks3 = SDL_CreateTextureFromSurface(renderer, back3);

            SDL_Rect size4 = {xsound1-dx, ysound1-dy , wsound1*d , hsound1*d};
            SDL_Surface *sound1 = SDL_LoadBMP("sound1.bmp");
            SDL_Texture *aks4 = SDL_CreateTextureFromSurface(renderer, sound1);

            SDL_Rect size5 = {xsound2-ex, ysound2-ey , wsound2*e , hsound2*e};
            SDL_Surface *sound2 = SDL_LoadBMP("sound2.bmp");
            SDL_Texture *aks5 = SDL_CreateTextureFromSurface(renderer, sound2);

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, img, NULL, &andaze);
            text(renderer, 270, 50, "CHOOSE YOUR BACKGROUND", 42, 255,255,255,255);
            text(renderer, 315, 320, "CHOOSE YOUR MUSIC", 42, 255,255,255,255);
            SDL_RenderCopy(renderer, aks, NULL, &size);
            SDL_RenderCopy(renderer, aks1, NULL, &size1);
            SDL_RenderCopy(renderer, aks2, NULL, &size2);
            SDL_RenderCopy(renderer, aks3, NULL, &size3);
            SDL_RenderCopy(renderer, aks4, NULL, &size4);
            SDL_RenderCopy(renderer, aks5, NULL, &size5);
            if (!mutee)
                SDL_RenderCopy(renderer, aks6, NULL, &size6);
            else
                SDL_RenderCopy(renderer, aks7, NULL, &size7);
            SDL_DestroyTexture(aks1);
            SDL_FreeSurface(back1);
            SDL_DestroyTexture(aks2);
            SDL_FreeSurface(back2);
            SDL_DestroyTexture(aks3);
            SDL_FreeSurface(back3);
            SDL_DestroyTexture(aks4);
            SDL_FreeSurface(sound1);
            SDL_DestroyTexture(aks5);
            SDL_FreeSurface(sound2);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(background);
    SDL_DestroyTexture(img);
}

void startmenu (SDL_Window *window)
{
    int xbackicon=0, ybackicon=495, hbackicon=70, wbackicon=70;
    int xrandom=120, yrandom=200, hrandom=250, wrandom=250;
    int xtest=550, ytest=150, htest=100, wtest=200;
    int xmap1=550, ymap1=270, hmap1=100, wmap1=200;
    int xmap2=550, ymap2=390, hmap2=100, wmap2=200;
    int xbox1=35, ybox1=400, hbox1=70, wbox1=200;
    int xbox2=255, ybox2=400, hbox2=70, wbox2=200;
    int a=0;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background = SDL_LoadBMP("backgroundstartmenu.bmp");
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Rect size = {xbackicon, ybackicon , wbackicon , hbackicon};
    SDL_Surface *backicon = SDL_LoadBMP("backicon.bmp");
    SDL_Texture *aks = SDL_CreateTextureFromSurface(renderer, backicon);

    SDL_Rect size1 = {xrandom, yrandom , wrandom , hrandom};
    SDL_Surface *random = SDL_LoadBMP("random.bmp");
    SDL_Texture *aks1 = SDL_CreateTextureFromSurface(renderer, random);

    SDL_Rect size2 = {xtest, ytest , wtest , htest};
    SDL_Surface *test = SDL_LoadBMP("tes.bmp");
    SDL_Texture *aks2 = SDL_CreateTextureFromSurface(renderer, test);

    SDL_Rect size3 = {xmap1, ymap1 , wmap1, hmap1};
    SDL_Surface *map1 = SDL_LoadBMP("mapone.bmp");
    SDL_Texture *aks3 = SDL_CreateTextureFromSurface(renderer, map1);

    SDL_Rect size4 = {xmap2, ymap2 , wmap2 , hmap2};
    SDL_Surface *map2 = SDL_LoadBMP("maptwo.bmp");
    SDL_Texture *aks4 = SDL_CreateTextureFromSurface(renderer, map2);

    int c=0, i1=0, i2=0;
    char numa[3]="", nump[3]="";

    bool type=false, ok1=false, ok2=false, quit1=false, quit2=false;

    SDL_Event event;
    {
        while (running && hstart)
        {
            c++;
            SDL_Rect size1 = {xrandom, yrandom - a, wrandom, hrandom};
            SDL_Surface *random = SDL_LoadBMP("random.bmp");
            SDL_Texture *aks1 = SDL_CreateTextureFromSurface(renderer, random);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, img, NULL, &andaze);
            SDL_RenderCopy(renderer, aks, NULL, &size);
            SDL_RenderCopy(renderer, aks1, NULL, &size1);
            SDL_RenderCopy(renderer, aks2, NULL, &size2);
            SDL_RenderCopy(renderer, aks3, NULL, &size3);
            SDL_RenderCopy(renderer, aks4, NULL, &size4);
            if (type)
            {
                SDL_Rect size10 = {xbox1, ybox1, wbox1, hbox1};
                SDL_Surface *box1 = SDL_LoadBMP("a.bmp");
                SDL_Texture *aks10 = SDL_CreateTextureFromSurface(renderer, box1);

                SDL_Rect size11 = {xbox2, ybox2, wbox2, hbox2};
                SDL_Surface *box2 = SDL_LoadBMP("a.bmp");
                SDL_Texture *aks11 = SDL_CreateTextureFromSurface(renderer, box2);

                SDL_RenderCopy(renderer, aks10, NULL, &size10);
                SDL_RenderCopy(renderer, aks11, NULL, &size11);

                SDL_FreeSurface(box1);
                SDL_DestroyTexture(aks10);
                SDL_FreeSurface(box2);
                SDL_DestroyTexture(aks11);
            }
            SDL_PollEvent(&event);
            text(renderer, 280, 50, "CHOSE YOUR MAP!", 56, 0, 0, 0, 255);
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                double x = event.motion.x;
                double y = event.motion.y;
                if (x >= xbackicon && x <= xbackicon + wbackicon && y >= ybackicon && y <= ybackicon + hbackicon)
                {
                    hmenu = true;
                    hstart = false;
                }
                if (x >= xrandom && x <= xrandom + wrandom && y >= yrandom && y <= yrandom + hrandom)//random
                {
                    if (!type)
                    {
                        a = 100;
                        maps = 0;
                        type = true;
                    }
                    else if (numberofareas !=0 && numberofplayers!=0)
                    {
                        hmap=true;
                        hstart=false;
                    }
                }
                if (x >= xmap1 && x <= xmap1 + wmap1 && y >= ymap1 && y <= ymap1 + hmap1)//1
                {
                    maps = 1;
                    hmap = true;
                    hstart = false;
                }
                if (x >= xmap2 && x <= xmap2 + wmap2 && y >= ymap2 && y <= ymap2 + hmap2)//2
                {
                    maps = 2;
                    hmap = true;
                    hstart = false;
                }
                if (x >= xtest && x <= xtest + wtest && y >= ytest && y <= ytest + htest)//3
                {
                    maps = 3;
                    hmap = true;
                    hstart = false;
                }
                if (x >= xbox1 && x <= xbox1 + wbox1 && y >= ybox1 && y <= ybox1 + hbox1 && type)
                    ok1 = true;
                if (x >= xbox2 && x <= xbox2 + wbox2 && y >= ybox2 && y <= ybox2 + hbox2 && type)
                    ok2 = true;
            }
            if (ok1 && !quit1)
            {
                char ch = 'm';
                if (event.type == SDL_KEYUP)
                {
                    if (event.key.keysym.sym == SDLK_BACKSPACE && i1 > 0)
                    {
                        numa[i1 - 1] = '\0';
                        i1--;
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN)
                        quit1 = true;
                    else
                        ch = event.key.keysym.sym;

                    if ((ch >= '0' && ch <= '9'))
                        numa[i1++] = ch;
                }
            }
            if (strlen(numa) != 0)
            {
                text(renderer, xbox1 + 75, ybox1 + 15, numa, 56, 0, 0, 0, 255);
            }
            numberofareas = atoi(numa);
            if (ok2 && !quit2)
            {
                char ch = 'm';
                if (event.type == SDL_KEYUP)
                {
                    if (event.key.keysym.sym == SDLK_BACKSPACE && i2 > 0)
                    {
                        nump[i2 - 1] = '\0';
                        i2--;
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN)
                        quit2 = true;
                    else
                        ch = event.key.keysym.sym;

                    if ((ch >= '0' && ch <= '9'))
                    {
                        nump[i2++] = ch;
                    }
                }
            }
            if (strlen(nump)!= 0)
            {
                text(renderer, xbox2 + 85, ybox2 + 15, nump, 56, 0, 0, 0, 255);
            }
            numberofplayers = atoi(nump);

            SDL_RenderPresent(renderer);
            SDL_FreeSurface(random);
            SDL_DestroyTexture(aks1);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(background);
    SDL_DestroyTexture(img);
}

void rankingmenu(SDL_Window *window)
{
    struct users carbar[40];
    int xname=100, yname=20;
    int xbord=350, ybord=20;
    int xmosavi=470, ymosavi=20;
    int xbakht=590, ybakht=20;
    int xscore=700,yscore=20;
    int x1=20, y1=90;
    int x2=20, y2=162;
    int x3=20, y3=234;
    int x4=20, y4=306;
    int x5=20, y5=378;
    int xbackicon=0, ybackicon=495, hbackicon=70, wbackicon=70;
    readfile(carbar);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    SDL_Rect andaze = {0, 0 , SCREEN_WIDTH , SCREEN_HEIGHT};
    SDL_Surface *background = SDL_LoadBMP("backgroundranking.bmp");
    SDL_Texture *img = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Rect size = {xbackicon, ybackicon , wbackicon , hbackicon};
    SDL_Surface *backicon = SDL_LoadBMP("backicon.bmp");
    SDL_Texture *aks = SDL_CreateTextureFromSurface(renderer, backicon);

    SDL_Event event;
    while (running && hranking)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, img, NULL, &andaze);
        SDL_RenderCopy(renderer, aks, NULL, &size);
        text(renderer, xname, yname, "NAME", 48, 0, 0,0, 255);
        text(renderer, xbord, ybord, "W", 48, 0, 0,0, 255);
        text(renderer, xmosavi, ymosavi, "D", 48, 0, 0,0, 255);
        text(renderer, xbakht, ybakht, "L", 48, 0, 0,0, 255);
        text(renderer, xscore, yscore, "SCORE", 48, 0, 0,0, 255);
        text(renderer, x1, y1, "1", 48, 0, 0,0, 255);
        text(renderer, x2, y2, "2", 48, 0, 0,0, 255);
        text(renderer, x3, y3, "3", 48, 0, 0,0, 255);
        text(renderer, x4, y4, "4", 48, 0, 0,0, 255);
        text(renderer, x5, y5, "5", 48, 0, 0,0, 255);
        for (int i=0; i<5; i++)
        {
            char win[3], lose[3], draw[3], score[7];
            sprintf(win, "%d", carbar[i].win);
            sprintf(lose, "%d", carbar[i].lose);
            sprintf(draw, "%d", carbar[i].draw);
            sprintf(score, "%d", carbar[i].score);
            text(renderer, xname, y1 + 72*i, carbar[i].name, 48, 0, 0,0, 255);
            text(renderer, xbord, y1 + 72*i, win, 48, 0, 0,0, 255);
            text(renderer, xbakht, y1 + 72*i, lose, 48, 0, 0,0, 255);
            text(renderer, xmosavi, y1 + 72*i, draw, 48, 0, 0,0, 255);
            text(renderer, xscore, y1 + 72*i, score, 48, 0, 0,0, 255);
        }
        SDL_PollEvent(&event);
        SDL_RenderPresent(renderer);
        if (event.type == SDL_QUIT)
            running=false;
        if(event.type== SDL_MOUSEBUTTONDOWN)
        {
            double x=event.motion.x;
            double y=event.motion.y;
            if (x>=xbackicon && x<=xbackicon+wbackicon && y>=ybackicon && y<= ybackicon+hbackicon)
            {
                hranking=false;
                hmenu=true;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(background);
    SDL_DestroyTexture(img);
}