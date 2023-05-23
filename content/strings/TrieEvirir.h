/**
 * Author: Evirir
 * Date: 2022-05-20
 * License: CC0
 * Source: own
 * Description: Builds a trie. Also has a DFS function.
 * Time: $O(|s|)$ for add($s$).
 * Status: tested
 */
#pragma once

struct TrieNode {
	int next[26];  // change 26 to alphabet size
	bool leaf = false;
	TrieNode(){fill(begin(next), end(next), -1);}
};
struct Trie {
	int siz;
	vector<TrieNode> tr;
	Trie(): siz(0), tr(vector<TrieNode>(1)) {}
	TrieNode& operator[](int u){ return tr[u]; }
	int size(){ return siz; }
	void add(const string &s) {
		int v = 0;
		for (char ch : s) {
			int c = ch - 'a';  // change this
			if (tr[v].next[c] == -1) {
				tr[v].next[c] = tr.size();
				tr.emplace_back();
			}
			v = tr[v].next[c];
		}
		if(!tr[v].leaf) siz++;
		tr[v].leaf = true;
	}
	template<class F>
	void dfs(int u, F f) {
        // use function f as callback
		forn(i,0,26) {  // change this 26
			if(tr[u].next[i] != -1) {
				dfs(tr[u].next[i]);
			}
		}
	}
};