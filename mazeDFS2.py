from collections import deque

# directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
# directions = [(0, 1),(-1, 0), (1, 0),(0, -1)]
all_visited = []
visited = set()
found_path = False  # 添加一个全局标志，表示是否已经找到路径

def DFS(maze, location, path, step=0,directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]):
    global found_path  # 使用全局变量 found_path
    m, n = len(maze), len(maze[0])
    if location not in all_visited:
        all_visited.append(location)

    if location in visited or found_path:  # 如果已经访问过或者已经找到路径，则直接返回
        return float('inf'), []

    visited.add(location)

    if location == (m - 1, n - 1):
        found_path = True  # 找到路径后，设置 found_path 为 True
        return step, path + [location]

    path.append(location)
    x, y = location

    min_steps = float('inf')
    best_path = []

    for dx, dy in directions:
        newx, newy = x + dx, y + dy
        if 0 <= newx < m and 0 <= newy < n and maze[newx][newy] == 0:
            steps, new_path = DFS(maze, (newx, newy), path, step + 1,directions=directions)
            if steps < min_steps:
                min_steps = steps
                best_path = new_path
                if found_path:  # 如果已经找到路径，直接返回
                    return min_steps, best_path

    visited.remove(location)
    path.pop()

    return (min_steps, best_path) if min_steps != float('inf') else (float('inf'), [])

if __name__ == "__main__":
    n, m = map(int, input().split())
    maze = [list(map(int, input().split())) for _ in range(m)]
    step, path = DFS(maze, location=(0, 0), path=[])
    print("Step:", step)
    print("Path:", path)
    print("All visited:", all_visited)