#include "GA_one.h"
//全局变量
//P *cur = new P[sizepop+1];
//P *population = new P[sizepop+1]; 
P  cur[sizepop+1], max_one, min_one[sizepop+1];//定义结构体数组，有当前染色体种群，下一代染色体种群，以及最优和最差染色体。
P  population[sizepop + 1];
bool tag_two = true;
//MGraph M;//公共子图
int m[maxgen + 1];
double fitsum;//记录所有染色体适应度之和
//从数组中删除指定元素
int remove(int arr[], int length, int item) {
	for (int i = 1; i < length; i++) {
		if (arr[i] == item) {
			for (int j = i; j < length-1; j++) {
				arr[j] = arr[j + 1];
			}
		}
		break;
	}
	length--;
	return length;
}
//论文中的算法
void SIP(MGraph G, MGraph H) {
	//double ans;
	double similar = 0, judge = 0,vex_num;
	bool tag_one = true;
	int i, j = 1, c = 0,  l, length = G.numVertexes+1, sum_m = 0;
	int *V1 = new int[G.numVertexes+1];
	int *V2 = new int[G.numVertexes + 1];
	vex_num = (1.0 * G.numVertexes + H.numVertexes) / 2;
	//int V1[G.numVertexes], V2[G.numVertexes];
	//初始化max_one
	max_one.fitness = 100;
	//int n = maxgen;//进化代数5
	while (j <= maxgen) {
		m[j] = 1;
		sum_m = m[j] + sum_m;
		if (sum_m > G.numVertexes)
			m[j] = 0;
		j++;
	}
	for (i = 1; i <= G.numVertexes; i++) {
		V1[i] = G.vexs[i];         //取出G的结点序列存为V1
	}
	//cout << "原结点序列：";
	//for (i = 1; i <= G.numVertexes; i++) {
	//	//cout << V1[i] << " ";
	//	V1[i] = i;
	//}
	//cout << endl;
	int LEN = 0;
	init(LEN, G,H, c);//映射初始化操作
	for (i = 1; i <= maxgen; i++) {    //第i代
		//cout << "i:" << i << " maxgen:" << maxgen << endl;
		c = m[i];
		/*cout << "------------第" << i << "代-------" << endl;
		cout << "c = " << c << " m = " << m[i] << endl;*/
		for (j = 1; j <= c; j++) {
			V2[j] = V1[j];           //将每一步要扩展的顶点存储为Vc
		}
		//cout << "要添加的顶点序列：";
		//for (j = 1; j <= c; j++) {
		//	cout << V2[j] << " ";           //将每一步要扩展的顶点存储为Vc
		//}
		//cout << endl;
		for (j = 1; j <= c; j++) {
			length = remove(V1, length, V2[j]);  //从V1中移除扩展的顶点
		}
		//cout << "原序列删掉扩展的结点之后：";
		//for (j = 1; j < length; j++) {
		//	cout << V1[j] << " ";          //将每一步要扩展的顶点存储为Vc
		//}
		//cout << endl;
		for (j = 1; j <= c; j++) {
			//扩展的结点加入映射
			LEN++;
			for (l = 1; l <= sizepop; l++) {
				cur[l].h[LEN].first = V2[j];  //第i代（共n代）种群个数LEN个
			}
		}
		init(LEN,G, H, c);//映射初始化操作-----硬编码一组映射编写适应度计算函数
		//cout << "初始化后的映射：" << endl;
		cal_fitness(LEN, G, H);//计算当前种群适应度
		//cout << "" << endl;
		//printcur(LEN);
		if (LEN != 1) {   //第一代不交叉
			tran(LEN, G, H);//遗传算法-换代-将当前代交叉变异为最好的一组映射
			if (c == 0) {
				//出现适应度为0时停止
				for (j = 1; j <= sizepop; j++) {
					if (cur[j].fitness == 0)
						tag_one = false;
					break;
				}
			}
			if (tag_two == false) {
				break;
			}
		}
		if (tag_one == false) {
			cout << "最终结果1：" << endl;
			for (j = 1; j <= sizepop; j++) {
				if (cur[j].fitness == 0) {
					for (l = 1; l <= LEN; l++) {
						cout << cur[j].h[l].first << "--------->" << cur[j].h[l].second << " ";
					}
					cout << "不匹配的边数 = " << cur[j].edge;
					cout << " 不匹配的顶点数 = " << cur[j].node;
					cout << " 适应度 = " << cur[j].fitness;
				}
				cout << " vex_num = " << vex_num;
				similar = cur[j].fitness / vex_num;
				cout << "  similar = " << similar << endl;
				break;
			}
			break;
		}
	}
	if (i == maxgen + 1 || tag_two == false) {
		double result = cur[1].fitness;
		for (j = 1; j <= sizepop; j++) {
			if (cur[j].fitness < result)
				result = cur[j].fitness;
		}
		cout << "最终结果2：" << endl;
		if (result < max_one.fitness) {
			for (j = 1; j <= sizepop; j++) {
				if (cur[j].fitness == result) {
					for (l = 1; l <= LEN; l++) {
						cout << cur[j].h[l].first << "--------->" << cur[j].h[l].second << " ";
					}
					cout << "不匹配的边数 = " << cur[j].edge;
					cout << " 不匹配的顶点数 = " << cur[j].node;
					cout << " 适应度 = " << cur[j].fitness;
				}
				//similar = (1 - 10 * cur[j].fitness) / G.numEdges;
				similar = cur[j].fitness / vex_num;
				cout << " vex_num = " << vex_num;
				cout << "  相似度 = " << similar << endl;
				break;
			}
		}
		else {
			for (l = 1; l <= LEN; l++) {
				cout << max_one.h[l].first << "--------->" << max_one.h[l].second << " ";
			}
			cout << "不匹配的边数3 = " << max_one.edge;
			cout << " 不匹配的顶点数 = " << max_one.node;
			cout << " 适应度 = " << max_one.fitness;
			//cout <<  " 边数 = " << G.numEdges;
			//similar = (1 - 10 * cur[j].fitness) / G.numEdges;
			similar = cur[j].fitness / vex_num;
			cout << " vex_num = " << vex_num;
			cout << "  相似度 = " << similar << endl;
		}
	}
	cout << "  graph1_nodes = " << G.numVertexes;
	cout << "  graph2_nodes = " << H.numVertexes<<endl;
	delete(V1);
	delete(V2);
}


