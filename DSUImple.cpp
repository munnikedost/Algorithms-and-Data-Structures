#pragma GCC optimize("O3")
#include <bits/stdc++.h>   
 
#define rep(i,a,n) for(int i=a;i<n;i++)
#define mod 1000000007
#define N 200005
#define se second
#define fi first
#define pie 3.14159265359
#define pll pair<ll,ll> 
#define pb push_back
#define sz(x) (int)x.size()
#define endl "\n"
 
#define debug2(x,y) cerr<<#x<<" :: "<<x<<"\t"<<#y<<" :: "<<y<<"\n";
#define debug3(x,y,z) cerr<<#x<<" :: "<<x<<"\t"<<#y<<" :: "<<y<<"\t"<<#z<<" :: "<<z<<"\n";
 
typedef long long ll;
using namespace std;
const int maxn = 10000;
int cnt[maxn];
bool big[maxn];
int col[maxn];
int sz[maxn];
vector<vector<int> > g(N);
void dsz(int cur,int par){
  sz[cur] += 1;
  for(auto e : g[cur]){
    if(e != par){
      dsz(e,cur);
      sz[cur] += sz[e];
    }
  }
}
void add(int v, int p, int x){
    cnt[ col[v] ] += x;
    for(auto u: g[v])
        if(u != p && !big[u])
            add(u, v, x);
}
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1), big[bigChild] = 1;  // bigChild marked as big and not cleared from cnt
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    cout << v << " " << keep << " " << sz[v] << "\n";
    rep(i,0,5){
      cout << cnt[i] << " "; 
    }
    cout << "\n";
    if(bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0)
        add(v, p, -1);
    cout << "Repeat\n";  
    rep(i,0,5){
      cout << cnt[i] << " "; 
    }
    cout << "\n";
}
void solve(){
  int n,m;
  cin >> n >> m;
  rep(i,1,n+1){
    cin >> col[i];
  }
  rep(i,0,m){
    int a,b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dsz(1,0);
  dfs(1,0,0); 
}

int main()
{
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  int tc=1;
  //cin>>tc;
  while(tc--)solve();
  return 0;
}
/*
6
5
0
1
2
0
1
2
1
2
2
3
1
4
4
5
4
6
*/