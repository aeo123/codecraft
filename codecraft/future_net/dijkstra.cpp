#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue> 
#include <functional>



using namespace std;
////pair ��first �����Ϊ��̾���, second�����Ϊ������
//typedef pair<int, int >P;					  //����  ��֪�������аٶ�   
//
//struct node
//{
//	int v, w;									//v Ϊ����ĵ�, wΪȨ��
//	int next;									//��¼��һ���ṹ���λ�� �����������next������һ����
//};
//node edge[4803];								//�����еıߣ���Ϊ������
//int cnt;										//�ṹ����±�
//int n, s, t;									//n ����,s ���,tֹ��
//int head[603];									//�������ͷָ��������һ���ġ�ֻ�����˴�head[u]��¼��Ϊ������ edge ������u�����ı��� edge �е�λ�ã����±�
//
//void add(int u, int v, int w)					//�ӱ߲���
//{
//	edge[cnt].v = v;
//	edge[cnt].w = w;
//	edge[cnt].next = head[u];					//�����һ���ṹ���λ��
//	head[u] = cnt++;							//��¼ͷָ����±�
//}


//void dijkstra(int ds, int dt)
//{
//	int dis[603];								//���·������
//	int i, v;									//v����Ӷ�����ȡ�������ĵڶ�����  Ҳ���Ƕ���ı��
//	priority_queue<P, vector<P>, greater<P> >que;//���ȶ��� ��С����
//	node e;//����ߵ���Ϣ��Ϊ����д����
//	P p;//����Ӷ���ȡ������ֵ
//
//	fill(dis, dis + n, MAX);//��ʼ������Ϊ�����
//	dis[ds] = 0;//s��>s  ����Ϊ0
//	que.push(P(0, ds));//������� Ϊ0   ��Ϊs
//	while (!que.empty()){
//		p = que.top();//ȡ����������̾�����С�Ķ���
//		que.pop();//ɾ��
//		v = p.second;//�����̾�����С�Ķ�����
//		if (dis[v] < p.first)//��ȡ���Ĳ�����̾���
//			continue;//�������һ��ѭ��
//		for (i = head[v]; i != -1; i = edge[i].next)//����˵����������еĵ���б���
//		{
//			e = edge[i];//Ϊ����д�ķ��㡣
//			if (dis[e.v]>dis[v] + e.w){//�����ɳ�
//				dis[e.v] = dis[v] + e.w;//�ɳڳɹ�
//				que.push(P(dis[e.v], e.v));//���ҵ����ɳڳɹ��ľ��� �Ͷ���������
//
//			}
//		}
//
//	}
//	printf("%d\n", dis[dt] == MAX ? -1 : dis[dt]);//������
//}

//int main()
//{
//	int m, u, v, w;
//
//	while (scanf_s("%d %d", &n, &m) == 2){//��ȡ����  ����
//		cnt = 0;//�ṹ���±��0��ʼ
//		memset(head, -1, sizeof(head));//��ʼ��head[N]����
//		while (m--){
//			scanf_s("%d %d %d", &u, &v, &w);//��ȡu,v,w(u,v)
//			add(u, v, w);//�ӱ�
//			//add(v, u, w);//�ӱ�
//
//		}
//		scanf_s("%d %d", &s, &t);//��ȡ��ֹ��
//		dijkstra(s, t);
//
//	}
//	return 0;
//}