//初始化染色体种群，共sizepop个
void init(int LEN,MGraph Q, MGraph L, int c)
{
	int i, j, r, k = 0, f = 0,in_degree ,ou_degree ,a,w;
	int inD = 0, ouD = 0;
	/*cout << "第二张图结点序列：";
	for (i = 1; i < L.numVertexes + 1; i++) {
		cout << L.vexs[i] << " ";
	}
	cout << endl;*/
	if (LEN == 0) {
		for (i = 1; i <= sizepop; i++) //种群数目
		{
			for (j = 1; j <= LEN; j++)
			{
				cur[i].h[j].first = 0;
				cur[i].h[j].second = 0;
			}
		}
	}
	else {
		for (i = 1; i <= sizepop; i++) //种群数目
		{	
			for (j = LEN - c + 1; j <= LEN; j++)
			{
				in_degree = 0;
				ou_degree = 0;
				//取出当前染色体的first 结点
				f = cur[i].h[j].first;
				for (k = 1; k < LEN + 1; k++) {
					//计算结点度数
					if (Q.arc[f][cur[i].h[k].first] == 1) //出度
						ou_degree ++;
					if (Q.arc[cur[i].h[k].first][f] == 1) //入度
						in_degree ++;
				}
 
				r = rand() % L.numVertexes + 1;
				for (k = 1; k <= j; k++) {
					if (cur[i].h[k].second == r) {
						r = rand() % L.numVertexes + 1;
						k = 0;
					}

					if (LEN < L.numVertexes && k != 0 ) {
						a = L.vexs[r];
						inD = 0;
						ouD = 0;
						//计算入度
						for (w = 1; w <= L.numVertexes; w++) // 行
						{
							if (0 != L.arc[w][a])
							{
								inD++;
							}
						}
						//计算出度
						for (w = 1; w <= L.numVertexes; w++) // 行
						{
							if (0 != L.arc[a][w])
							{
								ouD++;
							}
						}

						//公共子图结点入度不为0，原图入度为0，则绝不会匹配；公共子图结点出度不为0，原图出度为0，则绝不会匹配。
						if (inD == 0 && in_degree != 0 || ouD == 0 && ou_degree != 0) {
							r = rand() % L.numVertexes + 1;
							k = 0;
						}
					}	
				}
				cur[i].h[j].second = L.vexs[r];//产生的随机结点不知道是否覆盖全部
			}
		}
	}
}
void cal_f(int f[], int s[], int &f1, int &f2, int LEN, MGraph &Q, MGraph &L) {
	int i, j;
	f1 = 0;
	f2 = 0;
	int *de_gree_one = new int[LEN+1];
	int *de_gree_two = new int[LEN+1];
	for (i = 1; i < LEN + 1; i++) {
		de_gree_one[i] = 0;
		de_gree_two[i] = 0;
	}
	for (i = 1; i < LEN + 1; i++) {
		for (j = 1; j < LEN + 1; j++) {
			if (Q.arc[f[i]][f[j]] != L.arc[s[i]][s[j]])
				f1++; //不匹配的边数
			//计算结点度数
			if (Q.arc[f[i]][f[j]] == 1)
				de_gree_one[i] ++;
			if (Q.arc[f[j]][f[i]] == 1)
				de_gree_one[i] ++;

			if (L.arc[s[i]][s[j]] == 1)
				de_gree_two[i] ++;
			if (L.arc[s[j]][s[i]] == 1)
				de_gree_two[i] ++;
		}
	}
	for (i = 1; i < LEN + 1; i++) {
		if (de_gree_one[i] != de_gree_two[i])
			f2++;//不匹配结点数
	}
	delete(de_gree_one);
	delete(de_gree_two);
}
//计算当前种群中各个个体的适应度
void cal_fitness(int LEN, MGraph Q, MGraph L)
{
	int  j, k, r, f1, f2;
	int *f = new int[LEN+1];
	int *s = new int[LEN+1];
	double d;
	for (k = 1; k < LEN; k++) {
		f[k] = 0;
		s[k] = 0;
	}
	//计算每个种群的适应度及适应度总和
	for (k = 1; k <= sizepop; k++) {
		r = 1;
		f1 = 0;
		f2 = 0;
		for (j = 1; j <= LEN; j++) {
			f[r] = cur[k].h[j].first;
			s[r] = cur[k].h[j].second;
			r++;
		}
		//cout << max_one.fitness << endl;
		cal_f(f, s, f1, f2, LEN, Q, L);
		//cout << max_one.fitness << endl;
		//d = 0.1*f1 + 0.9*f2;
		d = f1 + f2;
		cur[k].edge = f1;
		cur[k].node = f2;
		cur[k].fitness = d;
	}
	delete(f);
	delete(s);
	//计算适应度f=0.1f1+0.9f2
	//f1:不匹配的边数
	//f2:不匹配的顶点数（度数不同）
}


