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

typedef pair<int, int >P;					  //����  
		
//��ʽǰ����
struct node
{
	int id;										//�ߵ�id
	int v, w;									//v Ϊ����ĵ�, wΪȨ��
	int next;									//��¼��һ���ṹ���λ�� �����������next������һ����
};

struct RESULTPATH
{
	int dCost;
	int keyvalue;
	bool visited[603];
	vector<int >  listShortestPath;
	vector<int >  edgeShortestPath;
};

node edge[4803];								//�����е������
node fedge[4803];								//�����еķ����
vector<int>demandpoint;
int  cnt;										//�ṹ����±�
int  n,edges, startpoint, endpoint;				//n ����,edges������s ���,tֹ��
int  head[603];									//�������ͷָ��������һ���ġ�ֻ�����˴�head[u]��¼��Ϊ������ edge ������u�����ı��� edge �е�λ�ã����±�
int  fhead[603];								//�����ͷָ��
bool visdfs[603];								//dfs���ʱ�־
bool visbfs[603];
bool visited[603];

vector<int >  listShortestPath;					 //��������·������
RESULTPATH resultPath;							 //���·����Ϣ

void add(int i, int u, int v, int w)					//�ӱ߲���
{
	edge[cnt].id = i;							//����
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];					//�����һ���ṹ���λ��
	head[u] = cnt++;

	fedge[cnt].id = i;							//����
	fedge[cnt].v = u;
	fedge[cnt].w = w;
	fedge[cnt].next = fhead[v];					//�����һ���ṹ���λ��
	fhead[v] = cnt++;							//��¼ͷָ����±�
	
}

