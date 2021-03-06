#ifndef RANDOM_GRAPH_H
#define RANDOM_GRAPH_H

#include <random>
#include "Graph.hpp"
#include <ctime>
#include <cmath>
#include <unordered_set>

class randomGraphGenerator
{
public:
    randomGraphGenerator(int _numOfVertices, double _power, double _constant, bool _hasNegative) : rng(time(nullptr)), numOfVertices(_numOfVertices), power(_power), constant(_constant), hasNegative(_hasNegative) {}
    void setNumOfVertices(int _numOfVertices)
    {
        numOfVertices = _numOfVertices;
    }
    int getNumOfVertices() const { return numOfVertices; }
    void setPower(double _power)
    {
        power = _power;
    }
    void setConstant(double _constant)
    {
        constant = _constant;
    }
    void setHasNegative(bool _hasNegative)
    {
        hasNegative = _hasNegative;
    }
    void setLowerBound(int _loBound)
    {
        loBound = _loBound;
    }
    void setUpperBound(int _hiBound)
    {
        hiBound = _hiBound;
    }
    void operator()(Graph &_graph)
    {
        _graph.clear();
        for (auto i = 0; i < numOfVertices; ++i)
        {
            _graph.addNode();
        }
        auto c = static_cast<int>(constant * std::pow(numOfVertices, power));
        if (c > numOfVertices * (numOfVertices - 1))
        {
            c = numOfVertices * (numOfVertices - 1);
        }
        // 建立一个 1 ~ n*n 列表, 去掉对角线上元素, 然后随机撒点
        std::unordered_set<int> us;
        for (auto i = 0; i < numOfVertices; ++i)
        {
            us.insert(i * numOfVertices + i);
        }
        std::uniform_real_distribution<> number(0, 1);
        std::uniform_int_distribution<> length(0, hiBound);
        if (hasNegative)
        {
            length = std::uniform_int_distribution<>(loBound, hiBound);
        }
        for (auto i = 0; i < c; ++i)
        {
        randomfind:
            int next_int = static_cast<int>(number(rng) * numOfVertices * numOfVertices);
            if (us.find(next_int) != us.end())
            {
                goto randomfind;
            }
            int begin = next_int % numOfVertices;
            int end = next_int / numOfVertices;
            _graph.addEdge(begin, end, length(rng));
            us.insert(next_int);
        }
    }

private:
    std::default_random_engine rng;
    // E ~ constant * (V ** power), 1 <= power <= 2
    double constant;
    double power;
    int numOfVertices;
    bool hasNegative;
    int loBound = -50;
    int hiBound = 10000;
};
#endif