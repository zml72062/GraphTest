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
    + `Graph.hpp`: 包含图的类 `Graph`, 其节点下标按照顺序 `0, 1, ..., V-1` 标记, 边由邻接表存储. 提供下列 API,
        * 类 `Graph`
            + `numberOfNodes()` 返回节点数目 $V$
            + `numberOfEdges()` 返回边数目 $E$
            + `nodeOf(int _index)` 访问下标为 `_index` 的节点的引用, 返回值是一个结构体 `Graph::Node` 的引用
            + `addNode()` 添加一个节点, 其下标顺延
            + `hasEdge(int _start, int _end)` 判断下标为 `_start` 和 `_end` 的节点之间是否有边相连
            + `addEdge(int _start, int _end, int _cost)` 在下标为 `_start` 和 `_end` 的节点之间添加一条权为 `_cost` 的边
            + `deleteEdge(int _start, int _end)` 如标为 `_start` 和 `_end` 的节点之间有边相连, 删除之
            + `deleteBack()` 删除下标最大的节点以及与它相连的所有边
            + `clear()` 清除整个图中的顶点和边
        * 结构体 `Graph::Node`
            + `numberOfEdges()` 返回出边数
            + `edgeOf(int _number)` 访问邻接表中下标为 `_number` 的边的引用, 它是一个结构体 `Graph::Edge` 的引用
        * 结构体 `Graph::Edge`
            + 字段 `end` 表示边的终点下标
            + 字段 `cost` 表示边权

    + `randomGraph.hpp`: 包含 "随机图生成器" 类 `randomGraphGenerator`, 它在 $V$ 个顶点之间随机连 $$E=\min\left\{CV^\alpha,\frac{V(V-1)}{2}\right\}$$条互异的边来构成一个图. 其中 $C$ 和 $\alpha$ 是常数, 并且有 $1\leqslant \alpha\leqslant 2$. 提供下列 API,
        + 类 `randomGraphGenerator`
            * `setNumOfVertices(int _numOfVertices)` 设置 $V$ 为 `_numOfVertices`
            * `setPower(double _power)` 设置 $\alpha$ 为 `_power`
            * `setConstant(double _constant)` 设置 $C$ 为 `_constant`
            * `setHasNegative(bool _hasNegative)` 设置是否要在随机图中生成负权边, 如果 `_hasNegative` 为 `true` 则会生成负权边
            * `setUpperBound(int _hiBound)` 设置边权最大值为 `_hiBound`
            * `setLowerBound(int _loBound)` 如允许负权边, 设置边权最小值为 `_loBound` (应小于 0, 但别太小了以免生成负权环)
            * `operator()(Graph& _graph)` 将 `_graph` 生成为所要的随机图
    + `shortestPath.hpp`: 包含 "最短路径算法" 的一系列函数. 提供下列内容
        + 类型 `distances`, 它等同于 `std::pair<bool, std::vector<int>>`, 其 `first` 成员代表最短路径是否存在 (若为 `true`, 则存在最短路), 其 `second` 成员代表各节点到指定节点的最短路径长 (如果有的话)
        + 类型 `distanceMatrix`, 它等同于 `std::pair<bool, std::vector<std::vector<int>>>`, 其 `first` 成员代表最短路径是否存在 (若为 `true`, 则存在最短路), 其 `second` 成员代表各节点对之间的最短路径长 (如果有的话)