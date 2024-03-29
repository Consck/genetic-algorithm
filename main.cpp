#include "GA_one.h"
#include "time.h"
/*构建有向图的邻接矩阵表示
void CreateMGraph(MGraph G){
   int i,j,k;
   cout<<"输入顶点数和边数:";
   cin>>G.numVertexes>>G.numEdges;
   for(i=1;i<=G.numVertexes;i++)
	  scanf(&G.vexs[i]);  //读入顶点信息，建立顶点表
   for(i=1;i<=G.numVertexes;i++)
	  for(j=1;j<=G.numVertexes;j++)
		 G.arc[i][j]=0;  //邻接矩阵初始化
   for(k=0;k<G.numEdges;k++){ //给边表赋值
	  cout<<"输入第"<<k+1<<"条边的起始点（结点编号从1开始）：\n";
	  scanf("%d %d",&i,&j);  //输入边（vi,vj）
	  G.arc[i][j]=1;  //有向图
   }
   cout<<"图的邻接矩阵："<<endl;
   //输出邻接矩阵
   for(i=1;i<=G.numVertexes;i++){
	for(j=1;j<=G.numVertexes;j++){
		cout<<G.arc[i][j]<<" ";
	  }
	  cout<<endl;
   }
}*/
//硬编码一张有向图G
MGraph CreateMGraph(MGraph G) {
	G.numVertexes = 6;
	G.numEdges = 9;
	int i, j;
	for (i = 1; i <= G.numVertexes; i++) {
		G.vexs[i] = i;
	}
	for (i = 1; i <= G.numVertexes; i++)
		for (j = 1; j <= G.numVertexes; j++)
			G.arc[i][j] = 0;  //邻接矩阵初始化
	G.arc[1][2] = 1;
	G.arc[2][3] = 1;
	G.arc[3][4] = 1;
	G.arc[4][2] = 1;
	G.arc[1][4] = 1;
	G.arc[6][4] = 1;
	G.arc[6][1] = 1;
	G.arc[5][4] = 1;
	G.arc[5][6] = 1;
	//输出邻接矩阵
	for (i = 1; i <= G.numVertexes; i++) {
		for (j = 1; j <= G.numVertexes; j++) {
			cout << G.arc[i][j] << " ";
		}
		cout << endl;
	}
	return G;
}
//硬编码一张有向图A
MGraph CreateMGraphA(MGraph G) {
	G.numVertexes = 6;
	G.numEdges = 9;
	int i, j;
	for (i = 1; i <= G.numVertexes; i++) {
		G.vexs[i] = i;
	}
	for (i = 1; i <= G.numVertexes; i++)
		for (j = 1; j <= G.numVertexes; j++)
			G.arc[i][j] = 0;  //邻接矩阵初始化
	G.arc[1][2] = 1;
	G.arc[2][3] = 1;
	G.arc[3][4] = 1;
	G.arc[2][4] = 1;
	G.arc[1][4] = 1;
	G.arc[6][4] = 1;
	G.arc[6][1] = 1;
	G.arc[5][4] = 1;
	G.arc[5][6] = 1;
	//输出邻接矩阵
	for (i = 1; i <= G.numVertexes; i++) {
		for (j = 1; j <= G.numVertexes; j++) {
			cout << G.arc[i][j] << " ";
		}
		cout << endl;
	}
	return G;
}
//硬编码一张有向图H
MGraph CreateMGraphH(MGraph G) {
	G.numVertexes = 3;
	G.numEdges = 3;
	int i, j;
	for (i = 1; i <= G.numVertexes; i++) {
		G.vexs[i] = i;
	}
	for (i = 1; i <= G.numVertexes; i++)
		for (j = 1; j <= G.numVertexes; j++)
			G.arc[i][j] = 0;  //邻接矩阵初始化
	G.arc[1][2] = 1;
	G.arc[1][3] = 1;
	G.arc[2][3] = 1;
	//输出邻接矩阵
	for (i = 1; i <= G.numVertexes; i++) {
		for (j = 1; j <= G.numVertexes; j++) {
			cout << G.arc[i][j] << " ";
		}
		cout << endl;
	}
	return G;
}

