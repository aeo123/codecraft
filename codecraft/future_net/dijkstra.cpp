#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue> 
#include <functional>



using namespace std;
////pair 的first 保存的为最短距离, second保存的为顶点编号
//typedef pair<int, int >P;					  //对组  不知道请自行百度   
//
//struct node
//{
//	int v, w;									//v 为到达的点, w为权重
//	int next;									//记录下一个结构体的位置 ，就向链表的next功能是一样的
//};
//node edge[4803];								//存所有的边，因为是无向
//int cnt;										//结构体的下标
//int n, s, t;									//n 点数,s 起点,t止点
//int head[603];									//和链表的头指针数组是一样的。只不过此处head[u]记录的为最后加入 edge 的且与u相连的边在 edge 中的位置，即下标
//
//void add(int u, int v, int w)					//加边操作
//{
//	edge[cnt].v = v;
//	edge[cnt].w = w;
//	edge[cnt].next = head[u];					//获得下一个结构体的位置
//	head[u] = cnt++;							//记录头指针的下标
//}


//void dijkstra(int ds, int dt)
//{
//	int dis[603];								//最短路径数组
//	int i, v;									//v保存从队列中取出的数的第二个数  也就是顶点的编号
//	priority_queue<P, vector<P>, greater<P> >que;//优先队列 从小到大
//	node e;//保存边的信息，为了书写方便
//	P p;//保存从队列取出的数值
//
//	fill(dis, dis + n, MAX);//初始化，都为无穷大
//	dis[ds] = 0;//s—>s  距离为0
//	que.push(P(0, ds));//放入距离 为0   点为s
//	while (!que.empty()){
//		p = que.top();//取出队列中最短距离最小的对组
//		que.pop();//删除
//		v = p.second;//获得最短距离最小的顶点编号
//		if (dis[v] < p.first)//若取出的不是最短距离
//			continue;//则进行下一次循环
//		for (i = head[v]; i != -1; i = edge[i].next)//对与此点相连的所有的点进行遍历
//		{
//			e = edge[i];//为了书写的方便。
//			if (dis[e.v]>dis[v] + e.w){//进行松弛
//				dis[e.v] = dis[v] + e.w;//松弛成功
//				que.push(P(dis[e.v], e.v));//讲找到的松弛成功的距离 和顶点放入队列
//
//			}
//		}
//
//	}
//	printf("%d\n", dis[dt] == MAX ? -1 : dis[dt]);//输出结果
//}

//int main()
//{
//	int m, u, v, w;
//
//	while (scanf_s("%d %d", &n, &m) == 2){//获取点数  边数
//		cnt = 0;//结构体下标从0开始
//		memset(head, -1, sizeof(head));//初始化head[N]数组
//		while (m--){
//			scanf_s("%d %d %d", &u, &v, &w);//获取u,v,w(u,v)
//			add(u, v, w);//加边
//			//add(v, u, w);//加边
//
//		}
//		scanf_s("%d %d", &s, &t);//获取起止点
//		dijkstra(s, t);
//
//	}
//	return 0;
//}