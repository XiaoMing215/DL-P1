// # 给定⼀个n个点m条边的有向图，图中可能存在重边和⾃环。
// # 所有边的⻓度(权重)都是1，点的编号为1-n。
// # 请你求出1号点到n号点的最短距离，如果从1号点⽆法⾛到n号点，输出-1。

// 第⼀⾏包含两个整数n和m。
// 接下来m⾏，每⾏包含两个整数a和b，表示存在⼀条从a⾛到b的⻓度为1的边

//BFS 维护一个队列 每次遍历并添加进去 
//图：邻接表表达 vector<vector<int>>
// 

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

int main(){
    int n,m;//m是边的个数
    cin>>n>>m;
    vector<vector<int>> graph(n+1);//让1-n表示对应的值 不用0
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
    }
    vector<int> distance(n+1,-1);  //位置代表点，数值代表到达的最短距离
    distance[1] = 0;
    queue<int> q;//队列不可以指定长度，队列代表需要被遍历的个数
    q.push(1);//最先要看的是1号点
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        
        vector<int> reached = graph[tmp];
        for (int neighbor : reached)//迭代器大幅降低工作量
        {
            if (distance[neighbor]==-1)
            {
                distance[neighbor] = distance[tmp] + 1;
                q.push(neighbor);//这一步要放在里面 不然会循环多层访问！
            }       
        }   
    }
    cout<<distance[n];//如果不可达输出-1
    return 0;
}
