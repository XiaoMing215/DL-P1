"""
待补充代码：对搜索过的格子染色
"""
import matplotlib.pyplot as plt
import numpy as np
import mazeAstar
import mazeBFS
import mazeDFS
import mazeDIJ
import mazeDFS2
import mazeBFSadd
import mazeDIJadd
import mazeAstaradd


def visualize_maze_with_path(maze, path, visited, name, interval=0.1):
    import matplotlib.colors as mcolors

    print(f"{name}的visited: {visited}")
    print(f"{name}的path: {path}")
    
    plt.figure(figsize=(len(maze[0]), len(maze)))

    # 生成自定义颜色映射
    cmap = plt.get_cmap("Greens")
    norm_maze = np.array(maze, dtype=float)
    
    # 处理墙壁
    wall_mask = (norm_maze == 1)

    # 处理沼泽，限制范围
    swamp_mask = (norm_maze >= 2)
    norm_maze[norm_maze > 8] = 8
    norm_maze[norm_maze < 2] = 0  

    # 先绘制沼泽地形
    plt.imshow(norm_maze, cmap=cmap, interpolation='nearest')

    # 叠加墙壁
    plt.imshow(wall_mask, cmap=mcolors.ListedColormap(['black', 'black']), alpha=wall_mask.astype(float))

    plt.title(name)
    plt.xticks(range(len(maze[0])))
    plt.yticks(range(len(maze)))
    plt.gca().set_xticks([x - 0.5 for x in range(1, len(maze[0]))], minor=True)
    plt.gca().set_yticks([y - 0.5 for y in range(1, len(maze))], minor=True)
    plt.grid(which="minor", color="black", linestyle='-', linewidth=2)

    # 逐步显示 visited
    for step in visited:
        plt.scatter(step[1], step[0], color='lightblue', s=100)
        plt.pause(interval)

    # 逐步显示路径
    for i in range(len(path)):
        if i == 0:
            plt.scatter(path[i][1], path[i][0], color='red', s=100)
        else:
            plt.plot([path[i-1][1], path[i][1]], [path[i-1][0], path[i][0]], marker='o', markersize=8, color='red', linewidth=3)
        plt.pause(interval)

    plt.axis('on')
    plt.show()




# # 提供迷宫的二维数组
# maze = [
#     [0, 1, 0, 0, 0],
#     [0, 1, 0, 1, 0],
#     [0, 0, 0, 0, 0],
#     [0, 1, 1, 1, 0],
#     [0, 0, 0, 1, 0]
# ]

# 假设给定路径的坐标列表
# path = [(0, 0), (1, 0), (2, 0), (2, 1), (2, 2), (2, 3), (2, 4), (3, 4), (4, 4)]
# visited = {(4, 4), (2, 4), (1, 2), (0, 4), (2, 1), (3, 4), (0, 0), (0, 3), (2, 0), (1, 4), (2, 3), (0, 2), (2, 2), (1, 0)}  

# 可视化迷宫及路径

#n m代表n行m列
# n, m = map(int, input().split())
# maze = [list(map(int, input().split())) for _ in range(m)]






maze = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 1, 1, 1, 0, 1, 1, 1, 1, 0],
    [1, 0, 0, 0, 0, 1, 1, 0, 1, 0],
    [1, 0, 1, 1, 0, 0, 0, 0, 1, 0],
    [1, 0, 1, 0, 0, 0, 1, 1, 0, 0],
    [1, 0, 1, 0, 1, 1, 1, 1, 0, 0],
    [1, 0, 1, 0, 0, 0, 0, 0, 0, 0],
    [1, 0, 1, 1, 1, 1, 1, 1, 1, 0],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 0]
]

#调试完毕
DFSstep,DFSpath = mazeDFS.DFS(maze,location=(0,0),path=[])
DFSvisited = mazeDFS.all_visited
visualize_maze_with_path(maze, DFSpath,DFSvisited,'DFS')


# 调试完毕
#DFS2不会全部搜索。direction不同也会导致最终路径不同
#默认 directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
DFSstep3,DFSpath3 = mazeDFS2.DFS(maze,location=(0,0),path=[],directions = [(0, 1),(-1, 0), (1, 0),(0, -1)])
DFSvisited3 = mazeDFS2.all_visited
visualize_maze_with_path(maze, DFSpath3,DFSvisited3,'DFS2-d1')

#调试完毕
#清空，随后展示更好的情况
mazeDFS2.all_visited = []
mazeDFS2.found_path =False
mazeDFS2.visited = set()
DFSstep2,DFSpath2 = mazeDFS2.DFS(maze,location=(0,0),path=[],directions = [(1, 0), (0, 1), (-1, 0), (0, -1)])
DFSvisited2 = mazeDFS2.all_visited
visualize_maze_with_path(maze, DFSpath2,DFSvisited2,'DFS2-d2') 

#调试完毕
BFSstep,BFSpath,BFSvisited = mazeBFS.BFS(maze)
visualize_maze_with_path(maze, BFSpath,BFSvisited,'BFS') 

# # directions = [(1, 0), (0, 1), (-1, 0), (0, -1)] 
DIJstep,DIJpath,DIJvisited = mazeDIJ.dijkstra(maze)
visualize_maze_with_path(maze, DIJpath,DIJvisited,'DIJ')

Astarstep,Astarpath,Astarvisited = mazeAstar.Astar(maze)
visualize_maze_with_path(maze, Astarpath,Astarvisited,'A*')

mazeadd = [
    [0, 0, 0, 0, 1, 1, 0, 0, 0, 0],  # 起点 (0,0)
    [1, 1, 1, 0, 1, 1, 0, 1, 1, 0],  
    [0, 6, 0, 0, 0, 1, 0, 1, 0, 0],  
    [0, 5, 1, 1, 0, 0, 0, 1, 0, 1],  
    [0, 4, 0, 1, 1, 1, 2, 1, 0, 0],  
    [0, 3, 0, 0, 0, 1, 3, 3, 2, 5],  
    [0, 2, 1, 1, 0, 1, 4, 3, 3, 2],  
    [0, 0, 0, 0, 0, 1, 5, 4, 3, 0]   # 终点 (7,9)
]


#调试完毕
BFSaddstep,BFSaddpath,BFSaddvisited = mazeBFSadd.BFS(mazeadd)
visualize_maze_with_path(mazeadd, BFSaddpath,BFSaddvisited,'BFSadd') 

#调试完毕
DIJaddstep,DIJaddpath,DIJaddvisited = mazeDIJadd.dijkstra(mazeadd)
visualize_maze_with_path(mazeadd, DIJaddpath,DIJaddvisited,'DIJadd')

#调试完毕
Astaraddstep,Astaraddpath,Astaraddvisited = mazeAstaradd.Astar(mazeadd)
visualize_maze_with_path(mazeadd, Astaraddpath,Astaraddvisited,'A*add')