class Solution {
public:
    typedef pair<int,int> pii;
    typedef long long ll;

    vector<vector<pair<int,int>>> adj;
    priority_queue<pair<ll,pii>, vector<pair<ll,pii>>, greater<pair<ll,pii>>> pq;

    int n, k;

    int solve(int src, int dest, vector<vector<ll>>& dist, string &labels) {
        pq.push({0, {src, 1}});
        dist[src][1] = 0;

        while(!pq.empty()) {
            auto it = pq.top();
            pq.pop();

            ll d = it.first;
            int u = it.second.first;
            int cnt = it.second.second;

            if(d > dist[u][cnt]) continue;

            if(u == dest) return d;

            for(auto &a : adj[u]) {
                int v = a.second;
                int wt = a.first;

                int newCnt = (labels[u] == labels[v]) ? cnt + 1 : 1;

                if(newCnt > k) continue;

                if(dist[v][newCnt] > d + wt) {
                    dist[v][newCnt] = d + wt;
                    pq.push({dist[v][newCnt], {v, newCnt}});
                }
            }
        }

        return -1;
    }

    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        this->n = n;
        this->k = k;

        adj.resize(n);

        for(auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({w, v});
        }

        vector<vector<ll>> dist(n, vector<ll>(k + 1, LLONG_MAX));

        return solve(0, n - 1, dist, labels);
    }
};

