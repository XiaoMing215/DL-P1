import heapq  # 一个用于实现优先队列的库

directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]

def hn(srcx, srcy, dstx, dsty,maze):
    """ 计算启发式函数 h(n)"""
    manhattan = abs(srcx - dstx) + abs(srcy - dsty)
    swamp_cost = 0
    if maze[srcx][srcy] > 1:  # 当前位置是沼泽
        swamp_cost = maze[srcx][srcy] * 1.5  # 增加权重
    return manhattan + swamp_cost

def Astar(maze):
    m, n = len(maze), len(maze[0])

    gn = [[float('inf')] * n for _ in range(m)]
    gn[0][0] = 0  # 记录到达每个位置的最少代价作为 gn
    parent = {}
    visited = []

    pq = [(hn(0, 0, m - 1, n - 1,maze), 0, 0, 0)]  # (f(n), g(n), x, y)
    
    while pq:
        _, cost, x, y = heapq.heappop(pq)
        
        if (x, y) in visited:
            continue
        visited.append((x, y))

        if x == m - 1 and y == n - 1:
            path = []
            while (x, y) in parent:
                path.append((x, y))
                x, y = parent[(x, y)]
            path.append((0, 0))
            return cost, path[::-1], visited

        for dx, dy in directions:
            newx, newy = x + dx, y + dy
            if 0 <= newx < m and 0 <= newy < n and maze[newx][newy] != 1:
                move_cost = maze[newx][newy] if maze[newx][newy] > 1 else 1  # 非0、1的值作为cost
                new_cost = cost + move_cost
                if new_cost < gn[newx][newy]:  # 只更新更短路径
                    gn[newx][newy] = new_cost
                    parent[(newx, newy)] = (x, y)
                    fn = new_cost + hn(newx, newy, m - 1, n - 1,maze)
                    heapq.heappush(pq, (fn, new_cost, newx, newy))
    
    return -1, [], visited  # 终点不可达

if __name__ == "__main__":
    n, m = map(int, input().split())
    maze = [list(map(int, input().split())) for _ in range(m)]

    step, path, visited = Astar(maze)
    print(step)
    print(path)
    print(visited)
