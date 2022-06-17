#include "header/ShortestPath.hpp"
#include <limits.h>
#include <set>
#include <queue>
#include <algorithm>

// 最短路搜索算法中的节点
struct DistNode
{
    DistNode(int _index, int _distance)
    {
        index = _index;
        distance = _distance;
    }
    int index;
    int distance;
    bool operator<(const DistNode &_right) const
    {
        return distance < _right.distance || distance == _right.distance && index < _right.index;
    }
};

// 支持 decreaseKey 操作的优先队列, 用 std::set 实现
class PriorityQueue
{
public:
    std::size_t size() const noexcept
    {
        return data.size();
    }
    bool empty() const noexcept
    {
        return data.empty();
    }
    void push(const DistNode &_node)
    {
        data.insert(_node);
    }
    void push(DistNode &&_node)
    {
        data.insert(_node);
    }
    const DistNode &top() const
    {
        return *data.begin();
    }
    void pop()
    {
        data.erase(data.begin());
    }
    void decreaseKey(const DistNode &_target, int _key)
    {
        auto p = data.find(_target);
        if (p == data.end())
            return;
        data.erase(p);
        data.insert(DistNode(_target.index, _key));
    }
    void decreaseKey(DistNode &&_target, int _key)
    {
        auto p = data.find(_target);
        if (p == data.end())
            return;
        data.erase(p);
        data.insert(DistNode(_target.index, _key));
    }

private:
    std::set<DistNode> data;
};

distances Dijkstra(const Graph &_graph, int _index)
{
    std::size_t V = _graph.numberOfNodes();
    vector<int> dist(V, INT_MAX);
    dist[_index] = 0;
    PriorityQueue pq;
    pq.push(DistNode(_index, 0));
    while (!pq.empty())
    {
        auto s = pq.top();
        pq.pop();
        auto e = _graph.nodeOf(s.index).numberOfEdges();
        for (auto i = 0; i < e; ++i)
        {
            int indexTemp = _graph.nodeOf(s.index).edgeOf(i).end;
            if (dist[indexTemp] == INT_MAX)
            {
                dist[indexTemp] = dist[s.index] + _graph.nodeOf(s.index).edgeOf(i).cost;
                pq.push(DistNode(indexTemp, dist[indexTemp]));
            }
            else
            {
                auto update = dist[s.index] + _graph.nodeOf(s.index).edgeOf(i).cost;
                if (update < dist[indexTemp])
                {
                    pq.decreaseKey(DistNode(indexTemp, dist[indexTemp]), update);
                    dist[indexTemp] = update;
                }
            }
        }
    }
    return std::make_pair(true, dist);
}

distances BellmanFord(const Graph &_graph, int _index)
{
    std::size_t V = _graph.numberOfNodes();
    vector<int> dist(V, INT_MAX);
    dist[_index] = 0;

    for (auto repeat = 1; repeat <= V; ++repeat)
    {
        for (auto c = 0; c < V; ++c)
        {
            auto indexCur = (_index + c) % V;
            auto e = _graph.nodeOf(indexCur).numberOfEdges();
            for (auto i = 0; i < e; ++i)
            {
                int indexTemp = _graph.nodeOf(indexCur).edgeOf(i).end;
                if (dist[indexCur] != INT_MAX)
                {
                    auto update = dist[indexCur] + _graph.nodeOf(indexCur).edgeOf(i).cost;
                    if (update < dist[indexTemp])
                    {
                        dist[indexTemp] = update;
                        if (repeat == V)
                        {
                            return std::make_pair(false, dist);
                        }
                    }
                }
            }
        }
    }
    return std::make_pair(true, dist);
}

distanceMatrix Dijkstra(const Graph &_graph)
{
    std::size_t V = _graph.numberOfNodes();
    vector<vector<int>> ans;
    for (auto i = 0; i < V; ++i)
    {
        distances d = Dijkstra(_graph, i);
        ans.push_back(d.second);
    }
    return std::make_pair(true, ans);
}

distanceMatrix BellmanFord(const Graph &_graph)
{
    std::size_t V = _graph.numberOfNodes();
    vector<vector<int>> ans;
    for (auto i = 0; i < V; ++i)
    {
        distances d = BellmanFord(_graph, i);
        if (!d.first)
        {
            return std::make_pair(false, ans);
        }
        ans.push_back(d.second);
    }
    return std::make_pair(true, ans);
}

distanceMatrix AdjacencyMatrix(const Graph &_graph)
{
    std::size_t V = _graph.numberOfNodes();
    vector<vector<int>> ans(V, vector<int>(V, INT_MAX));
    for (auto i = 0; i < V; ++i)
    {
        ans[i][i] = 0;
    }
    for (auto i = 0; i < V; ++i)
    {
        auto e = _graph.nodeOf(i).numberOfEdges();
        for (auto j = 0; j < e; ++j)
        {
            ans[i][_graph.nodeOf(i).edgeOf(j).end] = _graph.nodeOf(i).edgeOf(j).cost;
        }
    }
    return std::make_pair(true, ans);
}

distanceMatrix Floyd(const Graph &_graph)
{
    std::size_t V = _graph.numberOfNodes();
    vector<vector<int>> ans = AdjacencyMatrix(_graph).second;
    for (auto k = 0; k < V; ++k)
    {
        for (auto i = 0; i < V; ++i)
        {
            for (auto j = 0; j < V; ++j)
            {
                if (ans[i][k] == INT_MAX || ans[k][j] == INT_MAX)
                {
                    ans[i][j] = ans[i][j];
                }
                else
                {
                    ans[i][j] = std::min(ans[i][j], ans[i][k] + ans[k][j]);
                }
            }
        }
    }
    return std::make_pair(true, ans);
}

distanceMatrix Johnson(Graph &_graph)
{
    _graph.addNode();
    vector<vector<int>> ans;
    auto V = _graph.numberOfNodes() - 1;
    for (auto i = 0; i < V; ++i)
    {
        _graph.addEdge(V, i, 0);
    }
    auto s = BellmanFord(_graph, V);
    if (!s.first)
    {
        return std::make_pair(false, ans);
    }
    s.second.pop_back();
    _graph.deleteBack();
    for (auto i = 0; i < V; ++i)
    {
        auto e = _graph.nodeOf(i).numberOfEdges();
        for (auto j = 0; j < e; ++j)
        {
            auto begin = i;
            auto end = _graph.nodeOf(i).edgeOf(j).end;
            _graph.nodeOf(i).edgeOf(j).cost += (s.second[begin] - s.second[end]);
        }
    }
    auto t = Dijkstra(_graph);
    for (auto i = 0; i < V; ++i)
    {
        for (auto j = 0; j < V; ++j)
        {
            if (t.second[i][j] != INT_MAX)
            {
                t.second[i][j] += (s.second[j] - s.second[i]);
            }
        }
    }
    return t;
}