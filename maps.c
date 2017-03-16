#include "maps.h"

Map load_map(const char* map_name, int target){
    int i, j, von, zu, M;

    FILE* f;
    Map g;

    if(map_name[0] == '\0'){
        g.loaded = 0;
        return g;
    }

    f = fopen(map_name, "r");

    fscanf(f, "%d", &(g.N));
    fscanf(f, "%d", &M);

    g.matrix = (int**) malloc(sizeof(int*) * g.N);
    for(i = 0; i < g.N; i++){
        g.matrix[i] = (int*) malloc(sizeof(int) * g.N);
    }

    g.x = (int*) malloc(sizeof(int) * g.N);
    g.y = (int*) malloc(sizeof(int) * g.N);

    g.color = (int*) malloc(sizeof(int) * g.N);

    for(i = 0; i < g.N; i++){
        fscanf(f, "%d", &g.x[i]);
        fscanf(f, "%d", &g.y[i]);
    }


    for(i = 0; i < g.N; i++){
        for(j = 0; j < g.N; j++){
            g.matrix[i][j] = -1;
        }
    }

    for(i = 0; i < M; i++){
        fscanf(f, "%d", &von);
        fscanf(f, "%d", &zu);

        g.matrix[von][zu] = dist(g.x[von], g.y[von], g.x[zu], g.y[zu]);
        g.matrix[zu][von] = g.matrix[von][zu];
    }

    for(i = 0; i < 3; i++){
        fscanf(f, "%d", &g.best[i]);
    }

    for(i = 0; i < g.N; i++){
        g.color[i] = 0;
    }
    g.pos = 0;
    g.weg = 0;
    g.id = target;
    //NIKOLAUS

    g.nik_x = g.x[g.pos];
    g.nik_y = g.y[g.pos];
    g.nik_richtung = 0;
    g.nik_moving = 0;

    g.loaded = 1;
    fclose(f);

    return g;
}

void unload_map(Map* m){
    m->loaded = 0;
}
void free_map(Map* g){
    int i;

    unload_map(g);
    for(i = 0; i < g->N; i++){
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g->x);
    free(g->y);
    free(g->color);
}
int bewegen(Map* m){
	if(m->nik_n <= 0){
        m->color[m->nik_wohin] = 1;
        m->weg += m->matrix[m->pos][m->nik_wohin];
        m->pos = m->nik_wohin;
        m->nik_x = m->x[m->pos];
        m->nik_y = m->y[m->pos];
        m->nik_richtung = 0;
        return 0;
    }else{
        m->nik_x += m->nik_vx;
        m->nik_y += m->nik_vy;
        m->nik_n--;
        return 1;
    }
}


int kann_bewegen(Map* m, int wohin){
    return m->matrix[m->pos][wohin] != -1 && m->color[wohin] == 0;
}
SDL_TimerID klick_map(Map* m, int x, int y){
    int target;
    SDL_TimerID timer_id;
    if(!(m->nik_moving) ){
        target = get_node_at(m, x, y);
        if(target != -1 && kann_bewegen(m, target)){
            timer_id = gehen_zu(m, target);
            m->nik_moving = 1;
            return timer_id;
        }
    }
    return (SDL_TimerID)-1;
}
int get_node_at(Map* m, int x, int y){
    int i;
    for(i = 0; i < m->N; i++){
        if(ist_in_kreis(m->x[i], m->y[i], x, y)){
            return i;
        }
    }
    return -1;
}
SDL_TimerID gehen_zu(Map* m, int wohin){
    double d;
    int distx = m->x[wohin] - m->x[m->pos];
    int disty = m->y[wohin] - m->y[m->pos];

    if(abs(distx) > abs(disty)){
        if(distx > 0){
            m->nik_richtung = 2;
        }else{
            m->nik_richtung = 1;
        }
    }else{
        if(disty > 0){
            m->nik_richtung = 0;
        }else{
            m->nik_richtung = 3;
        }
    }

    m->nik_x = m->x[m->pos];
    m->nik_y = m->y[m->pos];

    d = distd(m->nik_x, m->nik_y, m->x[wohin], m->x[wohin]);
    m->nik_vx = (PLAYER_V*distx) / d;
    m->nik_vy = (PLAYER_V*disty) / d;
    m->nik_n = (int) (d / PLAYER_V + 0.5);
    m->nik_wohin = wohin;

    return SDL_AddTimer(TIMER_SLEEP, my_timer, NULL);
}
int end_game(Map* m){
    int i;
    //weg > 3.beste
    if(m->weg > m->best[2]){
        return 1;
    }
    //kihagyott csucs
    if(m->pos == 0 && m->color[0] == 1){
        for(i = 0; i < m->N; i++){
            if(m->color[i] == 0){
                return 1;
            }
        }
        return 2;
    }
    //beschränkt
    for(i = 0; i < m->N; i++){
        if(kann_bewegen(m, i) && m->color[i] == 0){
            return 0;
        }
    }
    return 1;
}
