/**
 * Author: Kaiyuan Liu
 * Date: 2017-05-15
 * Source:
 * Description: Suffix Auto Maton
 * Time: $O(26N)$
 * Status: stress-tested a bit
 */
#pragma once
struct node{
	int ch[26],len,fa,size;
}sam[N*4];
int las=1,tot=1,n;
long long ans;
void insertchar(int c){
	if(sam[las].ch[c]&&sam[las].len+1==sam[sam[las].ch[c]].len) //1
	return (void)(las=sam[las].ch[c]);
	int p=las,np=las=++tot; sam[np].size=1;
	sam[np].len=sam[p].len+1;
	for(;p&&!sam[p].ch[c];p=sam[p].fa) sam[p].ch[c]=np;
	if(!p) sam[np].fa=1; else{
		int q=sam[p].ch[c];
		if(sam[q].len==sam[p].len+1) sam[np].fa=q;
		else{
			int nq=++tot;
			if(sam[p].len+1==sam[np].len) las=nq; //2
			sam[nq]=sam[q],sam[nq].len=sam[p].len+1;
			sam[q].fa=sam[np].fa=nq; sam[nq].size=0;
			for(;p&&sam[p].ch[c]==q;p=sam[p].fa) sam[p].ch[c]=nq;
		}
	}
}
queue<int>que; int pos[N]={0,1};
void buildsam(){
	que.push(1);
	while(!que.empty()){
		int p=que.front(); que.pop();
		rep(i,0,25) if(trie[p].ch[i]){
			las=pos[p];
			que.push(trie[p].ch[i]);
			insertchar(i);
			pos[trie[p].ch[i]]=las;
		}
	}
}