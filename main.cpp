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
#define END_CLOCK(out)                                                             \
    std::clock_t __SECOND__CLOCK__ = std::clock();                                 \
    out << std::setiosflags(std::ios::fixed);                                      \
    out << std::setprecision(6);                                                   \
    out << std::setw(12);                                                          \
    out << (double)(__SECOND__CLOCK__ - __FIRST__CLOCK__) / CLOCKS_PER_SEC << " "; \
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
    double expo = 4.2;
    if (expo < 7)
    {
        Graph g;
        randomGraphGenerator rnd(static_cast<int>(std::exp(expo)), 2, 0.4, false);
        rnd(g);
        outInfo << std::setw(8) << static_cast<int>(std::exp(expo)) << " ";
        distanceMatrix s1, s2, s3, s4;
        START_CLOCK;
        s1 = Dijkstra(g);
        printResult(outDijkstra, s1);
        END_CLOCK(outInfo);

        START_CLOCK;
        s2 = BellmanFord(g);
        printResult(outBellmanFord, s2);
        END_CLOCK(outInfo);

        START_CLOCK;
        s3 = Floyd(g);
        printResult(outFloyd, s3);
        END_CLOCK(outInfo);

        START_CLOCK;
        s4 = Johnson(g);
        printResult(outJohnson, s4);
        END_CLOCK(outInfo);
        outInfo << endl;
        expo += 0.1;
    }

    outInfo.close();
    outDijkstra.close();
    outBellmanFord.close();
    outFloyd.close();
    outJohnson.close();
    return 0;
}