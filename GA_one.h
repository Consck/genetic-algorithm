#ifndef GA_ONE_H_INCLUDED
#define GA_ONE_H_INCLUDED
#define MAXVER 100  //最大顶点数
#define sizepop 20 // 种群数目
#define maxgen 100 // 进化代数
#define pcross 0.3 // 交叉概率
#define selection 0.3 //选择概率
#define pmutation 0.8 // 变异概率
#include "main.h"

//每一个匹配映射的存储结构
typedef struct Q {
	int first;//G结点
	int second;//H结点
}Q;
//每一个染色体的存储结构
typedef struct P {
	Q h[MAXVER];//未知总个
	int node, edge;
	double fitness;//适应度函数
}P;
extern void GA(int LEN);
extern void SIP(MGraph G, MGraph H);
extern void init(int LEN, MGraph Q, MGraph L, int c);
extern void cal_fitness(int LEN, MGraph Q, MGraph L);
extern int sel();
extern void print(P tmp, int LEN);
extern void printcur(int LEN);
extern void tran(int LEN, MGraph Q, MGraph L);
#endif // GA_ONE_H_INCLUDED
