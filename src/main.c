#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_image.h>

#include "maps.h"
#include "utils.h"
#include "graphics.h"
#include "scores.h"

int main(int argc, char *argv[]) {
    int quit, clicked, target, result, temp;
    char* info;
    SDL_TimerID timer_id, tmp;
    SDL_Event event;
    SDL_Surface *screen;

    Score scr = load_scores();
    Map m = load_map("1.txt", 1);//Aktuelle Map (null falls MainMenu)
    info = "\0";
    unload_map(&m);
    Graphics g = load_graphics();

    unload_map(&m);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen=SDL_SetVideoMode(640, 480, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Nikolaus", "Nikolaus");

    quit = 0;

    while (!quit) {
        if(m.loaded)
            draw_map(&m, &g, screen);
        else
            draw_menu(info, &g, &scr, screen);


        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && !clicked){
                    clicked = 1;
                    if(m.loaded){
                        tmp = klick_map(&m, event.button.x, event.button.y);
                        if((int)tmp != -1) timer_id = tmp;
                    }else{
                        if(target = klick_menu(event.button.x, event.button.y, &scr)){
                            free_map(&m);
                            m = load_map(to_mapname(target), target-1);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    clicked = 0;
                }
                break;
            case SDL_USEREVENT:
                if(!bewegen(&m)){
                    SDL_RemoveTimer(timer_id);
                    m.nik_moving = 0;
                    if(result = end_game(&m)){
                        if(result == 1){
                            info = "Du hast verloren! (Zu langes weg/Ausgelasste Knoten/Beschraenkt)";
                            unload_map(&m);
                        }else{
                            if(m.weg <= m.best[0]){
                                temp = 3;
                                info = "Das kuerzeste Weg!!!";
                            }else
                            if(m.weg <= m.best[1]){
                                temp = 2;
                                info = "Das zweite kuerzeste Weg!!";
                            }else{
                                temp = 1;
                                info = "Das dritte kuerzeste Weg!";
                            }
                            new_score(&scr, m.id, temp);
                            unload_map(&m);
                        }
                    }
                }
                break;
            case SDL_QUIT:
                quit=1;
                break;
        }
    }

    save_score(&scr);
    free_map(&m);
    free_graphics(&g);
    SDL_Quit();
    return 0;
}
