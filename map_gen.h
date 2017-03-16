#ifndef MAP_GEN_
#define MAP_GEN_

#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Graph struct graph

Graph{
    int **matrix;
    int *x;
    int *y;
    int *von_arr;
    int *zu_arr;
    int N, M;
};

int dist(int x1, int y1, int x2, int y2);
int gut(Graph* g, int *m, int i);
int* brute_force(Graph* g);

Graph load_graph(const char* file_name);
void free_graph(Graph* g);
void write_graph(const char* file_name, Graph* g);
void convert(const char* in, const char* out);
#endif // MAP_GEN_
