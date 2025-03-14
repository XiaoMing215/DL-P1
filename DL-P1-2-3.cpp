#include <iostream>
#include <vector>
#include<algorithm>
#include <map>
#include <string>
#include<queue>
using namespace std;

const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // 上下左右
const vector<char> labels = {'l', 'r', 'd', 'u'};
string goal ="123456780"; 

bool isGoal(const string& board){
    return board == goal;
}

int findzero(const string& board){
    
    return board.find('0');
}

int Manhattan(int dst, int src){//目标，源
    int xdst = dst%3,ydst = dst/3;
    int xsrc = src%3,ysrc = src/3; 
    return abs(xdst-xsrc)+abs(ydst-ysrc);
}

int hn(const string& board ){//启发式代价
    int cost = 0;
    for (size_t i = 0; i < 9; i++)
    {
        if (board[i] == '0') 
            continue;
        int dst = board[i]-'1';//数码的值不代表他的位置
        int src = i; //这个数码现在处在i的位置
        cost+=Manhattan(dst,src);
    }
    return cost;
}

string Astar(const string& board){
    priority_queue<pair<int,string>,vector<pair<int, string>>, greater<pair<int, string>>> pq; //fn,lzero
    map<string,int> visited;
    map<string, string> parent;//每个图的前驱图
    map<string, char> move_direction;//每个图的移动方向
    // int lzero = findzero(board);//or board.find('0')
    pq.push({0+hn(board),board});
    visited[board] = 0+hn(board);

    while (!pq.empty())
    {
        auto [cost,board] = pq.top();
        pq.pop();

        if(isGoal(board)){
            string path;
            while (parent.find(board) != parent.end()) {
                path = move_direction[board] + path;
                board = parent[board];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // if(visited[board]<=cost)//内部已经存有更小的cost
        //     continue;
        //优先队列存储 因此这样的情况不会被优先弹出

        //另：上课讲到了A*不会在第一次搜索到时就直接返回 代码没有体现 为什么？、
        //这是因为第一次搜索到的值被存在pq当中了。如果有更短的路径 他的遍历会在这个值之前。

        int lzero = findzero(board);
        int xzero = lzero%3,yzero = lzero/3;
        for (int i=0 ; i<4 ; i++)
        {
            auto [x,y]  = directions[i];
            int xnew = xzero + x,ynew = yzero + y;
            if (xnew < 3 && xnew >= 0 && ynew < 3 && ynew >= 0)
            {
                int lnew = xnew + 3*ynew;
                string newboard = board;
                swap(newboard[lzero],newboard[lnew]);
                
                int fn = visited[board] + 1 - hn(board) + hn(newboard);
                if (!visited.count(newboard) || fn < visited[newboard])
                {
                    pq.push({fn,newboard});
                    visited[newboard] = fn;
                    parent[newboard] = board;
                    move_direction[newboard] = labels[i];
                }
            }
        }
    }
    return "unsolvable";
}

//pq承接所有frointier 格式：<fn,string>
int main() {
    string start = "";

    for (int i = 0; i < 9; ++i) {
        string s;
        cin >> s;
        if (s == "x") start += '0';  // x 转换为 0
        else start += s;
    }
    string res = Astar(start);
    cout<<res;
    return 0;
}
