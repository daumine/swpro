#include <vector>
#include <iostream>
#include <climits>

using namespace std;

struct Edge {
    int src;
    int dst;
    int weight;
};

const int UNKNOWN = INT_MAX;

vector<int> BelmanFord(vector<Edge> edges, int V, int start)
{
    vector<int> distance(V, UNKNOWN);
    distance[start] = 0;

    for(int i = 0; i < V-1; i++) {
        for(auto &e: edges) {
            if(distance[i] == UNKNOWN)
                continue;
        
            if(distance[e.dst] > distance[e.src] + e.weight) {
                distance[e.dst] = distance[e.src] + e.weight;
            }
        }
    }

    return distance;
}

int main()
{
    int V = 5;
    vector<Edge> edges;

    vector<vector<int>> edge_map {
        {0, 1, 3},
        {1, 2, 5,},
        {1, 3, 10},
        {3, 2, -7},
        {2, 4, 2}
    };

    for(auto &e: edge_map) {
        edges.emplace_back(Edge {e[0], e[1], e[2]});
    }

    int start = 0; 
    vector<int> distance = BelmanFord(edges, V, start);

    cout << "[ From " << start << " minimum length]" << endl;

    for (int i = 0 ; i < distance.size(); i++) {
        if(distance[i] == UNKNOWN) {
            cout << i << "not visited" << endl;
        }
        else {
            cout << "edge " << i << ": " << distance[i] << endl;
        }
    }
}