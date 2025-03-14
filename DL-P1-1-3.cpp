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
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    distance[start] = 0;
    pq.push({0,start});//emplace更快
    //不能用队列 而是每次从distance当中找最小值
    while (!pq.empty())
    {
        auto [dist,node] = pq.top();//弹出1节点能到达的距离和最短的节点
        pq.pop();

        if (dist > distance[node])//该节点已被更新过
        {
            continue;
        }
        for (auto [neighbour,weight] : graph[node])
        {
            if (distance[node] + weight < distance[neighbour])
            {
                distance[neighbour] = distance[node]+weight;
                pq.push({distance[neighbour],neighbour});
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