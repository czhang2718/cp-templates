// O(E*sqrt(V)) maximum matching given bipartite graph
// augmenting paths
// like kuhns but find as many k-length paths as possible each iteration
// can show each iteration k increases
// bfs to find min length augmenting path k
// try all endpoints of ap's with len k with dfs

#include "bits/stdc++.h"
using namespace std;
 
#define rep(i, a, b) for(int i=a; i<=b; i++)
#define trav(a, x) for(auto& a:x)
#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define f first
#define s second
#define nl "\n"
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int MOD=1e9+7;
template<class T> using pqg=priority_queue<T, vector<T>, greater<T>>;

const int N=50000;
int inf=1e9;
int n, m, e;
vi adj[2*N+1]; // A
int mt[2*N+1];
int dist[2*N+1];
bool vis[2*N+1];
vi B;

void bfs(){
	B.clear();
	queue<int> q;
	rep(i, 1, n+m) dist[i]=inf, vis[i]=0;
	rep(i, 1, n){
		if(mt[i]) continue;
		dist[i]=0;
		trav(k, adj[i]){
			dist[k]=1;
			q.push(k);
		}
	}

	while(!q.empty()){
		int x=q.front(); q.pop();
		if(!mt[x]){
			B.pb(x); break;
		}
		int a=mt[x];
		dist[a]=dist[x]+1;
		trav(k, adj[a]){
			if(dist[k]==inf){
				dist[k]=dist[x]+2;
				q.push(k);
			}
		}
	}

	while(!q.empty()){
		int x=q.front(); q.pop();
		if(!mt[x]) B.pb(x);
	}
}

bool dfs(int x){
	trav(a, adj[x]){
		if(dist[a]==dist[x]-1 && (!mt[a] || dfs(mt[a]))){
			mt[x]=a;
			mt[a]=x;
			dist[x]=dist[a]=inf;
			return 1;
		}
	}
	dist[x]=inf;
	return 0;
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  // freopen("input.txt", "r", stdin); 
  // freopen("output.txt", "w", stdout);

  cin >> n >> m >> e;
  rep(i, 1, e){
  	int u, v; cin >> u >> v;
  	adj[u].pb(n+v);
  	adj[n+v].pb(u);
  }
  int ans=0;
  while(true){
  	bfs();
  	if(B.empty()) break;
  	trav(u, B){
  		if(vis[u]) continue; //repeats when doing bfs and not removing duplicates from queue
  		vis[u]=1;
  		if(dfs(u)) ans++;
  	}
  }
  cout << ans;
}