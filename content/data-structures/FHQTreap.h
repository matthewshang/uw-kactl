/**
 * Author: Kaiyuan
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: FHQ Treap with merge(join)
 * Time: $O(nlogn)$
 * Status: stress-tested
 */
#pragma once
int newnode(int x){
	treap[++cnt]=(node){{0,0},x,1ll*rand()*rand()*rand()*rand()%19260817,1};
	return cnt;
}
void upd(int p){
	treap[p].size=treap[son(p,0)].size+treap[son(p,1)].size+1;
}
int merge(int &p,int x,int y){
	if(x==0||y==0) return p=x+y;
	if(treap[x].key<treap[y].key) merge(son(p,1),son(p=x,1),y);
	else merge(son(p,0),x,son(p=y,0));
	return upd(p),p;
}
int split(int p,int k,int &x,int &y){
	if(!p) return x=y=0;
	if(treap[son(p,0)].size>=k) split(son(p,0),k,x,son(y=p,0));
	else split(son(p,1),k-treap[son(p,0)].size-1,son(x=p,1),y);
	return upd(p),0;
}
int Split(int p,int k,int &x,int &y){
	if(!p) return x=y=0;
	if(treap[p].val<k) Split(son(p,0),k,x,son(y=p,0));
	else Split(son(p,1),k,son(x=p,1),y);
	return upd(p),0;
}
int join(int &p,int x,int y){
	if(!x||!y) return p=x+y;
	if(treap[x].key>treap[y].key) swap(x,y);
	int r1,r2; Split(y,treap[x].val,r1,r2);
	join(son(x,0),son(x,0),r1); join(son(x,1),son(x,1),r2); p=x;
	return upd(p),p;
}