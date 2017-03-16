#ifndef SCORES_H_INCLUDED
#define SCORES_H_INCLUDED

#include <stdio.h>
#include "graphics.h"

#define Score struct score

Score{
    int scores[16];
};

Score load_scores();
void new_score(Score* scr, int map_i, int score_i);
void save_score(Score* scr);
int klick_menu(int x, int y, Score* scr);
#endif // SCORES_H_INCLUDED
