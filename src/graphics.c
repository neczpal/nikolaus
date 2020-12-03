#include "graphics.h"

Graphics load_graphics(SDL_Renderer* renderer){
    Graphics g;

    g.kids = IMG_Load("kids.png");
    g.kids_tex = SDL_CreateTextureFromSurface(renderer, g.kids);
    SDL_FreeSurface(g.kids);

    g.nikolaus = IMG_Load("nikolaus.png");
    g.nikolaus_tex = SDL_CreateTextureFromSurface(renderer, g.nikolaus);
    SDL_FreeSurface(g.nikolaus);

    g.houses = IMG_Load("houses.png");
    g.houses_tex = SDL_CreateTextureFromSurface(renderer, g.houses);
    SDL_FreeSurface(g.houses);

    g.nordpole = IMG_Load("nordpole.png");
    g.nordpole_tex = SDL_CreateTextureFromSurface(renderer, g.nordpole);
    SDL_FreeSurface(g.nordpole);

    return g;
}

void free_graphics(Graphics* g){
    SDL_DestroyTexture(g->kids_tex);
    SDL_DestroyTexture(g->houses_tex);
    SDL_DestroyTexture(g->nikolaus_tex);
    SDL_DestroyTexture(g->nordpole_tex);
}

void draw_nikolaus(Map* m, Graphics* g, SDL_Renderer* screen){
    SDL_Rect quelle = {(m->nik_moving) ? (m->nik_i % 4) * NIK_W : 0, m->nik_richtung * NIK_H, NIK_W, NIK_H };
    SDL_Rect ziel   = { (int)m->nik_x - NIK_W/2, (int)m->nik_y  - NIK_H/2, NIK_W, NIK_H };

    SDL_RenderCopy(screen, g->nikolaus_tex, &quelle, &ziel);
}

void draw_house(int x, int y, Graphics* g, SDL_Renderer* screen){
    SDL_Rect quelle = { (x % 5) * HAUS_W, (y % 2) * HAUS_H, HAUS_W, HAUS_H };
    SDL_Rect ziel   = { x-HAUS_W/2, y-HAUS_H/2-25, HAUS_W, HAUS_H };

    SDL_RenderCopy(screen, g->houses_tex, &quelle, &ziel);
}
void draw_nordpole(int x, int y, Graphics* g, SDL_Renderer* screen){
    SDL_Rect quelle = { 0, 0, HAUS_W, HAUS_H };
    SDL_Rect ziel   = { x-HAUS_W/2, y-HAUS_H/2-25, HAUS_W, HAUS_H };

    SDL_RenderCopy(screen, g->nordpole_tex, &quelle, &ziel);
}
void draw_kid(int x, int y, Graphics* g, SDL_Renderer* screen){
    SDL_Rect quelle = { (y % 4) * KID_W, (x % 2) * KID_H, KID_W, KID_H };
    SDL_Rect ziel   = { x-KID_W/2-10, y-KID_H/2, KID_W, KID_H };

    SDL_RenderCopy(screen, g->kids_tex, &quelle, &ziel);
}
void draw_option(int x, int y, const char* lvl, Graphics* g, int red, int green, int blue, int alpha, SDL_Renderer* screen){
    SDL_Rect quelle = { ((2*x+y) % 5) * HAUS_W, ((3*y) % 2) * HAUS_H, HAUS_W, HAUS_H };
    SDL_Rect ziel   = { x, y, HAUS_W, HAUS_H };

    boxRGBA(screen, x,
                    y,
                    x + HAUS_W,
                    y + HAUS_H,
                    red,
                    green,
                    blue,
                    alpha);//



    SDL_RenderCopy(screen, g->houses_tex, &quelle, &ziel);

    stringRGBA(screen, x+HAUS_W/2-4, y+HAUS_H+4, lvl, 255, 255, 255, 255);
}

