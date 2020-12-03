#include <SDL.h>

#include "maps.h"
#include "utils.h"
#include "graphics.h"
#include "scores.h"

int main(int argc, char *argv[]) {
    int quit, clicked = 0, target, result, temp;
    char* info;
    SDL_TimerID timer_id, tmp;
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *screen;

    Score scr = load_scores();
    Map m = load_map("1.txt", 1);//Aktuelle Map (null falls MainMenu)
    info = "\0";
    unload_map(&m);

    unload_map(&m);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    window = SDL_CreateWindow("Santa Cruise",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              640, 480,
                              0);
//    screen=SDL_SetVideoMode(640, 480, 0, SDL_ANYFORMAT);
//    ();
//
//    screen = SDL_CreateRenderer(window, -1, 0);

    if (!window) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
//    screen = SDL_GetWindowSurface(window);
    screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//    SDL_WM_SetCaption("Nikolaus", "Nikolaus");

    Graphics g = load_graphics(screen);

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
                    result = end_game(&m);
                    if(result != 0){
                        if(result < 0){
//                            info = "Du hast verloren! (Zu langes weg/Ausgelasste Knoten/Beschraenkt)";
                            switch(result) {
                                case -1:
                                    info = "You Lost! (Too long Route)";
                                    break;
                                case -2:
                                    info = "You Lost! (Missed a house)";
                                    break;
                                case -3:
                                    info = "You Lost! (Got stuck)";
                                    break;
                            }

                            unload_map(&m);

                        }else{
                            if(m.weg <= m.best[0]){
                                temp = 3;
//                                info = "Das kuerzeste Weg!!!";
                                info = "You Win! (Shortest Route)";
                            }else
                            if(m.weg <= m.best[1]){
                                temp = 2;
//                                info = "Das zweite kuerzeste Weg!!";
                                info = "You Win! (2nd shortest Route)";
                            }else{
                                temp = 1;
//                                info = "Das dritte kuerzeste Weg!";
                                info = "You Win! (3rd shortest Route)";
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

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
