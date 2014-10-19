/*
 * Author:  DreamHigh
 * Created Time:  2014/10/19 10:57:42
 * File Name: A.cpp
 * solve: A.cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<map>
#include<stack>
#include<set>
#include<iostream>
#include<vector>
#include<queue>
//ios_base::sync_with_stdio(false);
//#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repf(i, a, b) for (int i = (a); i <= (b); ++i)
#define repd(i, a, b) for (int i = (a); i >= (b); --i)
#define clr(x) memset(x,0,sizeof(x))
#define sqr(x) ((x) * (x))
typedef long long LL;

const int INF = 1000000000;
const double eps = 1e-8;
const int maxn = 30000;
const int mod = 1000000000 + 7;
const int Node = 26;
const char base = 'a';
struct Trie{
    int num;
    bool terminal;
    struct Trie* son[Node];
};
Trie* NewTrie(){//
    Trie* temp = new Trie;
    temp->num = 1;
    temp->terminal = false;
    rep(i,0,Node) temp->son[i] = NULL;
    return temp;
}
void insert(Trie* pnt,char* s){
    Trie* temp = pnt;
    int len = strlen(s);
    rep(i,0,len){
        if(temp->son[s[i]-base] == NULL) temp->son[s[i]-base] = NewTrie();
        else temp->son[s[i]-base]->num++;
        temp = temp->son[s[i]-base];
    }
    temp->terminal = true;
}
int CalAns(Trie* pnt,char *s){
    Trie* temp = pnt;
    int len = strlen(s);
    rep(i,0,len){
        //if(temp->terminal == true) return temp->num;
        if(temp->son[s[i]-base] == NULL) return 0;
        temp = temp->son[s[i]-base];
    }
    return temp->num;
}
Trie* find(Trie* pnt,char* s)
{
    int len  = strlen(s);
    Trie* temp = pnt;
    for(int i = 0;i<len;++i)
    {
        if(temp->son[s[i]-base]!=NULL)
        temp = temp->son[s[i]-base];
        else
        return NULL;
    }
    return temp;
}
char ss[maxn];
int main() 
{
    //freopen("in.txt","r",stdin);
    int n;
    while(scanf("%d",&n) == 1){
        Trie* tt = NewTrie();
        rep(i,0,n){
            scanf("%s",ss);
            insert(tt,ss);
        }
        
        int q;
        scanf("%d",&q);
        while(q--){
            scanf("%s",ss);
            printf("%d\n",CalAns(tt,ss));
           /* int ans;
            if(find(tt,ss) == NULL) ans = 0;
            else ans = find(tt,ss)->num;
            printf("%d\n",ans);*/
        }
    }
    return 0;
}
