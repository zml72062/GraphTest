# GraphTest
Test for various shortest-path algorithms on graphs.

仓库地址: [https://github.com/zml72062/GraphTest](https://github.com/zml72062/GraphTest)

## 概述
这是一个测试各种图上 **最短路径算法** 的 repository. 如果记图 $G$ 中的顶点数为 $V$, 边数为 $E$, 一些通用的最短路径算法的时间复杂度如下表所示

|算法名称|求任意两点间最短路径的时间复杂度|说明|
|:--|:--|:--|
|Dijkstra (邻接表 + 二叉堆)|$O(EV\log V+V^2\log V)$|只适用于非负权边|
|Dijkstra (邻接表 + Fibonacci 堆)| $O(EV+V^2\log V)$|只适用于非负权边|
|Bellman-Ford (邻接表)| $O(EV^2)$|适用于负权边, 可判断负权环|
|Floyd|$O(V^3)$|适用于负权边, 不可判断负权环|
|Johnson (采用 Fibonacci 堆的 Dijkstra 算法)|$O(EV+V^2\log V)$|适用于负权边, 可判断负权环|

## 具体实现说明

* `/header` 目录下放置了本依赖的头文件
    + `Graph.hpp`