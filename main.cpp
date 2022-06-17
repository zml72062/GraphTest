#include <iostream>
#include "Graph.hpp"
#include "ShortestPath.hpp"
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (auto i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u - 1, v - 1, w);
    }
    auto s = Johnson(g);
    if (!s.first)
    {
        cout << -1 << endl;
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (s.second[i][j] == INT_MAX)
                {
                    s.second[i][j] = 1000000000;
                }
            }
            long long sum = 0;
            for (int j = 0; j < n; ++j)
            {
                sum += (long long)(j + 1) * (long long)(s.second[i][j]);
            }
            cout << sum << endl;
        }
    }
    return 0;
}