MGraph CreateMGraphQ(MGraph G) {
	G.numVertexes = 7;
	G.numEdges = 8;
	int i, j;
	for (i = 1; i <= G.numVertexes; i++) {
		G.vexs[i] = i;
	}
	for (i = 1; i <= G.numVertexes; i++)
		for (j = 1; j <= G.numVertexes; j++)
			G.arc[i][j] = 0;  //邻接矩阵初始化
	G.arc[1][2] = 1;
	G.arc[1][3] = 1;
	//G.arc[2][3] = 1;
	G.arc[2][4] = 1;
	G.arc[2][5] = 1;
	G.arc[4][6] = 1;
	G.arc[5][6] = 1;
	G.arc[6][7] = 1;
	G.arc[3][7] = 1;
	//输出邻接矩阵
	for (i = 1; i <= G.numVertexes; i++) {
		for (j = 1; j <= G.numVertexes; j++) {
			cout << G.arc[i][j] << " ";
		}
		cout << endl;
	}
	return G;
}


MGraph CreateMGraphW(MGraph G) {
	G.numVertexes = 8;
	G.numEdges = 9;
	int i, j;
	for (i = 1; i <= G.numVertexes; i++) {
		G.vexs[i] = i;
	}
	for (i = 1; i <= G.numVertexes; i++)
		for (j = 1; j <= G.numVertexes; j++)
			G.arc[i][j] = 0;  //邻接矩阵初始化
	G.arc[1][2] = 1;
	G.arc[2][3] = 1;
	G.arc[2][4] = 1;
	G.arc[4][7] = 1;
	G.arc[3][6] = 1;
	G.arc[3][5] = 1;
	G.arc[6][8] = 1;
	G.arc[5][8] = 1;
	G.arc[8][2] = 1;
	//输出邻接矩阵
	for (i = 1; i <= G.numVertexes; i++) {
		for (j = 1; j <= G.numVertexes; j++) {
			cout << G.arc[i][j] << " ";
		}
		cout << endl;
	}
	return G;
}



MGraph CreateMGraphL(MGraph G) {
	G.numVertexes = 13;
	G.numEdges = 18;
	int i, j;
	for (i = 1; i <= G.numVertexes; i++) {
		G.vexs[i] = i;
	}
	for (i = 1; i <= G.numVertexes; i++)
		for (j = 1; j <= G.numVertexes; j++)
			G.arc[i][j] = 0;  //邻接矩阵初始化
	G.arc[1][2] = 1;
	G.arc[1][3] = 1; 
	G.arc[2][3] = 1;
	G.arc[3][4] = 1;
	G.arc[3][5] = 1;
	G.arc[5][4] = 1;
	G.arc[4][6] = 1;
	G.arc[4][7] = 1;
	G.arc[7][8] = 1;
	G.arc[6][9] = 1;
	G.arc[6][10] = 1;
	G.arc[9][11] = 1;
	G.arc[11][10] = 1;
	G.arc[10][12] = 1;
	G.arc[10][13] = 1;
	G.arc[12][13] = 1;
	G.arc[9][13] = 1;
	G.arc[13][3] = 1;
	//输出邻接矩阵
	for (i = 1; i <= G.numVertexes; i++) {
		for (j = 1; j <= G.numVertexes; j++) {
			cout << G.arc[i][j] << " ";
		}
		cout << endl;
	}
	return G;
}
/*顶点排序部分*/
int visited[maxNum];//通过visited数组来标记这个顶点是否被访问过，0表示未被访问，1表示被访问
queue<int>q;
/*宽度优先遍历*/
void bfs(MGraph G, int i, int v[maxNum])
{
	int k, j, n = 1;
	visited[i] = 1;//标记顶点i被访问
	v[n] = i;
	q.push(i);
	while (!q.empty())
	{
		k = q.front();//返回栈顶元素
		q.pop();
		for (j = 1; j <= G.numVertexes; j++)
		{
			if (G.arc[k][j] != 0 && visited[j] == 0)
			{
				visited[j] = 1;
				n++;
				v[n] = j;
				q.push(j);
			}
		}
	}
	cout << "BFS:" << endl;
	for (int l = 1; l <= G.numVertexes; l++) {
		cout << v[l] << " ";
	}
	cout << endl;
}

