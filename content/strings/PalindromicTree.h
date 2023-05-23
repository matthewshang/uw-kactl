/**
 * Author: Kaiyuan Liu
 * Date: 2016-12-15
 * License: CC0
 * Description: Palindromic Tree
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once
struct node{
	int ch[26],fail,len,num;
}trie[N]={(node){{0},1,0,0},(node){{0},0,-1,0}};
int n,length,last,cnt=1,s[N]={26};
char c[N];
int getfail(int p,int x){
	while(s[x-trie[p].len-1]!=s[x]) p=trie[p].fail;
	return p;
}
void insert(int x){
	int p=getfail(last,x);
	if(!trie[p].ch[s[x]]){
		trie[++cnt].len=trie[p].len+2;
		int tmp=getfail(trie[p].fail,x);
		trie[cnt].fail=trie[tmp].ch[s[x]];
		trie[cnt].num=trie[trie[cnt].fail].num+1;
		trie[p].ch[s[x]]=cnt;
	}
	last=trie[p].ch[s[n]];
}
