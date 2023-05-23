/**
 * Author: Evirir
 * Date: 2022-05-20
 * License: CC0
 * Source: own
 * Description: Centroid decomposition. Two independent functions:
 * (1) \texttt{build\_tree} builds the centroid tree. (2) \texttt{solve}
 * Time: \texttt{build\_tree} is $O(n \log n)$. \texttt{solve}:
 * Every node is processed by $O(\log n)$ roots. $O(n \log n)$ if you
 * do $O(\text{centroid subtree size})$ time per root.
 * Status: tested
 */

vector<vector<int>> adj; // adjacency list
int sz[MAXN];   // subtree size w.r.t. current root
bool vst[MAXN]; // whether it has been some root
int cprt[MAXN]; // centroid tree parent
vector<int> child[MAXN]; // subtree of centroid tree

void dfs_sz(int u, int p) {
	sz[u] = 1;
	for(int v : adj[u]) {
		if(v == p || vst[v]) continue;
		dfs_sz(v, u);
		sz[u] += sz[v];
	}
}
int centroid(int u, int p, int r) {
	for(int v : adj[u]) {
		if (v == p || vst[v]) continue;
		if (sz[v] * 2 > sz[r]) return centroid(v, u, r);
	}
	return u;
}
int build_tree(int u) {  // do mset(cprt, -1); before calling this!
	dfs_sz(u, -1);
	u = centroid(u, -1, u);
	vst[u] = true;
	for (int v : adj[u]) {
		if (vst[v]) continue;
		cprt[build_tree(v)] = u;
	}
	return u;
}
void solve(int u) {
	dfs_sz(u, -1);
	u = centroid(u, -1, u);
	// Do stuff. When iter-ing neighbors, skip visited nodes (and parent)! In DFS:
	// for (int v : adj[u]) {
	//     if (vst[v] || v == p) continue;
	// }
	vst[u] = true;
	for (int v : adj[u]) {
		if (vst[v]) continue;
		solve(v);
	}
}
