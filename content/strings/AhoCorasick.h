/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: stress-tested
 */
#pragma once

struct AhoCorasick {
	enum {alpha = 26, first = 'A'}; // change this!
	struct Node {
		int fail = 0;
        int next[alpha];
        bool leaf = 0;
		Node() { memset(next, 0, sizeof(next)); }
	};
	vector<Node> N;
	void insert(const string& s) {
		assert(!s.empty());
		int u = 0;
		for (char c : s) {
			int nxt = N[u].next[c - first];
			if (!nxt) {
                nxt = N[u].next[c - first] = sz(N);
                N.emplace_back();
            }
			u = nxt;
		}
        N[u].leaf = 1;
	}
	AhoCorasick(const vector<string>& v) : N(1) {
		forn(i,0,sz(v)) insert(v[i]);

		queue<int> q;
        forn(i,0,alpha) if (N[0].next[i]) q.push(N[0].next[i]);
		for (; !q.empty(); q.pop()) {
			int u = q.front(), prev = N[u].fail;
			forn(i,0,alpha) {
				int& nxt = N[u].next[i];
                int y = N[prev].next[i];
				if (!nxt) nxt = y;
				else {
					N[nxt].fail = y;
					q.push(nxt);
				}
			}
		}
	}
};
