/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Using Tarjan To get the BlockForest.
 */
#pragma once
void Tarjan(int p){
	dfsn[p]=low[p]=++cnt;
	st[++top]=p;
	Rep(i,E,p){
		int v=E[p][i];
		if(dfsn[v]) low[p]=min(low[p],dfsn[v]); else{
			Tarjan(v);
			low[p]=min(low[p],low[v]);
			if(low[v]==dfsn[p]){
				tot++;
				for(int x=0;x!=v;top--){
					x=st[top];
					e[tot].push_back(x);
					e[x].push_back(tot);
				}
				e[tot].push_back(p);
				e[p].push_back(tot);
			}
		}
	}
}
