#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "Graph.hpp"
#include <utility>
using std::pair;

using distances = pair<bool, vector<int>>;
using distanceMatrix = pair<bool, vector<vector<int>>>;

/** 单源最短路径算法:
 *
 *  返回值是一个 pair<bool, vector<int>>
 *      若 first = true, 表示没有负权环, 在 second 中存储了到各节点的最短路径长
 *      若 first = false, 表示有负权环, 最短路不存在
 *
 */

// 用 Dijkstra 算法求解 *非负权值* 单源最短路径
distances Dijkstra(const Graph &_graph, int _index);
// 注: Dijkstra 算法不能判断负权环的存在, 所以 first 永为 true

// 用 Bellman-Ford 算法求解 *任意权值* 单源最短路径
distances BellmanFord(const Graph &_graph, int _index);

/** 全源最短路径算法:
 *
 *  返回值是一个 pair<bool, vector<vector<int>>>
 *      若 first = true, 表示没有负权环, 在 second 中存储了各节点对之间的最短路径长
 *      若 first = false, 表示有负权环, 最短路不存在
 *
 */

// 用 Dijkstra 算法求解 *非负权值* 全源最短路径
distanceMatrix Dijkstra(const Graph &_graph);
// 用 Floyd 算法求解 *任意权值* 全源最短路径
distanceMatrix Floyd(const Graph &_graph);
// 注: 以上算法不能判断负权环的存在, 所以 first 永为 true

// 用 Bellman-Ford 算法求解 *任意权值* 全源最短路径
distanceMatrix BellmanFord(const Graph &_graph);
// 用 Johnson 算法求解 *任意权值* 全源最短路径
distanceMatrix Johnson(Graph &_graph);

#endif