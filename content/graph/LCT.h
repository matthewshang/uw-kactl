/**
 * Author: Kaiyuan Liu
 * Date: 2016-07-25
 * Source: hahaha
 * Description: Represents a forest of unrooted trees. You can add and remove
 * edges (as long as the result is still a forest), and check whether
 * two nodes are in the same tree.
 * Time: All operations take amortized O(\log N).
 * Status: Stress-tested a bit for N <= 20
 */
#pragma once
struct node{
	int child[2],val,sum,fa,tag;
}tree[N];
int n,m;
//Splay part
inline void upd(int p){
	tree[p].sum=tree[son(p,0)].sum^tree[son(p,1)].sum^tree[p].val;
}
inline void pushdown(int p){
	if(tree[p].tag) swap(son(p,1),son(p,0));
	tree[son(p,1)].tag^=tree[p].tag;
	tree[son(p,0)].tag^=tree[p].tag;
	tree[p].tag=0;
}
inline int soncheck(int p){
	return son(tree[p].fa,1)==p;
}
inline bool rootcheck(int p){
	return son(tree[p].fa,1)!=p&&son(tree[p].fa,0)!=p;
}
inline void rotate(int p){
	int f=tree[p].fa,g=tree[f].fa,k=soncheck(p);
	if(!rootcheck(f)) son(g,soncheck(f))=p;
	tree[p].fa=g,son(f,k)=son(p,k^1),tree[son(p,k^1)].fa=f;
	son(p,k^1)=f,tree[f].fa=p;
	upd(f),upd(p);
}
inline void Pushtag(int p){
	if(!rootcheck(p)) Pushtag(tree[p].fa);
	pushdown(p);
}
inline void splay(int p){
	Pushtag(p);
	while(!rootcheck(p)){
		int f=tree[p].fa;
		if(!rootcheck(f)) rotate(soncheck(p)==soncheck(f)?f:p);
		rotate(p);
	}
}
//Link-Cut-tree part
void access(int p){
	for(int x=0;p;p=tree[x=p].fa) splay(p),son(p,1)=x,upd(p);
}
void makeroot(int p){
	access(p),splay(p),tree[p].tag^=1;
}
int findroot(int p){
	access(p),splay(p);
	for(pushdown(p);son(p,0);pushdown(p=son(p,0)));
	return p;
}
void split(int x,int y){
	makeroot(x),access(y),splay(y);
}
void link(int x,int y){
	makeroot(x);
	if(findroot(y)!=x) tree[x].fa=y;
	upd(y);
}
void cut(int x,int y){
	makeroot(x);
	if(findroot(y)==x&&tree[x].fa==y&&!son(x,1)) tree[x].fa=son(y,0)=0,upd(y);
}
