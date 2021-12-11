int N;
ll cap[201][201];
vi adj[201];
const ll INF=LONG_LONG_MAX;

ll bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, ll>> q;
    q.push({s, INF});

    while (!q.empty()) {
      int cur = q.front().first;
      ll flow = q.front().second;
      q.pop();
      for (int next : adj[cur]) {
        if (parent[next] == -1 && cap[cur][next]) {
          parent[next] = cur;
          ll new_flow = min(flow, cap[cur][next]);
          if (next == t)
            return new_flow;
          q.push({next, new_flow});
        }
      }
    }

    return 0;
}

vi maxflow(int s, int t) {
  ll flow = 0;
  vector<int> parent(N+1);
  ll new_flow;

  while (new_flow = bfs(s, t, parent)) {
    flow += new_flow;
    int cur = t;
    while (cur != s) {
      int prev = parent[cur];
      cap[prev][cur] -= new_flow;
      cap[cur][prev] += new_flow;
      cur = prev;
    }
  }

  vi paths;

  return flow;
}
