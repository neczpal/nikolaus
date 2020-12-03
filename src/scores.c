#include "scores.h"

Score load_scores(){
    Score scr;
    int map_i, score_i, i;
    FILE* f = fopen("scores.txt", "r");

    //Falls scores.txt nicht existiert
    if (f == NULL) {
        for(i = 0;i < 16; i++){//16 Map van
            scr.scores[i] = 0;
        }
    } else {
        for(i = 0;i < 16; i++){//16 Map van
            fscanf(f, "%d", &map_i);
            fscanf(f, "%d", &score_i);
            scr.scores[map_i] = score_i;
        }
    fclose(f);
    }

    return scr;
}
void new_score(Score* scr, int map_i, int score_i){
    if(scr->scores[map_i] < score_i){
        scr->scores[map_i] = score_i;
    }
}
void save_score(Score* scr){
    int i;
    FILE* f = fopen("scores.txt", "w");
    for(i = 0;i < 16; i++){//16 Map van
        fprintf(f, "%d %d\n", i, scr->scores[i]);
    }
    fclose(f);
}
int klick_menu(int x, int y, Score* scr){
    int i, j;

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(KERET + i*(HAUS_W+KERET) <= x && x <= KERET + i*(HAUS_W+KERET)+HAUS_W &&
               KERET + j*(HAUS_H+KERET) <= y && y <= KERET + j*(HAUS_H+KERET)+HAUS_H && (scr->scores[MAX(j*4+i-1, 0)] > 0 || j*4+i == 0)){
                    return j*4+i+1;
               }
        }
    }
    return 0;
}
