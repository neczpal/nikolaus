#include <SDL_events.h>
#include "utils.h"

int dist(int x1, int y1, int x2, int y2){
    return (int)(sqrt(pow(x1 - (double)x2, 2) + pow(y1 - (double)y2, 2)));
}
double distd(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
int ist_in_kreis(int x1, int y1, int x2, int y2){
    return pow(x1-x2, 2) + pow(y1-y2, 2) <= R2;
}

char* to_mapname(int target){
    char buffer[20];

//    itoa(target, buffer, 10);
    int length = snprintf (buffer, 20, "%d",  target);
    strcat(buffer, ".txt");

    return buffer;
}
Uint32 my_timer(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}
