#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <SDL_types.h>

#define R 25
#define R2 625

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

int dist(int x1, int y1, int x2, int y2);
double distd(double x1, double y1, double x2, double y2);
int ist_in_kreis(int x1, int y1, int x2, int y2);
char* to_mapname(int target);
Uint32 my_timer(Uint32 ms, void *param);

#endif // UTILS_H_INCLUDED