//选择种群中某个染色体
int sel()
{
	float a = 0;
	double b = 0;
	a = ((float)rand()) / RAND_MAX;
	for (int i = 1; i <= sizepop; i++) {
		b = cur[i].fitness / fitsum + b;
		if (a <= b)
			return i;
	}
	return sizepop;
}


//打印个体适应度和二进制编码
void print(P tmp, int LEN)
{
	for (int i = 1; i <= LEN; i++)
		cout << tmp.h[i].first << "------->" << tmp.h[i].second << " ";
}


//打印种群
void printcur(int LEN)
{
	for (int i = 1; i <= sizepop; i++) {
		print(cur[i], LEN);
		cout << " 适应度 = " << cur[i].fitness << endl;
	}
}
//交叉函数
void cross(P n1, P n2, int s1, int s2, int LEN,int m1, MGraph &Q, MGraph &L) {   
	
	int i, j = 1,k,  q = 0,data_recode_one=0, data_recode_two = 0;

	//取出中间部分s1-s2
	for (i = s1; i <= s2; i++) {
	    population[m1].h[i].first = n1.h[i].first;
		population[m1].h[i].second = n1.h[i].second;
		//        cout<<pel.h[i].first<<"       "<<pel.h[i].second<<endl;
		//        cout<<"中间部分完成"<<endl;
		population[m1+1].h[i].first = n2.h[i].first;
		population[m1+1].h[i].second = n2.h[i].second;
	}
	if (s1 > 1) {
		//第一条染色体
		for (i = 1; i < s1; i++) {
			population[m1].h[i].first = n2.h[i].first;
		}
		//前半部分1-s1
		k = 1;
		i = 1;
		while (k < s1) {
			while ( i <= LEN) {   
				data_recode_one = n2.h[i].second;  //依次取出第二条染色体的second结点
				//与中间部分的second结点进行对比
				for (j = 1; j <= s2; j++) {
					if (population[m1].h[j].second == data_recode_one)   //如果中间部分存在相等，则进行下一个；如果不存在相等，j=s2+1
						break;
				}
				if (j > s2) {  //如果j>s2，则与中间部分不同
					population[m1].h[k].second = data_recode_one;
					k++;
					break;
				}
				i++;
			}
			//随机生成
			if (i > LEN) {
				data_recode_one = rand() % L.numVertexes + 1; //随机生成一个数
				j = 1;
				while ( j <= s2 ) {
					if (population[m1].h[j].second == data_recode_one) {   //如果染色体存在相等，则重新随机生成，并查找是否有相等
						data_recode_one = rand() % L.numVertexes + 1;
						j = 0;
					}
					j++;
				}
				population[m1].h[k].second = data_recode_one;
				k++;
			}
		}
		

		//第二条染色体
		for (i = 1; i < s1; i++) {
			population[m1+1].h[i].first = n1.h[i].first;
		}
		//前半部分1-s1
		k = 1;
		i = 1;
		while (k < s1) {
			while (i <= LEN) {
				data_recode_one = n1.h[i].second;  //依次取出第二条染色体的second结点
				//与中间部分的second结点进行对比
				for (j = 1; j <= s2; j++) {
					if (population[m1+1].h[j].second == data_recode_one)   //如果中间部分存在相等，则进行下一个；如果不存在相等，j=s2+1
						break;
				}
				if (j > s2) {  //如果j>s2，则与中间部分不同
					population[m1+1].h[k].second = data_recode_one;
					k++;
					break;
				}
				i++;
			}
			//随机生成
			if (i > LEN) {
				data_recode_one = rand() % L.numVertexes + 1; //随机生成一个数
				j = 1;
				while (j <= s2) {
					if (population[m1+1].h[j].second == data_recode_one) {   //如果染色体存在相等，则重新随机生成，并查找是否有相等
						data_recode_one = rand() % L.numVertexes + 1;
						j = 0;
					}
					j++;
				}
				population[m1+1].h[k].second = data_recode_one;
				k++;
			}
		}

		
	}
	if (s2 < LEN) {

		//第一条染色体
		for (i = s2+1; i <=LEN; i++) {
			population[m1].h[i].first = n2.h[i].first;
		}
		//后半部分s2-LEN
		k = s2+1;
		i = 1;
		while (k <= LEN) {
			while (i <= LEN) {
				data_recode_one = n2.h[i].second;  //依次取出第二条染色体的second结点
				//与中间部分的second结点进行对比
				for (j = 1; j < k; j++) {
					if (population[m1].h[j].second == data_recode_one)   //如果中间部分存在相等，则进行下一个；如果不存在相等，j=s2+1
						break;
				}
				if (j == k) {  //如果j>s2，则与中间部分不同
					population[m1].h[k].second = data_recode_one;
					k++;
					break;
				}
				i++;
			}
			//随机生成
			if (i > LEN) {
				data_recode_one = rand() % L.numVertexes + 1; //随机生成一个数
				j = 1;
				while (j < k) {
					if (population[m1].h[j].second == data_recode_one) {   //如果染色体存在相等，则重新随机生成，并查找是否有相等
						data_recode_one = rand() % L.numVertexes + 1;
						j = 0;
					}
					j++;
				}
				population[m1].h[k].second = data_recode_one;
				k++;
			}
		}



		//第二条染色体
		for (i = s2 + 1; i <= LEN; i++) {
			population[m1+1].h[i].first = n1.h[i].first;
		}
		//后半部分
		k = s2 + 1;
		i = 1;
		while (k <= LEN) {
			while (i <= LEN) {
				data_recode_one = n1.h[i].second;  //依次取出第二条染色体的second结点
				//与中间部分的second结点进行对比
				for (j = 1; j < k; j++) {
					if (population[m1+1].h[j].second == data_recode_one)   //如果中间部分存在相等，则进行下一个；如果不存在相等，j=s2+1
						break;
				}
				if (j == k) {  //如果j>s2，则与中间部分不同
					population[m1+1].h[k].second = data_recode_one;
					k++;
					break;
				}
				i++;
			}
			//随机生成
			if (i > LEN) {
				data_recode_one = rand() % L.numVertexes + 1; //随机生成一个数
				j = 1;
				while (j < k) {
					if (population[m1+1].h[j].second == data_recode_one) {   //如果染色体存在相等，则重新随机生成，并查找是否有相等
						data_recode_one = rand() % L.numVertexes + 1;
						j = 0;
					}
					j++;
				}
				population[m1+1].h[k].second = data_recode_one;
				k++;
			}
		}
	}
	//计算第一条染色体适应度
	int r, f1, f2;
	int *f = new int[LEN+1];
	int *s = new int[LEN+1];
	r = 1;
	f1 = 0;
	f2 = 0;
	for (j = 1; j <= LEN; j++) {
		f[r] = population[m1].h[j].first;
		s[r] = population[m1].h[j].second;
		r++;
	}
	
	cal_f(f, s, f1, f2, LEN, Q, L);
	population[m1].edge = f1;
	population[m1].node = f2;
	//population[m1].fitness = 0.1*f1 + 0.9*f2;
	population[m1].fitness = f1 + f2;
	//计算第二条染色体适应度
	r = 1;
	f1 = 0;
	f2 = 0;
	for (j = 1; j <= LEN; j++) {
		f[r] = population[m1+1].h[j].first;
		s[r] = population[m1 + 1].h[j].second;
		r++;
	}
	cal_f(f, s, f1, f2, LEN, Q, L);
	population[m1 + 1].edge = f1;
	population[m1 + 1].node = f2;
	//population[m1 + 1].fitness = 0.1*f1 + 0.9*f2;
	population[m1 + 1].fitness = f1 + f2;
}

