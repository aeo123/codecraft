#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue> 
#include <functional>

using namespace std;
#define MAX 9999999

typedef pair<int, int >P;					  //对组  
		
//链式前向星
struct node
{
	int id;										//边的id
	int v, w;									//v 为到达的点, w为权重
	int next;									//记录下一个结构体的位置 ，就向链表的next功能是一样的
};

struct RESULTPATH
{
	int dCost;
	int keyvalue;
	bool visited[603];
	vector<int >  listShortestPath;
	vector<int >  edgeShortestPath;
};

node edge[4803];								//存所有的正向边
node fedge[4803];								//存所有的反向边
vector<int>demandpoint;
int  cnt;										//结构体的下标
int  n,edges, startpoint, endpoint;				//n 点数,edges边数，s 起点,t止点
int  head[603];									//和链表的头指针数组是一样的。只不过此处head[u]记录的为最后加入 edge 的且与u相连的边在 edge 中的位置，即下标
int  fhead[603];								//反向边头指针
bool visdfs[603];								//dfs访问标志
bool visbfs[603];
bool visited[603];

vector<int >  listShortestPath;					 //求出的最短路径链表
RESULTPATH resultPath;							 //最短路径信息

void add(int i, int u, int v, int w)					//加边操作
{
	edge[cnt].id = i;							//正边
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];					//获得下一个结构体的位置
	head[u] = cnt++;

	fedge[cnt].id = i;							//反边
	fedge[cnt].v = u;
	fedge[cnt].w = w;
	fedge[cnt].next = fhead[v];					//获得下一个结构体的位置
	fhead[v] = cnt++;							//记录头指针的下标
	
}

char * fasttrim(char * str)
{
#define IS_SPACE(c)  (c == ' ' || c == '\t' || c == ' ')	//需要修剪的内容.
	char * start, *end = NULL;
	if (str == NULL)
		return NULL;
	while (IS_SPACE(*str)) str++;	//去掉头部的空格字符

	//start赋值，循环
	for (start = str; *str != '\0'; str++)
	{
		if (IS_SPACE(*str))
		{
			end = str++;	//遇到非连续的第一个空格，上个位置就是可能的尾部
			while (IS_SPACE(*str)) str++;	//去掉接下来连续的空格
			if (*str != '\0')	//没有到尾，还有其他的字符，上次记录的尾部无效
				end = NULL;		//invalid end             
		}
	}
	if (end) *end = '\0';
	return start;
}
void Get_demand(char * buff, int *startPoint, int *endPoint, vector<int> &route)
{

	buff = fasttrim(buff);

	char str[200];
	sscanf(buff, "%d,%d,%s", startPoint, endPoint, &str);
	const char *d = "|";
	char *p;
	p = strtok(str, d);
	route.push_back(atoi(p));
	while (p)
	{
		p = strtok(NULL, d);
		//int temp = atoi(p);
		if (p != NULL)
			route.push_back(atoi(p));
	}
}


int parent[601];
//star:单源起点  
//i:当前结点  
void printPath(int star, int i)
{
    //到祖先了   
    if (star == i) {
       cout << i << " ";
       return;
	}
	printPath(star, parent[i]);
    cout << i << " ";
}

int dijkstra(int ds, int dt, RESULTPATH & resultPath)
{
	int dis[603];								//最短路径数组
	int i, v;									//v保存从队列中取出的数的第二个数  也就是顶点的编号

	priority_queue<P, vector<P>, greater<P> >que;//优先队列 从小到大
	node e;//保存边的信息，为了书写方便
	P p;//保存从队列取出的数值
	fill(dis,    dis + n   , MAX);//初始化，都为无穷大
	fill(parent, parent + n, -1);//初始化所有节点没有父节点
	//resultPath.dCost = MAX;
	dis[ds] = 0;//s—>s  距离为0
	que.push(P(0, ds));//放入距离 为0   点为s
	parent[ds] = ds;
	while (!que.empty()){
		p = que.top();			//取出队列中最短距离最小的对组
		que.pop();				//删除
		v = p.second;			//获得最短距离最小的顶点编号

		if (visited[v]==1)		//若取出的访问过
			continue;			//则进行下一次循环

		visited[v] = 1;

		if (visited[dt]==1)			//找到目的节点退出
		{
			//resultPath.dCost = dis[dt];
			//resultPath.listShortestPath = tempPath;
			break;
		}
			
		if (dis[v] < p.first)	//若取出的不是最短距离
			continue;			//则进行下一次循环
		for (i = head[v]; i != -1; i = edge[i].next)//对与此点相连的所有的点进行遍历
		{
			e = edge[i];							//为了书写的方便。
			if (!visited[e.v] && dis[e.v]>dis[v] + e.w){				//进行松弛
				dis[e.v] = dis[v] + e.w;			//松弛成功
				que.push(P(dis[e.v], e.v));			//讲找到的松弛成功的距离 和顶点放入队列
				parent[e.v] = v;
			}
			
		}

	}
	return dis[dt] == MAX ? -1 : dis[dt];

}
struct cmpKeyvalue {
	bool operator() (const RESULTPATH &a, const RESULTPATH &b)
	{		   
		return a.keyvalue > b.keyvalue;		  //// 第一个元素大于第二个元素，返回真时； 对应的是小根堆，升序！
	}                                         // 当想要大根堆，降序时，让它返回false就好，即用'<' (默认值)

};
		