void BFS(MGraph G, int node[maxNum])
{
	int i;
	//初始化visited数组，表示一开始所有顶点都未被访问过
	for (i = 1; i <= G.numVertexes; i++) {
		visited[i] = 0;
	}
	//广度优先搜索
	for (i = 1; i <= G.numVertexes; i++)
	{
		if (visited[i] == 0)//如果这个顶点为被访问过，则从i顶点出发进行广度优先遍历
			bfs(G, i, node);
	}
	
}

/*按照度数非递增排序（度数=入度+出度）*/
void Degree(MGraph g, int node[maxNum])
{
	// 求图中顶点的入度
	int i, j;
	int *inD = new int[g.numVertexes + 1];
	for (j = 1; j <= g.numVertexes; j++) // 列
	{
		inD[j] = 0;
		for (i = 1; i <= g.numVertexes; i++) // 行
		{
			if (0 != g.arc[i][j])
			{
				inD[j]++;
			}
		}
	}
	/*cout << "入度：" << endl;
	for (int l = 1; l <= g.numVertexes; l++) {
		cout << inD[l] << " ";
	}
	cout << endl;*/

	// 求图中顶点的出度
	int *outD = new int[g.numVertexes + 1];
	for (i = 1; i <= g.numVertexes; i++) // 行
	{
		outD[i] = 0;
		for (j = 1; j <= g.numVertexes; j++) // 列
		{
			if (0 != g.arc[i][j])
			{
				outD[i]++;
			}
		}
	}
	/*cout << "出度：" << endl;
	for (int l = 1; l <= g.numVertexes; l++) {
		cout << outD[l] << " ";
	}
	cout << endl;

	cout << "度：" << endl;*/
	int *D = new int[g.numVertexes + 1];
	//编号初始化
	for (int l = 1; l <= g.numVertexes; l++) {
		node[l] = l;
	}
	for (int l = 1; l <= g.numVertexes; l++) {
		D[l] = inD[l] + outD[l];
		//cout << D[l] << " ";
	}
	//cout << endl;


	int temp;
	/*cout << "qian:" << endl;
	cout << "结点序列:";
	for (i = 1; i <= g.numVertexes; i++) {
		cout << node[i] << " ";
	}
	cout << endl;
	cout << "度数序列:";
	for (i = 1; i <= g.numVertexes; i++) {
		cout << D[i] << " ";
	}
	cout << endl;*/
	for (i = 1; i <= g.numVertexes; i++)
		for (j = 1; j <= g.numVertexes; j++) {
			if (D[j] < D[i]) {
				temp = D[i];
				D[i] = D[j];
				D[j] = temp;
				temp = node[i];
				node[i] = node[j];
				node[j] = temp;
			}
		}
	/*cout << "hou:" << endl;
	cout << "结点序列:";
	for (i = 1; i <= g.numVertexes; i++) {
		cout << node[i] << " ";
	}
	cout << endl;
	cout << "度数序列:";
	for (i = 1; i <= g.numVertexes; i++) {
		cout << D[i] << " ";
	}
	cout << endl;*/
}

int main()
{
	MGraph G, H, A,W,Q,L;
	//MGraph A;
	//int V[maxNum];
	cout << "-------输入第一个图-------" << endl;
	//order();
	A = CreateMGraphA(A);
	cout << endl;
	G = CreateMGraph(G);
	cout << endl;
	H = CreateMGraphH(H);
	//ais3_crakme
	Q = CreateMGraphQ(Q);
	//CADET_0001
	W = CreateMGraphW(W);
	//CADET_0001_ADAPTED
	L = CreateMGraphL(L);
	clock_t t_start, t_end;
	//t_start = time(NULL);
	t_start = clock();
	srand((unsigned)time(NULL));//初始化随机数种子产生器，为使程序中每次的rand()函数产生的随机数不一样
	//srand(5);
	SIP(H,H);
	t_end = clock();
	printf("time: %ld ms\n", t_end - t_start);
	return 0;
}