void com_fitness(P cur[], int LEN, MGraph &Q) {
	int i = 0, j = 0, k, mod_one;
	double mod;
	P sum[sizepop * 2 + 1];

	//合并两个数组
	for (i = 1; i <= sizepop; i++) {
		for (j = 1; j <= LEN; j++) {
			sum[i].h[j].first = cur[i].h[j].first;
			sum[i].h[j].second = cur[i].h[j].second;
			sum[i].edge = cur[i].edge;
			sum[i].node = cur[i].node;
			sum[i].fitness = cur[i].fitness;
		}
	}
	for (i = sizepop + 1, k = 1; i <= sizepop * 2, k <= sizepop; i++, k++) {
		for (j = 1; j <= LEN; j++) {
			sum[i].h[j].first = population[k].h[j].first;
			sum[i].h[j].second = population[k].h[j].second;
			sum[i].edge = population[k].edge;
			sum[i].node = population[k].node;
			sum[i].fitness = population[k].fitness;
		}
	}
	//比较适应度
	for (i = 1; i <= sizepop * 2; i++) {
		for (j = i; j <= sizepop * 2; j++) {
			if (sum[i].fitness > sum[j].fitness) {
				for (k = 1; k <= LEN; k++) {
					//交换第二个节点
					mod_one = sum[i].h[k].second;
					sum[i].h[k].second = sum[j].h[k].second;
					sum[j].h[k].second = mod_one;
				}
				//交换适应度
				mod = sum[i].fitness;
				sum[i].fitness = sum[j].fitness;
				sum[j].fitness = mod;
				//edge
				mod_one = sum[i].edge;
				sum[i].edge = sum[j].edge;
				sum[j].edge = mod_one;
				//node
				mod_one = sum[i].node;
				sum[i].node = sum[j].node;
				sum[j].node = mod_one;
			}
		}
	}
	if (sum[1].fitness < max_one.fitness && LEN == Q.numVertexes) {
		for (j = 1; j <= LEN; j++) {
			max_one.h[j].first = sum[1].h[j].first;
			max_one.h[j].second = sum[1].h[j].second;
		}
		max_one.edge = sum[1].edge;
		max_one.node = sum[1].node;
		max_one.fitness = sum[1].fitness;
	}
	if (LEN < Q.numVertexes+1) {
		for (j = 1; j < LEN+1; j++) {
			max_one.h[j].first = sum[1].h[j].first;
			max_one.h[j].second = sum[1].h[j].second;
		}
		max_one.edge = sum[1].edge;
		max_one.node = sum[1].node;
		max_one.fitness = sum[1].fitness;
	}
	//if (LEN == Q.numVertexes) {
		/*cout << "当前种群最优解：" << endl;
		for (j = 1; j <= LEN; j++) {
			cout << max_one.h[j].first << "-------" << max_one.h[j].second << " ";
		}
		cout << max_one.fitness << endl;*/
	//}
	for (i = 1; i <= sizepop; i++) {
		for (j = 1; j <= LEN; j++) {
			cur[i].h[j].first = sum[i].h[j].first;
			cur[i].h[j].second = sum[i].h[j].second;
			cur[i].edge = sum[i].edge;
			cur[i].node = sum[i].node;
			cur[i].fitness = sum[i].fitness;
		}
	}
}
//换代-从种群中选出最好的一组映射
void tran(int LEN, MGraph Q, MGraph L)
{
	int i, j, k, begi_n = 0, en_d = 0, index = 1;
	double a, b;
	bool tag = true;
	fitsum = 0;
	//初始化
	for (i = 1; i <= sizepop; i++) {
		for (j = 1; j <= LEN; j++) {
			population[i].h[j].first = 0;
			population[i].h[j].second = 0;
			population[i].fitness = 0;
		}
	}
	//保留上一代结果
	for (i = 1; i <= sizepop; i++) {
		for (j = 1; j <= LEN; j++) {
			min_one[i].h[j].first = cur[i].h[j].first;
			min_one[i].h[j].second = cur[i].h[j].second;
		}
		min_one[i].edge = cur[i].edge;
		min_one[i].node = cur[i].node;
		min_one[i].fitness = cur[i].fitness;
	}
	for (i = 1; i <= sizepop; i++) {
		fitsum = cur[i].fitness + fitsum;
	}
	while (index != sizepop + 1) {
		a = rand() / (RAND_MAX + 1.0);
		//交叉
		if (a <= pcross)//如果randd()产生的随机数(在0-1之间）小于设定的交叉率pcross
		{
			//选择交叉个体
			i = sel();//用sel函数挑选一个个体，染色体号为i
			j = sel();//同上，再选择个个体，号为j
			while (j == i) {
				j = sel();
			}
			//选择交叉位置
			begi_n = rand() % (LEN - 1) + 1;
			en_d = rand() % LEN + 1;
			if (begi_n == 1 && en_d == LEN) {
				begi_n = rand() % (LEN - 1) + 1;
				en_d = rand() % LEN + 1;
			}
			while (begi_n > en_d) {
				en_d = rand() % LEN + 1;
			}
			cross(cur[i], cur[j], begi_n, en_d, LEN, index, Q, L);
			index = index + 2;
		}
	}
	//将返回的population和cur，所有种群按照适应度从小到大排序，选出前sizepop个作为当前代。
	com_fitness(cur,  LEN, Q);
	//cout << "交叉后：" << endl;
	//printcur(LEN);
	int klp_one = 0, klp_two = 0, klp = 0, loc = 0, f1 = 0, f2 = 0;
	int *s = new int[LEN + 1];
	int *f = new int[LEN + 1];
	int w = 0,e = 0;
	double fit = 0;
	for (i = 1; i <= sizepop; i++) {
		b = rand() / (RAND_MAX + 1.0);//每一个种群产生随机概率
		if (b <= pmutation) { //小于变异概率则变异
			j = rand() % LEN + 1;//选择变异位置
			klp_one = cur[i].h[j].second;//记录j的映射
			
			if (LEN < L.numVertexes) {   //结点数不等
				w = rand() % L.numVertexes + 1;//随机产生一个结点数
				k = 1;
				while (k <= LEN) {
					if (cur[i].h[k].second == w) {
						w = rand() % L.numVertexes + 1;
						k = 0;
					}
					k++;
				}
				cur[i].h[j].second = w;
			}
			if (LEN >= L.numVertexes) {     //随机交换两个位置的数
				w = rand() % L.numVertexes + 1;   //随机产生一个与当前位置不一样的位置w进行交换
				while (w == j) {
					w = rand() % L.numVertexes + 1;
				}
				klp_two = cur[i].h[w].second; //记录w的结点
				cur[i].h[j].second = klp_two;
				cur[i].h[w].second = klp_one;
			}
			for (k = 1; k <= LEN; k++) {
				f[k] = cur[i].h[k].first;
				s[k] = cur[i].h[k].second;
			}
			cal_f(f, s, f1, f2, LEN, Q, L);
			//fit = 0.1*f1 + 0.9*f2;
			fit = f1 + f2;
			if (fit > cur[i].fitness || cur[i].h[j].second == klp_one) {
				if(LEN < L.numVertexes)
					cur[i].h[j].second = klp_one;
				if (LEN >= L.numVertexes) {
					cur[i].h[j].second = klp_one;
					cur[i].h[w].second = klp_two;
				}
			}
			else {
				cur[i].edge = f1;
				cur[i].node = f2;
				cur[i].fitness = fit;
				//cout << "第"<<i<<"条染色体变异成功" << endl;
			}
		}
		
	}

	//cout << "变异后的映射" << endl;
	//printcur(LEN);


	if (LEN == Q.numVertexes) {
	//与上一代结果进行对比
		for (i = 1; i <= sizepop; i++) {
			if (min_one[i].fitness != cur[i].fitness)
				break;
			for (k = 1; k <= LEN; k++) {
				if (min_one[i].h[k].second != cur[i].h[k].second)
					break;
			}
			if (k <= LEN)
				break;
		}
		if (i > sizepop)
			tag_two = false;
	}
	delete(f);
	delete(s);
}
