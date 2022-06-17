#include <iostream>
#include <fstream>
#include <iomanip>
#include "header/Graph.hpp"
#include "header/ShortestPath.hpp"
#include "header/randomGraph.hpp"
using std::cin;
using std::cout;
using std::endl;

#define START_CLOCK \
    {               \
        std::clock_t __FIRST__CLOCK__ = std::clock();
#define END_CLOCK(out)                                                              \
    std::clock_t __SECOND__CLOCK__ = std::clock();                                  \
    out << std::setiosflags(std::ios::fixed);                                       \
    out << std::setprecision(6);                                                    \
    out << (double)(__SECOND__CLOCK__ - __FIRST__CLOCK__) / CLOCKS_PER_SEC << endl; \
    }

std::ofstream outInfo(".\\test\\outInfo.txt", std::ios::out);
std::ofstream outDijkstra(".\\test\\outDijkstra.txt", std::ios::out);
std::ofstream outBellmanFord(".\\test\\outBellmanFord.txt", std::ios::out);
std::ofstream outFloyd(".\\test\\outFloyd.txt", std::ios::out);
std::ofstream outJohnson(".\\test\\outJohnson.txt", std::ios::out);

void printResult(std::ostream &_out, const distanceMatrix &_result)
{
    if (_result.first == false)
    {
        _out << "Failed!" << endl;
    }
    else
    {
        int N = _result.second.size();
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                _out << _result.second[i][j] << " ";
            }
            _out << endl;
        }
    }
}

int main()
{
    Graph g;
    randomGraphGenerator rnd(1000, 1.5, 1, false);
    rnd(g);

    outInfo << "E: " << endl;
    outInfo << g.numberOfEdges() << endl;
    outInfo << "V: " << endl;
    outInfo << g.numberOfNodes() << endl;

    distanceMatrix s1, s2, s3, s4;
    START_CLOCK;
    s1 = Dijkstra(g);
    outInfo << "Dijkstra time: " << endl;
    END_CLOCK(outInfo);
    printResult(outDijkstra, s1);

    START_CLOCK;
    s2 = BellmanFord(g);
    outInfo << "Bellman-Ford time: " << endl;
    END_CLOCK(outInfo);
    printResult(outBellmanFord, s2);

    START_CLOCK;
    s3 = Floyd(g);
    outInfo << "Floyd time: " << endl;
    END_CLOCK(outInfo);
    printResult(outFloyd, s3);

    START_CLOCK;
    s4 = Johnson(g);
    outInfo << "Johnson time: " << endl;
    END_CLOCK(outInfo);
    printResult(outJohnson, s4);

    outInfo.close();
    outDijkstra.close();
    outBellmanFord.close();
    outFloyd.close();
    outJohnson.close();
    return 0;
}