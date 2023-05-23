/**
 * Author: Evirir
 * Date: 2022-05-22
 * License: CC0
 * Source: own
 * Description: Single-source shortest paths.
 * Time: $O(V + E \log V)$.
 * Status: tested
 */
#pragma once

vector<ii> adj[MAXN];  // (node, distance)
ll dist[MAXN];
// int parents[MAXN];

void dijkstra(int src) {
    priority_queue<ii, vector<ii>, greater<ii>> q; // (distance, node)
    fill(dist, dist + n, INF);
    // fill(parents, parents + n, -1);
    dist[src] = 0;
    q.push({dist[src], src});
    while (!q.empty()) {
        auto [cur_dist, u] = q.top();
        q.pop();
        if (cur_dist > dist[u]) continue;
        for (auto [v, w] : adj[u])
        {
            if (dist[v] <= cur_dist + w) continue;
            dist[v] = cur_dist + w;
            // parents[v] = u;
            q.push({dist[v], v});
        }
    }
}
