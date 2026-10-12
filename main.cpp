#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 3005;
const int INF = 1e9;

struct Edge {
    int to, cap, rev;
    Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

vector<Edge> graph[MAXN];
int level[MAXN];
int iter[MAXN];

void add_edge(int from, int to, int cap) {
    graph[from].push_back(Edge(to, cap, graph[to].size()));
    graph[to].push_back(Edge(from, cap, graph[from].size() - 1));
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int i = 0; i < graph[v].size(); i++) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < graph[v].size(); i++) {
        Edge &e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    // Clear graph
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
    }
    
    // Read edges
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b, 1);  // Each pipe has capacity 1
    }
    
    // Calculate sum of max flows for all pairs (a,b) where a < b
    long long total_flow = 0;
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            // Reset graph for each flow calculation
            for (int i = 1; i <= n; i++) {
                for (auto &e : graph[i]) {
                    if (i < e.to) {  // Only reset each edge once
                        // We need to restore original capacities
                        // Since we're using symmetric edges, we need to be careful
                        // Let's rebuild the graph for each pair
                    }
                }
            }
            // Rebuild graph for this pair
            // We'll rebuild the entire graph for each pair to ensure clean state
            vector<pair<int, int>> edges;
            for (int i = 1; i <= n; i++) {
                for (auto &e : graph[i]) {
                    if (i < e.to) {  // Only store each edge once
                        edges.push_back({i, e.to});
                    }
                }
            }
            // Clear and rebuild
            for (int i = 1; i <= n; i++) {
                graph[i].clear();
            }
            for (auto &e : edges) {
                add_edge(e.first, e.second, 1);
            }
            
            total_flow += max_flow(a, b);
        }
    }
    
    cout << total_flow << endl;
    
    return 0;
}