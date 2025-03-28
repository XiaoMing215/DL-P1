#处理有沼泽问题的BFS：并不能很好的处理
#BFS解决迷宫问题

from collections import deque

directions =[(1,0),(0,1),(-1,0),(0,-1)] 
def BFS(maze,start = (0,0)):
    m, n = len(maze), len(maze[0])
    visited = []
    parent = {} #使用字典记录到达该路径的上一个路径
    queue = deque([(0,0,0)])#起始位置:x,y,step
    visited.append(start)
    while queue:
        x,y,steps = queue.popleft()
        if x == m-1 and y == n-1:
            path = [] #开始构建路径
            while (x,y) in parent:
                path.append((x,y))
                x,y = parent[(x,y)]
            path.append(start)
            path.reverse()
            return steps,path,visited
        for dx,dy in directions:
            newx,newy = x+dx,y+dy
            if newx >= 0 and newy >= 0 and newx < m and newy < n :
                if maze[newx][newy]!=1 and (newx,newy) not in visited:
                    queue.append((newx,newy,steps+1))
                    visited.append((newx,newy))
                    parent[(newx,newy)] = (x,y)

    
if __name__ == "__main__":
    n,m = map(int, input().split())
    maze = [list(map(int, input().split())) for _ in range(m)]
    # print(maze)
    step,path,visited = BFS(maze)
    print(step)
    print(path)
    print(visited)