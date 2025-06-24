#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> adj_t;

class BinaryLifting {
    int n, LOG;
    vector<int> depth;
    vector<vector<int>> up;

    void dfs(int u, int p, const adj_t& adj) {
        up[0][u] = p;
        depth[u] = (p < 0 ? 0 : depth[p] + 1);
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u, adj);
        }
    }
public:
    BinaryLifting(const adj_t& adj, int root = 0) {
        n = adj.size();
        LOG = 32 - __builtin_clz(n);
        depth.assign(n, 0);
        up.assign(LOG, vector<int>(n, -1));
        dfs(root, -1, adj);
        for (int i = 1; i < LOG; i++) {
            for (int v = 0; v < n; v++) {
                int p = up[i-1][v];
                up[i][v] = (p < 0 ? -1 : up[i-1][p]);
            }
        }
    }
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++)
            if (diff & (1<<i))
                u = up[i][u];
        if (u == v) return u;
        for (int i = LOG-1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }
        return up[0][u];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    adj_t adj(n);
    for(int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    BinaryLifting bl(adj, 0);

    while(q--){
        int u, v;
        cin >> u >> v;
        cout << bl.lca(u, v) << "\n";
    }
    return 0;
}
