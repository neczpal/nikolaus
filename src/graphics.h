#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED


#include<stdlib.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_image.h>
#include "maps.h"
#include "scores.h"

#define Graphics struct graphics
#define GRAY 0xBBBAAAAA
#define RED 0x800000FF
#define YELLOW 0xf65f45FF
#define GREEN 0x067120FF


#define NIK_W 32
#define NIK_H 48

#define HAUS_W 52
#define HAUS_H 52

#define KID_W 24
#define KID_H 24

#define KERET 54

#define Score struct score

Graphics{
    SDL_Surface* kids;
    SDL_Surface* houses;
    SDL_Surface* nikolaus;
    SDL_Surface* nordpole;
};

Graphics load_graphics();
void free_graphics(Graphics* g);

void draw_nikolaus(Map* m, Graphics* g, SDL_Surface* screen);
void draw_house(int x, int y, Graphics* g, SDL_Surface* screen);
void draw_nordpole(int x, int y, Graphics* g, SDL_Surface* screen);
void draw_kid(int x, int y, Graphics* g, SDL_Surface* screen);

void draw_option(int x, int y, const char* lvl, Graphics* g, Uint32 color, SDL_Surface* screen);
void draw_menu(const char* info, Graphics* g, Score* scr, SDL_Surface* screen);
void draw_map(Map* m, Graphics* g, SDL_Surface* screen);

#endif // GRAPHICS_H_INCLUDED