char * fasttrim(char * str)
{
#define IS_SPACE(c)  (c == ' ' || c == '\t' || c == ' ')	//��Ҫ�޼�������.
	char * start, *end = NULL;
	if (str == NULL)
		return NULL;
	while (IS_SPACE(*str)) str++;	//ȥ��ͷ���Ŀո��ַ�

	//start��ֵ��ѭ��
	for (start = str; *str != '\0'; str++)
	{
		if (IS_SPACE(*str))
		{
			end = str++;	//�����������ĵ�һ���ո��ϸ�λ�þ��ǿ��ܵ�β��
			while (IS_SPACE(*str)) str++;	//ȥ�������������Ŀո�
			if (*str != '\0')	//û�е�β�������������ַ����ϴμ�¼��β����Ч
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
//star:��Դ���  
//i:��ǰ���  
void printPath(int star, int i)
{
    //��������   
    if (star == i) {
       cout << i << " ";
       return;
	}
	printPath(star, parent[i]);
    cout << i << " ";
}

int dijkstra(int ds, int dt, RESULTPATH & resultPath)
{
	int dis[603];								//���·������
	int i, v;									//v����Ӷ�����ȡ�������ĵڶ�����  Ҳ���Ƕ���ı��

	priority_queue<P, vector<P>, greater<P> >que;//���ȶ��� ��С����
	node e;//����ߵ���Ϣ��Ϊ����д����
	P p;//����Ӷ���ȡ������ֵ
	fill(dis,    dis + n   , MAX);//��ʼ������Ϊ�����
	fill(parent, parent + n, -1);//��ʼ�����нڵ�û�и��ڵ�
	//resultPath.dCost = MAX;
	dis[ds] = 0;//s��>s  ����Ϊ0
	que.push(P(0, ds));//������� Ϊ0   ��Ϊs
	parent[ds] = ds;
	while (!que.empty()){
		p = que.top();			//ȡ����������̾�����С�Ķ���
		que.pop();				//ɾ��
		v = p.second;			//�����̾�����С�Ķ�����

		if (visited[v]==1)		//��ȡ���ķ��ʹ�
			continue;			//�������һ��ѭ��

		visited[v] = 1;

		if (visited[dt]==1)			//�ҵ�Ŀ�Ľڵ��˳�
		{
			//resultPath.dCost = dis[dt];
			//resultPath.listShortestPath = tempPath;
			break;
		}
			
		if (dis[v] < p.first)	//��ȡ���Ĳ�����̾���
			continue;			//�������һ��ѭ��
		for (i = head[v]; i != -1; i = edge[i].next)//����˵����������еĵ���б���
		{
			e = edge[i];							//Ϊ����д�ķ��㡣
			if (!visited[e.v] && dis[e.v]>dis[v] + e.w){				//�����ɳ�
				dis[e.v] = dis[v] + e.w;			//�ɳڳɹ�
				que.push(P(dis[e.v], e.v));			//���ҵ����ɳڳɹ��ľ��� �Ͷ���������
				parent[e.v] = v;
			}
			
		}

	}
	return dis[dt] == MAX ? -1 : dis[dt];

}
struct cmpKeyvalue {
	bool operator() (const RESULTPATH &a, const RESULTPATH &b)
	{		   
		return a.keyvalue > b.keyvalue;		  //// ��һ��Ԫ�ش��ڵڶ���Ԫ�أ�������ʱ�� ��Ӧ����С���ѣ�����
	}                                         // ����Ҫ����ѣ�����ʱ����������false�ͺã�����'<' (Ĭ��ֵ)

};
		
int DG_EN(int ds, int dt, RESULTPATH & resultPath){
#define MC  (1E4)

	priority_queue<RESULTPATH, vector<RESULTPATH >, cmpKeyvalue >que;//���ȶ��� С���ѣ�keyԽСԽ��
	vector<RESULTPATH > allFindPath;			//�����ҵ���·��
	RESULTPATH tempFindPath;					//��ǰ�ҵ���·��
	RESULTPATH p;								//����ȡ������·��
	int i, v;									//v����Ӷ�����ȡ�������ĵڶ�����  Ҳ���Ƕ���ı��
	int k, op;									//k���ҵ���·����Ŀ��op�ǶѲ�����Ŀ
	node e;										//����ߵ���Ϣ��Ϊ����д����
	
	//1.������ԭ��s���ڵ�j��һ��·��ΪP��s,j��
	//2.keyValue=numof(demandpoint)-point(demandpoint��P(s,u)).��ʣ���Ҫ��㣬ԽСԽ��
	//��ʼ��
	k = 0; 
	op = 1; 
	tempFindPath.dCost = 0;
	tempFindPath.keyvalue = (int)demandpoint.size();
	//memset(tempFindPath.visited, 0, sizeof(tempFindPath.visited));
	for (int j=0; j < sizeof(tempFindPath.visited); j++){		//��֦
		tempFindPath.visited[j] = !visdfs[j];
	}
	resultPath.keyvalue = 0;
	resultPath.dCost = MAX;

	tempFindPath.listShortestPath.insert(tempFindPath.listShortestPath.begin(), ds);	//��ʼ����һ��·��P(S,S)
	//allFindPath.push_back(FindPathtemp);			//����
	tempFindPath.visited[ds] = true;
	que.push(tempFindPath);								//�����ʼ·��,keyValue = 50,P(s,s)
	while (!que.empty()){
		p = que.top();									//ȡ�������и�Ԫ�أ���P(s,u)���汻ɾ����Ԫ��
		que.pop();										//ɾ��
		op++;											//�Ѳ��������������˳�
		if (op == MC)
			return k;
		if ( p.keyvalue == 0){	                         //��������ָ����
			if (p.listShortestPath.back() == dt){				//�ҵ���������
				allFindPath.push_back(p);								//�����ҵ���·��
				if (p.dCost < resultPath.dCost)
					resultPath = p;
				k++;													//�ҵ�������һ
				continue;
			}
		}

		for (i = head[p.listShortestPath.back()]; i != -1; i = edge[i].next){	//
			e = edge[i];														//Ϊ����д�ķ��㡣
			tempFindPath = p;
			if (tempFindPath.visited[e.v])													//��ѯ�Ƿ���ڻ�·
				continue;
			tempFindPath.listShortestPath.push_back(e.v);						//��չ·��P(s,u)->P(s,v)
			tempFindPath.edgeShortestPath.push_back(edge[i].id);
			tempFindPath.visited[e.v] = true;
			tempFindPath.dCost += e.w;											//�ۼ���չ·���ĳ���
			for (int j = 0; j < demandpoint.size();j++)							//����ؼ��֡������ǰ����ĵ���Ҫ��㣬�ؼ��ּ�һ
				if (demandpoint[j]==e.v){
					tempFindPath.keyvalue--;
					break;
				}
														//����P(S,V)�Ĺؼ���
			//tempFindPath.keyvalue = 0;
			que.push(tempFindPath);												 //����keyvalue�ڶ��з�����չ���·��
			op++;
			if (op == MC){
				return k;
			}				
		}
	}

	if (k > 0){			//�ҵ�·��	
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
	int q[603];//����
	int jin = 0, chu = 0, st;
	q[jin++] = x;
	visbfs[x] = true;//���
	while (chu < jin)
	{
		st = q[chu++];
		//printf("%d\n", st);
		for (int k = head[st]; k != -1; k = edge[k].next)
		{
			if (!visbfs[edge[k].v])
			{
				visbfs[edge[k].v] = true; //���
				q[jin++] = edge[k].v;
			}
		}
	}
}

int Min(int a[], int b[],int n)			//����ַ���μ���ַ������
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
	int m, i,u, v, w;		//û��id,�㣬�ߣ�Ȩ
	int j=0;
	int cost=0;
    unsigned short result[] = {2,6,3};//ʾ���е�һ����

	m = edges = edge_num;						//����	
	Get_demand(condition, &startpoint, &endpoint, demandpoint);

	cnt = 0;							//�ṹ���±��0��ʼ
	memset(head, -1, sizeof(head));		//��ʼ��head[N]����
	memset(visdfs, false, sizeof(visdfs));
	memset(visited, false, sizeof(visited));

	while (m--){						//������
		sscanf(graph[j++], "%d,%d,%d,%d\n", &i, &u, &v, &w);
		add(i,u, v, w);					//�ӱ�u=g[1],v=[2],w=[3]	
	}
	while(head[++m] != -1){
		n++;							//ͳ�ƽڵ���
	}
	DFS(startpoint);							//����
	
	//cost = dijkstra(startpoint, endpoint, resultPath);
	DG_EN(startpoint, endpoint, resultPath);
	cost = resultPath.dCost;
	//printPath(startpoint, endpoint);
	
	if (cost != MAX){		//�н�
		for (int i = 0; i < resultPath.edgeShortestPath.size(); i++)
			record_result(resultPath.edgeShortestPath[i]);
	}
	

}

