#ifndef GRAPH_HPP
#define GRAPH_HPP

#define MAX_NODES 25 

class CampusGraph {
private:
    int distanceMatrix[MAX_NODES][MAX_NODES];
    const int INF = 999999;

public:
    CampusGraph() {
        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NODES; j++) {
                distanceMatrix[i][j] = (i == j) ? 0 : INF; 
            }
        }
    }

    void addEdge(int u, int v, int weight) {
        int i = u - 100; 
        int j = v - 100;
        if (i >= 0 && i < MAX_NODES && j >= 0 && j < MAX_NODES) {
            distanceMatrix[i][j] = weight;
            distanceMatrix[j][i] = weight; 
        }
    }

    /**
     * @brief Computes the shortest path using Dijkstra's Algorithm.
     */
    int getShortestPath(int sourceId, int targetId) {
        int src = sourceId - 100;
        int dest = targetId - 100;

        int dist[MAX_NODES];
        bool visited[MAX_NODES];

        for (int i = 0; i < MAX_NODES; i++) {
            dist[i] = INF;
            visited[i] = false;
        }

        dist[src] = 0;

        for (int count = 0; count < MAX_NODES - 1; count++) {
            int u = -1;
            int minVal = INF;

            for (int v = 0; v < MAX_NODES; v++) {
                if (!visited[v] && dist[v] <= minVal) {
                    minVal = dist[v];
                    u = v;
                }
            }

            if (u == -1) break; 
            visited[u] = true;

            for (int v = 0; v < MAX_NODES; v++) {
                if (!visited[v] && distanceMatrix[u][v] != INF && 
                    dist[u] != INF && dist[u] + distanceMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + distanceMatrix[u][v];
                }
            }
        }

        return dist[dest];
    }
};

#endif