void draw_menu(const char* info, Graphics* g, Score* scr, SDL_Renderer* screen){
    int i, j;
    char buffer[10];

    boxRGBA(screen, 0, 0, 640, 480, 125, 125, 125, 255);
    SDL_RenderClear(screen);

    stringRGBA(screen, 80, 240, info, 255, 255, 0, 255);

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(scr->scores[MAX(j*4+i-1, 0)] > 0 || j*4+i == 0){
                snprintf (buffer, 10, "%d", j*4+i+1);
                switch(scr->scores[j*4+i]){
                    case 0:
                        draw_option(KERET + i*(HAUS_W+KERET), KERET + j*(HAUS_H+KERET), buffer, g, 175, 175, 175, 255, screen);
                        break;
                    case 1:
                        draw_option(KERET + i*(HAUS_W+KERET), KERET + j*(HAUS_H+KERET), buffer, g, 240, 125, 125, 255, screen);
                        break;
                    case 2:
                        draw_option(KERET + i*(HAUS_W+KERET), KERET + j*(HAUS_H+KERET), buffer, g, 200, 200, 45, 255, screen);
                        break;
                    case 3:
                        draw_option(KERET + i*(HAUS_W+KERET), KERET + j*(HAUS_H+KERET), buffer, g, 120, 240, 120, 255, screen);
                        break;
                }

            }
        }
    }

    boxRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+15, KERET + 4*(HAUS_W+KERET)+15, KERET+30, 175, 175, 175, 255);
    stringRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+35, "Not done.", 255, 255, 0, 255);

    boxRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+45, KERET + 4*(HAUS_W+KERET)+15, KERET+60, 240, 125, 125, 255);
    stringRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+65, "3rd shortest route", 255, 255, 0, 255);

    boxRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+75, KERET + 4*(HAUS_W+KERET)+15, KERET+90, 200, 200, 45, 255);
    stringRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+95, "2nd shortest route.", 255, 255, 0, 255);

    boxRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+105, KERET + 4*(HAUS_W+KERET)+15, KERET+120, 120, 240, 120, 255);
    stringRGBA(screen, KERET + 4*(HAUS_W+KERET), KERET+125, "Shortest route.", 255, 255, 0, 255);

    SDL_RenderPresent(screen);

}

void draw_map(Map* m, Graphics* g, SDL_Renderer* screen){
    int i, j;
    char buffer[20];


    boxRGBA(screen, 0, 0, 640, 480, 125, 145, 175, 255);
    SDL_RenderClear(screen);

    for(i = 0; i < m->N; i++){
        for(j = 0; j < m->N; j++){
            if(m->matrix[i][j] != -1){
                lineRGBA(screen, m->x[i], m->y[i], m->x[j], m->y[j], 255, 255, 255, 255);
            }
        }
    }

    filledCircleRGBA(screen, m->x[0], m->y[0], R, 120, 120, 240, 255);
    draw_nordpole(m->x[0], m->y[0], g, screen);

    for(i = 1; i < m->N; i++){

        if(m->color[i]){
            filledCircleRGBA(screen, m->x[i], m->y[i], R, 120, 240, 120, 255);
            draw_house(m->x[i], m->y[i], g, screen);
        } else{
            filledCircleRGBA(screen, m->x[i], m->y[i], R, 175, 175, 175, 255);
            draw_house(m->x[i], m->y[i], g, screen);
            draw_kid(m->x[i], m->y[i], g, screen);
        }

        snprintf (buffer, 20, "%d", i);
        stringRGBA(screen, m->x[i], m->y[i], buffer, 0, 0, 0, 255);
    }

    snprintf (buffer, 20, "Current: %d", (int) m->weg);
    if (m->weg <= m->best[0]) {
        stringRGBA(screen, 330, 30, buffer, 120, 240, 120, 255);
    } else
    if (m->weg <= m->best[1]) {
        stringRGBA(screen, 330, 30, buffer, 200, 200, 45, 255);
    } else
    if (m->weg <= m->best[2]) {
        stringRGBA(screen, 330, 30, buffer, 240, 125, 125, 255);
    } else {
        stringRGBA(screen, 330, 30, buffer, 255, 0, 0, 255);
    }

    snprintf (buffer, 20, "3: %d", m->best[2]);
    stringRGBA(screen, 330, 60, buffer, 240, 125, 125, 255);

    snprintf (buffer, 20, "2: %d", m->best[1]);
    stringRGBA(screen, 330, 90, buffer, 200, 200, 45, 255);

    snprintf (buffer, 20, "1: %d", m->best[0]);
    stringRGBA(screen, 330, 120, buffer, 120, 240, 120, 255);

    draw_nikolaus(m, g, screen);

    SDL_RenderPresent(screen);
}
