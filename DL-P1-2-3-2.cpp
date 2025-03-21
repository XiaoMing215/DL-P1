#include <iostream>
#include <vector>
#include<algorithm>
#include <map>
#include <string>
#include<queue>
using namespace std;

const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, -0}, {0, -1}};  // 上下左右
const vector<char> labels = {'u', 'r', 'd', 'l'};
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

bool isSolvable(const string& board) {
    int inv_count = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == '0') continue;
        for (int j = i + 1; j < 9; j++) {
            if (board[j] != '0' && board[i] > board[j]) {
                inv_count++;
            }
        }
    }
    return inv_count % 2 == 0;
}


string Astar(const string& start){
    priority_queue<pair<int,string>,vector<pair<int, string>>, greater<pair<int, string>>> pq; //fn,lzero
    map<string,int> visited;//存储步数gn
    map<string, pair<string, char>> parent;//每个图的前驱图，并且存储了到达所需的走法
    // map<string, char> move_direction;//每个图的移动方向 ，合并到上面了
    // int lzero = findzero(board);//or board.find('0')
    pq.push({hn(start),start});//只存储启发式函数hn
    visited[start] = 0;//只存储步数，即gn

    while (!pq.empty())
    {
        auto [cost,board] = pq.top();
        pq.pop();

        if(isGoal(board)){
            string path;
            while (goal != start) { //结束状态即goal，一步步反推
                path += parent[goal].second;
                goal = parent[goal].first;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // if(visited[board]<=cost)//内部已经存有更小的cost
        //     continue;
        //优先队列存储 因此这样的情况不会被优先弹出

        //另：上课讲到了A*不会在第一次搜索到时就直接返回 代码没有体现 为什么？、
        //这是因为第一次搜索到的值被存在pq当中了。如果有更短的路径 他的遍历会在这个值之前。

        int step = visited[board]; //用于更新gn
        int lzero = findzero(board);
        int xzero = lzero/3,yzero = lzero%3;//x为纵y为横，x轴向下y轴向左 之前的构造方法不都是从0开始因此错了
        string prev = board;//记录原状态

        for (int i=0 ; i<4 ; i++)
        {
            auto [x,y]  = directions[i];
            int xnew = xzero + x,ynew = yzero + y;
            if (xnew < 3 && xnew >= 0 && ynew < 3 && ynew >= 0)
            {
                int lnew = xnew*3 + ynew;
                
                swap(board[lzero],board[lnew]);
                if (!visited.count(board) || step+1 < visited[board])//很巧妙！如果不存在则不会进行后面的判断 否则就看有没有之前更少步数到达
                {
                    visited[board] = step+1;
                    parent[board] ={prev,labels[i]};
                    pq.push({visited[board]+hn(board),board});
                    // move_direction[newboard] = labels[i];
                }
                swap(board[lzero],board[lnew]);
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

    if (!isSolvable(start)) {
        cout << "unsolvable";
        return 0;
    }

    string res = Astar(start);
    cout<<res;
    return 0;
}
