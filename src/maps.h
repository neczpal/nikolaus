#ifndef MAPS_H_INCLUDED
#define MAPS_H_INCLUDED

#include <SDL.h>
#include<stdlib.h>

#include "utils.h"

#define PLAYER_V 5
#define TIMER_SLEEP 10

#define Map struct map

    Map{
    int N;
    int id;
    int loaded;
    int **matrix;

    int *x;
    int *y;

    int *color;

    int best[3];
    int pos;
    double weg;
    double temp_weg;

    //f�r die Bewegung
    double nik_x;
    double nik_y;
    int nik_i;
    int nik_n;
    double nik_vx;
    double nik_vy;
    int nik_wohin;
    int nik_richtung;
    int nik_moving;

};
Map load_map(const char* map_name, int target);
void unload_map(Map* m);
void free_map(Map* g);
int bewegen(Map* m);
int kann_bewegen(Map* m, int wohin);
SDL_TimerID klick_map(Map* m, int x, int y);
int get_node_at(Map* m, int x, int y);
SDL_TimerID gehen_zu(Map* m, int wohin);
int end_game(Map* m);

#endif // MAPS_H_INCLUDED
