#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i=a; i<=b; i++)

int l, r, m;
vector<int> mt;
vector<bool> used;
vector<int> adj[300];

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

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);


  cin >> l >> r >> m;
  mt.assign(r, -1);
  for(int i=1; i<=m; i++){
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
  }

  rep(i, 0, l-1){
    used.assign(l, false);
    try_kuhn(i);
  }

  vector<pair<int, int>> ans;
  rep(i, 0, r-1){
    if(mt[i]!=-1) ans.push_back({mt[i], i});
  }

  cout << (int) ans.size() << '\n';
  for(pair<int, int> p:ans){
    cout << p.first << " " << p.second << '\n';
  }
}