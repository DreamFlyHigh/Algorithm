/*
 * Author:  DreamHigh
 * Created Time:  2013/8/3 15:13:52
 * File Name: A.cpp(HDU 4614)
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
#define sz(v) ((int)(v).size())
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repf(i, a, b) for (int i = (a); i <= (b); ++i)
#define repd(i, a, b) for (int i = (a); i >= (b); --i)
#define clr(x) memset(x,0,sizeof(x))
#define clrs( x , y ) memset(x,y,sizeof(x))
#define out(x) printf(#x" %d\n", x)
#define sqr(x) ((x) * (x))
typedef long long LL;

const int INF = -1u>>1;
const double eps = 1e-8;
const int maxn = 50010;

int sgn(const double &x) {  return (x > eps) - (x < -eps); }
int sum[maxn<<2];
int setv[maxn<<2];
void push_up(int root){
    sum[root] = sum[root<<1] + sum[root<<1|1];
}
void push_down(int root ,int m){
    if(setv[root] >= 0){
        setv[root<<1] = setv[root];
        setv[root<<1|1] = setv[root];
        sum[root<<1] = setv[root]*(m-(m>>1));
        sum[root<<1|1] = setv[root]*(m>>1);
        setv[root] = -1;
    }
}
void build(int root,int L,int R){
     setv[root] = -1;
    sum[root] = 0;
    if(L==R) {
        return ;
    }
    int m = L+(R-L)/2;
    build(root<<1,L,m);
    build(root<<1|1,m+1,R);
    push_up(root);
}
void update(int l,int r,int v,int root,int L,int R){
    int m = L + (R-L)/2;
    if(l<=L&&r>=R) {
        setv[root] = v;
        sum[root] = v*(R-L+1);
        return ;
    }
    push_down(root,R-L+1);
    if(l<=m)
    update(l,r,v,root<<1,L,m);
    if(r>m)
    update(l,r,v,root<<1|1,m+1,R);
    push_up(root);
}
int query(int l,int r,int root,int L,int R){
    int _sum = 0;
    if(l<=L&&r>=R)
    return sum[root];
    int m = L+(R-L)/2;
    push_down(root,R-L+1);
    if(l<=m)
    _sum += query(l,r,root<<1,L,m);
    if(r>m)
    _sum += query(l,r,root<<1|1,m+1,R);
    return _sum;
}

int main() {
   //freopen("in.txt","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--){
        int n,m;
        scanf("%d%d",&n,&m);
        build(1,1,n);
        for(int i =  0;i<m;++i) {
            int cmd;
            scanf("%d",&cmd);
            int a,b;
            scanf("%d%d",&a,&b);
            a++;
            int sum = query(a,n,1,1,n);
            if(cmd == 1){
                if(sum == (n - a + 1)){
                    printf("Can not put any one.\n");
                }else {
                    int ans1,ans2;
                    int L,R;
                    L = a;
                    R = n;
                    int mid;
                    while(L < R){
                        mid = (L + R)/2;
                        if(mid - L + 1 - query(L,mid,1,1,n) >= 1){
                            R = mid;
                        }else if(mid - L + 1 - query(L,mid,1,1,n) == 0){
                            L = mid + 1;
                        }
                    }
                    ans1 = L;
                    L = a;
                    R = n;
                    if(n - a + 1 - query(a,n,1,1,n) >= b){
                    while(L < R){
                      mid = (L+R)/2;
                      if(mid - a + 1 - query(a,mid,1,1,n) >= b){
                          R = mid;
                      }else{
                          L = mid + 1;
                      }
                    }
                    ans2 = L;
                    }else{
                       while(L < R){
                           mid = (L+R)/2;
                           if(mid - a + 1 - query(a,mid,1,1,n) >= n - a + 1 - query(a,n,1,1,n)){
                               R = mid;
                           }else{
                               L = mid + 1;
                           }
                       }  
                       ans2 = L;
                    }
                    update(ans1,ans2,1,1,1,n);
                    ans1--;
                    ans2--;
                    printf("%d %d\n",ans1,ans2);
                }
            }
            if(cmd == 2){
                b++;
                sum = query(a,b,1,1,n);
                printf("%d\n",sum); 
                update(a,b,0,1,1,n);
            }
        }
        printf("\n");
    }
    return 0;
}

