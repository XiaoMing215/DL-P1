#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>

using namespace std;
//采用string减少计算量
//使用BFS算出最佳步数
//queue承载遍历列表，列表每个元素是pair<string,int>
//需要一个set排除所有重复情况
//不该使用set 因为要存储步数 使用map更好
//map使用count判断是否存在 如果已经存在必然代价更小 无需更新

string goal = "123456780";
vector<pair<int,int>> direction= {{1,0},{0,1},{-1,0},{0,-1}};//可能的每一步

int locationZero(const string& board){
    int location;
    for (size_t i = 0; i < 9; i++){
        if (board[i]==0)
            location = i;
    }
    return location;
}

int BFS(const string& board){//返回步数
    queue<pair<string,int>> q;
    map<string,int> visited;//记录该状态是否已存在
    
    q.push({board,0});
    visited[board] = 0;

    while (!q.empty())
    {
        auto [board,step] =q.front();
        q.pop();

        if (board == goal)
            return step;
        
        int lzero = board.find('0'); 
        // int lzero = locationZero(board);
        int xzero = lzero%3,yzero = lzero/3;
        for (auto [x,y] : direction )
        {
            int xnew = xzero + x,ynew = yzero + y;
            if (xnew < 3 && xnew >= 0 && ynew < 3 && ynew >= 0)
            {
                int lnew = xnew + 3*ynew;
                string newboard = board;
                swap(newboard[lzero],newboard[lnew]);
                
                if (!visited.count(newboard))
                {
                    q.push({newboard,step+1});
                    visited[newboard] = step+1;
                }
            }
        }
    }
    return -1;
}




int main(){
    string start = "";

    for (int i = 0; i < 9; ++i) {
        string s;
        cin >> s;
        if (s == "x") start += '0';  // x 转换为 0
        else start += s;
    }
    // cout<<start;
    int res = BFS(start);
    cout<<res;
    return 0;
}