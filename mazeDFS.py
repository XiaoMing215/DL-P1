#DFS解决迷宫问题
from collections import deque

# directions =[(1,0),(0,1),(-1,0),(0,-1)] 
directions = [(0, 1),(-1, 0), (1, 0),(0, -1)]
all_visited = []
visited =set()
def DFS(maze,location,path,step=0):
    m, n = len(maze), len(maze[0])
    if location not in all_visited:
        all_visited.append(location)

    if location in visited:
        return float('inf'),[]
    visited.add(location)
    
    if location ==(m-1,n-1):
        return step,path+[location] #需要创建新的path副本 否则退出时会被误处理pop干净
    
    path.append(location)
    x,y = location

    min_steps = float('inf') 
    best_path = []
    
    for dx,dy in directions:
        newx,newy = x+dx,y+dy
        if 0 <= newx < m and 0 <= newy < n and maze[newx][newy]==0 :
            steps,new_path =  DFS(maze,(newx,newy),path,step+1)
            if steps<min_steps:
                min_steps = steps
                best_path = new_path
    visited.remove(location)
    path.pop()

    return (min_steps,best_path) if min_steps != float('inf') else (float('inf'),[])
    
            
if __name__ == "__main__":
    n,m = map(int, input().split())
    maze = [list(map(int, input().split())) for _ in range(m)]
    # print(maze)
    step,path,visited = DFS(maze,location=(0,0),path=[])
    print(step)
    print(path)
    print(all_visited)