#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<queue>
#include <string.h>
#include<time.h>
using namespace std;
#define MAXVER 100  //最大顶点数
#define maxNum 100 //定义邻接矩阵的最大定点数
//有向图存储结构
typedef struct {
	int vexs[MAXVER];  //顶点表
	int arc[MAXVER][MAXVER];  //邻接矩阵，边表
	int numVertexes, numEdges; //图中当前顶点数和边数
}MGraph;
extern MGraph CreateMGraph(MGraph G);
extern void bfs(MGraph G, int i, int v[maxNum]);
extern void BFS(MGraph G, int node[maxNum]);
extern void Degree(MGraph g, int node[maxNum]);

#endif // MAIN_H_INCLUDED
