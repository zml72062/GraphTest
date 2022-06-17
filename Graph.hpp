#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stdexcept>
using std::vector;

// 类 Graph : 表示一个图
class Graph
{
public:
    using NodeType = int;

    struct Edge
    {
        Edge(NodeType _end, int _cost)
        {
            end = _end;
            cost = _cost;
        }
        NodeType end;
        int cost;
    };

    struct Node
    {
    public:
        Node(NodeType _index)
        {
            index = _index;
        }
        // 节点禁止拷贝, 禁止移动, 禁止赋值给另一个节点
        Node(const Node &) = delete;
        Node(Node &&) = delete;
        Node &operator=(const Node &) = delete;
        Node &operator=(Node &&) = delete;

        // 返回下标为 _number 的边
        const Edge &edgeOf(std::size_t _number) const
        {
            if (_number >= numberOfEdges())
            {
                throw std::out_of_range("Can't find this edge!");
            }
            return *(edges[_number]);
        }
        Edge &edgeOf(std::size_t _number)
        {
            if (_number >= numberOfEdges())
            {
                throw std::out_of_range("Can't find this edge!");
            }
            return *(edges[_number]);
        }

        // 出边数
        std::size_t numberOfEdges() const noexcept
        {
            return edges.size();
        }

        friend class Graph;
        ~Node() noexcept
        {
            std::size_t n = edges.size();
            for (auto i = 0; i < n; ++i)
            {
                delete edges[i];
            }
        }

    private:
        NodeType index;
        vector<Edge *> edges;
    };
    Graph() = default;

    // 构造一个含有 _numOfNodes 个节点的图, 节点指标为 0, 1, ...
    explicit Graph(std::size_t _numOfNodes) : nodes(_numOfNodes)
    {
        for (auto i = 0; i < _numOfNodes; ++i)
        {
            nodes[i] = new Node(i);
        }
    }
    // 图禁止拷贝, 禁止移动, 禁止赋值给另一个图
    Graph(const Graph &) = delete;
    Graph(Graph &&) = delete;
    Graph &operator=(const Graph &) = delete;
    Graph &operator=(Graph &&) = delete;

    // 添加一个节点
    void addNode()
    {
        nodes.push_back(new Node(nodes.size()));
    }
    // 添加一条始于 _start, 终于 _end, 权为 _cost 的边
    void addEdge(int _start, int _end, int _cost)
    {
        nodes[_start]->edges.push_back(new Edge(_end, _cost));
    }
    // 返回下标为 _index 的节点
    const Node &nodeOf(std::size_t _index) const
    {
        return *(nodes[_index]);
    }
    Node &nodeOf(std::size_t _index)
    {
        return *(nodes[_index]);
    }
    // 节点数
    std::size_t numberOfNodes() const noexcept
    {
        return nodes.size();
    }
    // 边数
    std::size_t numberOfEdges() const noexcept
    {
        std::size_t i = 0, n = nodes.size();
        for (auto j = 0; j < n; ++j)
        {
            i += nodes[j]->numberOfEdges();
        }
        return i;
    }
    // 判断 _start 与 _end 之间是否有边相连
    bool hasEdge(int _start, int _end) const
    {
        for (auto &p : nodes[_start]->edges)
        {
            if (p->end == _end)
            {
                return true;
            }
        }
        return false;
    }
    // 如果 _begin 与 _end 之间有边相连, 删除这条边
    void deleteEdge(int _start, int _end)
    {
        for (auto p = nodes[_start]->edges.begin(); p != nodes[_start]->edges.end(); ++p)
        {
            if ((*p)->end == _end)
            {
                delete *p;
                nodes[_start]->edges.erase(p);
                break;
            }
        }
    }
    // 删除最后一个节点
    void deleteBack()
    {
        delete nodes[nodes.size() - 1];
        nodes.pop_back();
        for (auto &p : nodes)
        {
            for (auto q = p->edges.begin(); q != p->edges.end(); ++q)
            {
                if ((*q)->end == nodes.size())
                {
                    delete *q;
                    p->edges.erase(q);
                    break;
                }
            }
        }
    }
    ~Graph() noexcept
    {
        std::size_t n = nodes.size();
        for (auto i = 0; i < n; ++i)
        {
            delete nodes[i];
        }
    }

private:
    vector<Node *> nodes;
};

#endif