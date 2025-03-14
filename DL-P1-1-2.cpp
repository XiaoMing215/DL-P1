// 输入格式
// 第一行包含整数n和m。
// 接下来m行每行包含三个整数x,y,z，表示存在一条从点x到点y的有向边，边长为z。
// 输出格式
// 输出一个整数，表示1号点到几号点的最短距离如果路径不存在，则输出一1。

#include <iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<climits>
using namespace std;


const int INF = INT_MAX;//不可以使用-1 会导致相加时路径出错
vector<pair<int,int>> graph[510];
//之前的vector<vector<int>>只能存储两维。
//pair才能让每个里面存一对：目的+cost 但是仍然只能存两个
//再使用数组使得它能够
//数组不能动态 只要足够大就行

vector<int> dijkstra(int n, int start) {
    //返回到所有地点的最近距离
    vector<int> distance(n+1,INF);
    vector<bool> visited(n+1,false);//why?

    distance[start] = 0;
    //不能用队列 而是每次从distance当中找最小值
    for (size_t i = 1; i <= n; i++)//why n times? 因为每次都会确定一个点的最短路径 n次足以得到结果
    {
        int node = -1,min_distance = INF;
        for (size_t j = 1; j <= n; j++)
        {
            if (visited[j]!=true && distance[j]<min_distance)
            {
                node = j;
                min_distance = distance[j];
            }
        }
        if (node == -1 )
        {
            break;
        }
        
        visited[node] = true;

        for (auto [neighbour,weight] : graph[node])
        {
            if (visited[neighbour]!=true && distance[node] + weight <distance[neighbour])
            {
                distance[neighbour] = distance[node]+weight;
            }
        }
    }

    return distance;
}
int main(){
    int n,m;
    cin>>n>>m;

    for (size_t i = 0; i < m; i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        graph[x].push_back({y,z});//使用make_pair()也可以
    }
    auto res = dijkstra(n,1);
    cout<<(res[n] == INF ? -1: res[n] );
    return 0;
}