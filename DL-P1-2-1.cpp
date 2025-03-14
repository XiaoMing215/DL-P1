#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<queue>
using namespace std;
set<string> visited;
vector<pair<int,int>> directions ={{1,0},{0,1},{-1,0},{0,-1}};
//不能使用二维向量承接的的set 似乎会爆
string goal ="123456780"; 

bool isGoal(const string& board){
    return board == goal;
}

int findzero(const string& board){
    
    return board.find('0');
}

bool DFS(string& board,int depth){
    if (isGoal(board))
        return true;
    
    if (visited.count(board) || depth>31)
        return false;//如果访问了且能成功一定会返回true的
    
    visited.insert(board);//不能在里面插入
    int lzero = findzero(board);
    int xzero = lzero%3,yzero = lzero/3;
    for (auto [x,y] :directions)
    {
        int xnew = x+xzero,ynew = y+yzero;
        if (xnew < 3 && xnew >= 0 && ynew < 3 && ynew >=0 )
        {
            int lnew = xnew + 3*ynew;
            string newboard = board;
            swap(newboard[lzero],newboard[lnew]);
            
            if (DFS(newboard,depth+1))
            return true;
        }
    }
    return false;
}


void testprint(const vector<vector<int>>& board){
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
           cout<<board[i][j]<<" ";
        }
        
    }
    cout<<endl;
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
    int res = DFS(start,1);
    cout<<(res?1:0);
    return 0;
}