#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_map>
#include<queue>
 
// #include <chrono> 
// using namespace std::chrono;

using namespace std;
//采用string减少计算量
//使用BFS算出最佳步数
//queue承载遍历列表，列表每个元素是pair<string,int>
//需要一个set排除所有重复情况
//不该使用set 因为要存储步数 使用map更好
//map使用count判断是否存在 如果已经存在必然代价更小 无需更新

string goal = "123456780";
vector<pair<int,int>> direction= {{1,0},{0,1},{-1,0},{0,-1}};//可能的每一步

// int locationZero(const string& board){
//     int location;
//     for (size_t i = 0; i < 9; i++){
//         if (board[i]==0)
//             location = i;
//     }
//     return location;
// }

int BFS(const string& board){//返回步数
    queue<pair<string,int>> q;
    // map<string,int> visited;//记录该状态是否已存在
    set<string> visited;
    
    q.push({board,0});
    visited.insert(board);

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
                // string newboard = board; //两次swap可能更快
                swap(board[lzero],board[lnew]);
                
                if (!visited.count(board))
                {
                    q.push({board,step + 1});
                    visited.insert(board);
                }
                swap(board[lzero],board[lnew]);
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
    // auto start_time = high_resolution_clock::now(); // 记录开始时间
    int res = BFS(start);
    // auto end_time = high_resolution_clock::now();   // 记录结束时间
    cout<<res;
    // auto duration = duration_cast<milliseconds>(end_time - start_time);
    // cout << "运行时间: " << duration.count() << " ms" << endl;
    return 0;
}