#include "graphics.h"

Graphics load_graphics(){
    Graphics g;

    g.kids = IMG_Load("kids.png");
    g.nikolaus = IMG_Load("nikolaus.png");
    g.houses = IMG_Load("houses.png");
    g.nordpole = IMG_Load("nordpole.png");

    return g;
}

void free_graphics(Graphics* g){
    SDL_FreeSurface(g->kids);
    SDL_FreeSurface(g->houses);
    SDL_FreeSurface(g->nikolaus);
    SDL_FreeSurface(g->nordpole);
}

void draw_nikolaus(Map* m, Graphics* g, SDL_Surface* screen){
    SDL_Rect quelle = { (m->nik_moving) ? (m->nik_n % 4) * NIK_W : 0, m->nik_richtung * NIK_H, NIK_W, NIK_H };
    SDL_Rect ziel   = { (int)m->nik_x - NIK_W/2, (int)m->nik_y  - NIK_H/2, NIK_W, NIK_H };

    SDL_BlitSurface(g->nikolaus, &quelle, screen, &ziel);
}

void draw_house(int x, int y, Graphics* g, SDL_Surface* screen){
    SDL_Rect quelle = { (x % 5) * HAUS_W, (y % 2) * HAUS_H, HAUS_W, HAUS_H };
    SDL_Rect ziel   = { x-HAUS_W/2, y-HAUS_H/2-25, HAUS_W, HAUS_H };

    SDL_BlitSurface(g->houses, &quelle, screen, &ziel);
}
void draw_nordpole(int x, int y, Graphics* g, SDL_Surface* screen){
    SDL_Rect quelle = { 0, 0, HAUS_W, HAUS_H };
    SDL_Rect ziel   = { x-HAUS_W/2, y-HAUS_H/2-25, HAUS_W, HAUS_H };

    SDL_BlitSurface(g->nordpole, &quelle, screen, &ziel);
}
void draw_kid(int x, int y, Graphics* g, SDL_Surface* screen){
    SDL_Rect quelle = { (y % 4) * KID_W, (x % 2) * KID_H, KID_W, KID_H };
    SDL_Rect ziel   = { x-KID_W/2-10, y-KID_H/2, KID_W, KID_H };

    SDL_BlitSurface(g->kids, &quelle, screen, &ziel);
}
void draw_option(int x, int y, const char* lvl, Graphics* g, Uint32 color, SDL_Surface* screen){
    SDL_Rect quelle = { ((2*x+y) % 5) * HAUS_W, ((3*y) % 2) * HAUS_H, HAUS_W, HAUS_H };
    SDL_Rect ziel   = { x, y, HAUS_W, HAUS_H };

    boxColor(screen, x,
                    y,
                    x + HAUS_W,
                    y + HAUS_H,
                    color);//

    SDL_BlitSurface(g->houses, &quelle, screen, &ziel);

    stringRGBA(screen, x+HAUS_W/2-4, y+HAUS_H/2-4, lvl, 255, 255, 0, 255);
}

void draw_menu(const char* info, Graphics* g, Score* scr, SDL_Surface* screen){
    int i, j;
    char buffer[10];

    boxColor(screen, 0, 0, 640, 480, 0x70B0EEFF);

    stringRGBA(screen, 80, 240, info, 255, 255, 0, 255);

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(scr->scores[MAX(j*4+i-1, 0)] > 0 || j*4+i == 0){
                itoa(j*4+i+1, buffer, 10);
                switch(scr->scores[j*4+i]){
                    case 0:
                        draw_option(KERET + i*(HAUS_W+KERET), KERET + j*(HAUS_H+KERET), buffer, g, GRAY, screen);
                        break;
                    case 1:
                        draw_option(KERET + i*(HAUS_W+KERET), KERET + j*(HAUS_H+KERET), buffer, g, RED, screen);
                        break;
                    case 2:
                        draw_option(KERET + i*(HAUS_W+KERET), KERET + j*(HAUS_H+KERET), buffer, g, YELLOW, screen);
                        break;
                    case 3:
                        draw_option(KERET + i*(HAUS_W+KERET), KERET + j*(HAUS_H+KERET), buffer, g, GREEN, screen);
                        break;
                }

            }
        }
    }
    boxColor(screen, KERET + 4*(HAUS_W+KERET), KERET+15, KERET + 4*(HAUS_W+KERET)+15, KERET+30, GRAY);
    stringRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+35, "Nicht gemacht.", 255, 255, 0, 255);

    boxColor(screen, KERET + 4*(HAUS_W+KERET), KERET+45, KERET + 4*(HAUS_W+KERET)+15, KERET+60, RED);
    stringRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+65, "3. kuerzeste Weg.", 255, 255, 0, 255);

    boxColor(screen, KERET + 4*(HAUS_W+KERET), KERET+75, KERET + 4*(HAUS_W+KERET)+15, KERET+90, YELLOW);
    stringRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+95, "2. kuerzeste Weg.", 255, 255, 0, 255);

    boxColor(screen, KERET + 4*(HAUS_W+KERET), KERET+105, KERET + 4*(HAUS_W+KERET)+15, KERET+120, GREEN);
    stringRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+125, "1. kuerzeste Weg.", 255, 255, 0, 255);



    SDL_Flip(screen);
}

void draw_map(Map* m, Graphics* g, SDL_Surface* screen){
    int i, j;
    char buffer[10];


    boxColor(screen, 0, 0, 640, 480, 0x70B0EEFF);

    for(i = 0; i < m->N; i++){
        for(j = 0; j < m->N; j++){
            if(m->matrix[i][j] != -1){
                lineRGBA(screen, m->x[i], m->y[i], m->x[j], m->y[j], 255, 255, 255, 255);
            }
        }
    }

    filledCircleRGBA(screen, m->x[0], m->y[0], R, 0, 0, 255, 255);
    draw_nordpole(m->x[0], m->y[0], g, screen);

    for(i = 1; i < m->N; i++){
        if(m->color[i]){
            filledCircleRGBA(screen, m->x[i], m->y[i], R, 255, 0, 0, 255);
            draw_house(m->x[i], m->y[i], g, screen);
        }else{
            filledCircleRGBA(screen, m->x[i], m->y[i], R, 0, 0, 255, 255);
            draw_house(m->x[i], m->y[i], g, screen);
            draw_kid(m->x[i], m->y[i], g, screen);
        }

        itoa(i, buffer, 10);
        stringRGBA(screen, m->x[i], m->y[i], buffer, 0, 0, 0, 255);
    }

    itoa(m->weg, buffer, 10);
    stringRGBA(screen, 30, 30, buffer, 0, 255, 0, 255);

    draw_nikolaus(m, g, screen);

    SDL_Flip(screen);
}
