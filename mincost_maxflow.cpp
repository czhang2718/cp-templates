// copied from ?
// works for negative edges
template <class C, class F>
struct MCMF {
  static constexpr F eps = (F) 1e-9;
  struct Edge {
    int v, inv;
    F cap, flow;
    C cost;
    Edge(int v, C cost, F cap, int inv) : 
      v(v), cost(cost), cap(cap), flow(0), inv(inv){}
  };
 
  int s, t, n, m = 0;
  vector< vector<Edge> > g;
  vector<C> cost;
  vi state, path, from;
 
  MCMF(int n, int ss = -1, int tt = -1):
    n(n), g(n + 5), cost(n + 5), state(n + 5), 
    path(n + 5), from(n + 5) {
    s = ss == -1 ? n + 1 : ss;
    t = tt == -1 ? n + 2 : tt;
  }
 
  void add(int u, int v, F cap, C cost) {
    g[u].pb(Edge(v, cost, cap, sz(g[v])));
    g[v].pb(Edge(u, -cost, 0, sz(g[u]) - 1));
    m += 2;
  }
 
  bool bfs() {
    fill(all(state), 2);
    fill(all(cost), numeric_limits<C>::max());
    deque<int> qu;
    qu.push_back(s);
    state[s] = 1, cost[s] = 0;
    while (sz(qu)) {
      int u = qu.front(); qu.pop_front();
      state[u] = 0;
      for (Edge &e : g[u]) if (e.cap - e.flow > eps)
        if (cost[u] + e.cost < cost[e.v]) {
          cost[e.v] = cost[u] + e.cost;
          path[e.v] = u;
          from[e.v] = g[e.v][e.inv].inv;
          if (state[e.v] == 0 || (sz(qu) && cost[qu.front()] > cost[e.v]))
            qu.push_front(e.v);
          else if (state[e.v] == 2)
            qu.push_back(e.v);
          state[e.v] = 1;
        }
    }
    return cost[t] != numeric_limits<C>::max();
  }
 
  pair<C, F> minCostFlow() {
    C cost = 0; F flow = 0;
    while (bfs()) {
      F nflow = numeric_limits<F>::max();
      for (int u, v = t; v != s; v = u) {
        u = path[v];
        Edge &e = g[u][from[v]];
        nflow = min(nflow, e.cap - e.flow);
      }
      for (int u, v = t; v != s; v = u) {
        u = path[v];
        g[u][from[v]].flow += nflow;
        g[v][g[u][from[v]].inv].flow -= nflow;
        cost += g[u][from[v]].cost * nflow;
      }
      flow += nflow;
    }
    return make_pair(cost, flow);
  }
};


// MCMF<int, int> flow(n, s, t);
// flow.add(u, v, cap, cost);
// pii p=low.minCostFlow();