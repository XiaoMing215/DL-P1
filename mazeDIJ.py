#dij解决迷宫问题
#迷宫无权重 退化为BFS



import heapq #一个用于实现优先队列的库

directions = [(1, 0), (0, 1), (-1, 0), (0, -1)] 

def dijkstra(maze):
    m, n = len(maze), len(maze[0])
        
    dist = [[float('inf')] * n for _ in range(m)] # 最短距离表
    dist[0][0] = 0

    parent = {}
    visited = []
    
    pq = [(0,0,0)]  #(步数, x, y)
    
    while pq:
        steps, x, y = heapq.heappop(pq)
        visited.append((x, y))

        if x == m-1 and y == n-1:
            path = []
            while (x, y) in parent:
                path.append((x, y))
                x, y = parent[(x, y)]
            path.append((0,0))
            return steps, path[::-1], visited  # 反转路径
        for dx, dy in directions:
            newx, newy = x + dx, y + dy
            if 0 <= newx < m and 0 <= newy < n and maze[newx][newy] == 0:
                new_steps = steps + 1
                if new_steps < dist[newx][newy]:  # 只更新更短路径
                    dist[newx][newy] = new_steps
                    parent[(newx, newy)] = (x, y)  
                    heapq.heappush(pq, (new_steps, newx, newy))
    
    return -1, [], visited  # 终点不可达

if __name__ == "__main__":
    n, m = map(int, input().split())
    maze = [list(map(int, input().split())) for _ in range(m)]

    step,path,visited = dijkstra(maze)
    print(step)
    print(path)
    print(visited)
