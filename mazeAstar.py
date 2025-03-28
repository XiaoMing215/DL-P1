#A*解决迷宫问题


import heapq

# 四个方向移动
directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]

def hn(srcx, srcy, dstx, dsty):
    """ 计算曼哈顿距离（启发式函数 h(n)）"""
    return abs(srcx - dstx) + abs(srcy - dsty)

def Astar(maze):
    m, n = len(maze), len(maze[0])

    gn = [[float('inf')] * n for _ in range(m)]
    gn[0][0] = 0 #记录到达每个位置的最少步数作为gn
    parent = {}
    visited = []

    pq = [(0+hn(0, 0, m-1, n-1), 0, 0, 0)]  # (f(n), g(n), x, y)
    
    while pq:
        _, steps, x, y = heapq.heappop(pq)
        visited.append((x, y))

        if x == m-1 and y == n-1:
            path = []
            while (x, y) in parent:
                path.append((x, y))
                x, y = parent[(x, y)]
            path.append((0,0))
            return steps,path[::-1], visited

        for dx, dy in directions:
            newx, newy = x + dx, y + dy
            if 0 <= newx < m and 0 <= newy < n and maze[newx][newy] == 0:
                new_steps = steps + 1
                if new_steps < gn[newx][newy]:  # 只更新更短路径
                    gn[newx][newy] = new_steps
                    parent[(newx, newy)] = (x, y)
                    fn = new_steps + hn(newx, newy, m-1, n-1)
                    heapq.heappush(pq, (fn, new_steps, newx, newy))
    
    return -1  # 终点不可达

if __name__ == "__main__":
    n, m = map(int, input().split())
    maze = [list(map(int, input().split())) for _ in range(m)]

    step,path,visited = Astar(maze)
    print(step)
    print(path)
    print(visited)