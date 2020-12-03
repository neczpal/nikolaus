#include "map_gen.h"

int dist(int x1, int y1, int x2, int y2){
    return (int)(sqrt(pow(x1 - (double)x2, 2) + pow(y1 - (double)y2, 2)));
}
int gut(Graph* g, int *m, int i){
    int j;
    if (g->matrix[m[i-1]][m[i]] == -1)
        return 0;

    if (i == g->N-1 && g->matrix[m[i]][0] == -1){
        return 0;
    }

    for (j = 0; j < i; j++){
        if (m[j] == m[i])
            return 0;
    }

    return 1;
}

/**
    Liefiert ein Array mit die 3 kuerzesten Hamilton-Kreislaenge
    Graph soll mindestens 1 Hamilton-Kreis haben, oder es liefiert nicht sinnvoll Datei
*/
int* brute_force(Graph* g){
    int *m = malloc(sizeof(int) * (g->N+1));//Menge der Weg
    int *s = malloc(sizeof(int) * (g->N+1));//Gewicht
    int *best = malloc(sizeof(int) * 3);   //3 kuerzeste Hamilton-Kreis

    int i = 1;
    int tmp;

    best[0] = 999999999;//1. Best
    best[1] = 999999999;//2. Best
    best[2] = 999999999;//3. Best

    m[0] = 0;
    s[0] = 0;
    m[1] = 1;

    while (i != 0){
        while (m[i] != g->N && !gut(g, m, i)){
            ++m[i];
        }

        if (m[i] == g->N){
            --i;
            ++m[i];
        }else{
            s[i] = s[i-1] + g->matrix[m[i-1]][m[i]];
            ++i;
            m[i] = 0;

            if (i == g->N){
                tmp = s[i-1]+g->matrix[m[i-1]][0];

                if (tmp < best[0]){
                    best[2] = best[1];
                    best[1] = best[0];
                    best[0] = tmp;
                }else
                if(tmp < best[1] && tmp != best[0]){
                    best[2] = best[1];
                    best[1] = tmp;
                }else
                if(tmp < best[2] && tmp != best[1] && tmp != best[0]){
                    best[2] = tmp;
                }

                --i;
                ++m[i];
            }
        }
    }
    free(m);
    free(s);
    return best;
}

/**
    Liest ein Rohfile und liefiert das Graph
*/
Graph load_graph(const char* file_name){
    int i, j, von, zu;
    FILE* f = fopen(file_name, "r");
    Graph g;

    fscanf(f, "%d", &(g.N));
    fscanf(f, "%d", &(g.M));

    g.matrix = (int**) malloc(sizeof(int*) * g.N);
    for(i = 0; i < g.N; i++){
        g.matrix[i] = (int*) malloc(sizeof(int) * g.N);
    }

    g.x = (int*) malloc(sizeof(int) * g.N);
    g.y = (int*) malloc(sizeof(int) * g.N);

    g.von_arr = (int*) malloc(sizeof(int) * g.M);
    g.zu_arr = (int*) malloc(sizeof(int) * g.M);

    for(i = 0; i < g.N; i++){
        fscanf(f, "%d", &g.x[i]);
        fscanf(f, "%d", &g.y[i]);
    }

    for(i = 0; i < g.N; i++){
        for(j = 0; j < g.N; j++){
            g.matrix[i][j] = -1;
        }
    }


    for(i = 0; i < g.M; i++){
        fscanf(f, "%d", &von);
        fscanf(f, "%d", &zu);

        g.von_arr[i] = von;
        g.zu_arr[i]  = zu;

        g.matrix[von][zu] = dist(g.x[von], g.y[von], g.x[zu], g.y[zu]);
        g.matrix[zu][von] = g.matrix[von][zu];
    }

    fclose(f);

    return g;
}
void free_graph(Graph* g){
    int i;
    for(i = 0; i < g->N; i++){
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g->x);
    free(g->y);
    free(g->von_arr);
    free(g->zu_arr);
}
void write_graph(const char* file_name, Graph* g){
    int i;
    FILE* f = fopen(file_name, "w");
    fprintf(f, "%d " , g->N);
    fprintf(f, "%d\n", g->M);

    for(i = 0; i < g->N; i++){
        fprintf(f, "%d " , g->x[i]);
        fprintf(f, "%d\n", g->y[i]);
    }

    for(i = 0; i < g->M; i++){
        fprintf(f, "%d " , g->von_arr[i]);
        fprintf(f, "%d\n", g->zu_arr[i]);
    }

    int* best_drei = brute_force(g);
    for(i = 0; i < 3; i++){
        fprintf(f, "%d\n" , best_drei[i]);
    }
    free(best_drei);
    fclose(f);
}

void convert(const char* in, const char* out){
    Graph g = load_graph(in);
    write_graph(out, &g);
    free_graph(&g);
}
int main(int argc, char *argv[]){
    if(argc == 3)
        convert(argv[1], argv[2]);
    else
        printf("Invalid arguments!!!\n");
    return 0;
}
