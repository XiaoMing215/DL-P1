import heapq  # 一个用于实现优先队列的库
#非0或1，则上面的数值代表了每一步的cost

directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]

def dijkstra(maze):
    m, n = len(maze), len(maze[0])
        
    dist = [[float('inf')] * n for _ in range(m)]  # 最短距离表
    dist[0][0] = 0

    parent = {}
    visited = []
    
    pq = [(0, 0, 0)]  # (总代价, x, y)
    
    while pq:
        cost, x, y = heapq.heappop(pq)
        
        if (x, y) in visited:
            continue
        visited.append((x, y))

        if x == m - 1 and y == n - 1:
            path = []
            while (x, y) in parent:
                path.append((x, y))
                x, y = parent[(x, y)]
            path.append((0, 0))
            return cost, path[::-1], visited  # 反转路径
        
        for dx, dy in directions:
            newx, newy = x + dx, y + dy
            if 0 <= newx < m and 0 <= newy < n and maze[newx][newy] != 1:
                move_cost = maze[newx][newy] if maze[newx][newy] > 1 else 1  # 非0、1的值作为cost
                new_cost = cost + move_cost
                if new_cost < dist[newx][newy]:  # 只更新更短路径
                    dist[newx][newy] = new_cost
                    parent[(newx, newy)] = (x, y)
                    heapq.heappush(pq, (new_cost, newx, newy))
    
    return -1, [], visited  # 终点不可达

if __name__ == "__main__":
    n, m = map(int, input().split())
    maze = [list(map(int, input().split())) for _ in range(m)]

    step, path, visited = dijkstra(maze)
    print(step)
    print(path)
    print(visited)