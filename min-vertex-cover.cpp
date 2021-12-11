//minimum vertex cover with maximum matching on bipartite graph
// 1. get max matching
// 2. dfs from exposed nodes in set A; edges go A->B if not in matching, B->A otherwise
// 3. answer = non-visited nodes in A U visited nodes in B
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i=a; i<=b; i++)
#define trav(x, a) for(auto &x : a)
#define nl '\n'

int l, r, m;
vector<int> mt;
vector<bool> used;
vector<int> adj[300];
int matched[300];
vector<int> adj2[600];
vector<pair<char, int>> ans;
bool vis[600];
vector<pair<int, int>> edges;

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : adj[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

void dfs(int x){
  vis[x]=1;
  trav(k, adj2[x]){
    if(!vis[k]) dfs(k);
  }
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);


  cin >> l >> r >> m;
  mt.assign(r, -1);
  for(int i=1; i<=m; i++){
    int u, v; cin >> u >> v;
    edges.push_back({u, v});
    adj[u].push_back(v);
  }

  rep(i, 0, l-1){
    used.assign(l, false);
    try_kuhn(i);
  }

  int ans=0;
  for(auto e:edges){
    int u=e.first;
    int v=e.second;
    if(mt[v]==u){
      ans++;
      adj2[v+l].push_back(u);
      matched[u]=1;
    }
    else adj2[u].push_back(v+l);
  }

  for(int i=0; i<l; i++){
    if(!matched[i]) dfs(i);
  }

  cout << ans << nl;
  for(int i=0; i<l; i++){
    if(!vis[i]) cout << "L " << i << nl;
  }
  for(int i=0; i<r; i++){
    if(vis[l+i]) cout << "R " << i << nl;
  }
}