int DG_EN(int ds, int dt, RESULTPATH & resultPath){
#define MC  (1E4)

	priority_queue<RESULTPATH, vector<RESULTPATH >, cmpKeyvalue >que;//优先队列 小根堆，key越小越优
	vector<RESULTPATH > allFindPath;			//所有找到的路径
	RESULTPATH tempFindPath;					//当前找到的路径
	RESULTPATH p;								//代表取出来的路径
	int i, v;									//v保存从队列中取出的数的第二个数  也就是顶点的编号
	int k, op;									//k是找到的路径数目，op是堆操作数目
	node e;										//保存边的信息，为了书写方便
	
	//1.定义重原点s到节点j的一条路径为P（s,j）
	//2.keyValue=numof(demandpoint)-point(demandpoint交P(s,u)).即剩余的要求点，越小越优
	//初始化
	k = 0; 
	op = 1; 
	tempFindPath.dCost = 0;
	tempFindPath.keyvalue = (int)demandpoint.size();
	//memset(tempFindPath.visited, 0, sizeof(tempFindPath.visited));
	for (int j=0; j < sizeof(tempFindPath.visited); j++){		//剪枝
		tempFindPath.visited[j] = !visdfs[j];
	}
	resultPath.keyvalue = 0;
	resultPath.dCost = MAX;

	tempFindPath.listShortestPath.insert(tempFindPath.listShortestPath.begin(), ds);	//初始化第一条路径P(S,S)
	//allFindPath.push_back(FindPathtemp);			//放入
	tempFindPath.visited[ds] = true;
	que.push(tempFindPath);								//放入初始路径,keyValue = 50,P(s,s)
	while (!que.empty()){
		p = que.top();									//取出队列中根元素，用P(s,u)代替被删除的元素
		que.pop();										//删除
		op++;											//堆操作次数达上线退出
		if (op == MC)
			return k;
		if ( p.keyvalue == 0){	                         //经过所有指定点
			if (p.listShortestPath.back() == dt){				//找到结束点且
				allFindPath.push_back(p);								//保存找到的路径
				if (p.dCost < resultPath.dCost)
					resultPath = p;
				k++;													//找到数量加一
				continue;
			}
		}

		for (i = head[p.listShortestPath.back()]; i != -1; i = edge[i].next){	//
			e = edge[i];														//为了书写的方便。
			tempFindPath = p;
			if (tempFindPath.visited[e.v])													//查询是否存在回路
				continue;
			tempFindPath.listShortestPath.push_back(e.v);						//扩展路径P(s,u)->P(s,v)
			tempFindPath.edgeShortestPath.push_back(edge[i].id);
			tempFindPath.visited[e.v] = true;
			tempFindPath.dCost += e.w;											//累加扩展路径的长度
			for (int j = 0; j < demandpoint.size();j++)							//计算关键字。如果当前加入的点是要求点，关键字减一
				if (demandpoint[j]==e.v){
					tempFindPath.keyvalue--;
					break;
				}
														//计算P(S,V)的关键字
			//tempFindPath.keyvalue = 0;
			que.push(tempFindPath);												 //根据keyvalue在堆中放入扩展后的路径
			op++;
			if (op == MC){
				return k;
			}				
		}
	}

	if (k > 0){			//找到路径	
		return k;
	}
	else
		return 0;

	
}


void DFS(int x)
{
	visdfs[x] = true;
	//printf("%d\n", x);
	for (int i = head[x]; i != -1; i = edge[i].next)
	{
		if (!visdfs[edge[i].v])
		{
			DFS(edge[i].v);
		}
	}
}

void BFS(int x)
{
	int q[603];//队列
	int jin = 0, chu = 0, st;
	q[jin++] = x;
	visbfs[x] = true;//标记
	while (chu < jin)
	{
		st = q[chu++];
		//printf("%d\n", st);
		for (int k = head[st]; k != -1; k = edge[k].next)
		{
			if (!visbfs[edge[k].v])
			{
				visbfs[edge[k].v] = true; //标记
				q[jin++] = edge[k].v;
			}
		}
	}
}

int Min(int a[], int b[],int n)			//基地址，次级地址，点数
{
	int m = a[b[0]];
	int i;
	for (i = 1; i < n; i++)
	{
		if (a[b[i]] < m)
		{
			m = a[b[i]];
		}
	}
	
	return i;
}



void search_route(char *graph[5000], int edge_num, char *condition)
{
	int m, i,u, v, w;		//没，id,点，边，权
	int j=0;
	int cost=0;
    unsigned short result[] = {2,6,3};//示例中的一个解

	m = edges = edge_num;						//边数	
	Get_demand(condition, &startpoint, &endpoint, demandpoint);

	cnt = 0;							//结构体下标从0开始
	memset(head, -1, sizeof(head));		//初始化head[N]数组
	memset(visdfs, false, sizeof(visdfs));
	memset(visited, false, sizeof(visited));

	while (m--){						//读数据
		sscanf(graph[j++], "%d,%d,%d,%d\n", &i, &u, &v, &w);
		add(i,u, v, w);					//加边u=g[1],v=[2],w=[3]	
	}
	while(head[++m] != -1){
		n++;							//统计节点数
	}
	DFS(startpoint);							//遍历
	
	//cost = dijkstra(startpoint, endpoint, resultPath);
	DG_EN(startpoint, endpoint, resultPath);
	cost = resultPath.dCost;
	//printPath(startpoint, endpoint);
	
	if (cost != MAX){		//有解
		for (int i = 0; i < resultPath.edgeShortestPath.size(); i++)
			record_result(resultPath.edgeShortestPath[i]);
	}
	

}

