// Updated 8/14/2021
// Verified on https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A


struct segtree{
  vector<ll> op, mn;
  int n;

  segtree(int n){
    this->n=n;
    op.resize(4*n);
    mn.resize(4*n);
  }

  void push(int x, int lx, int rx){
    if(rx-lx==1 || !op[x]) return;
    op[2*x+1]+=op[x];
    mn[2*x+1]+=op[x];
    op[2*x+2]+=op[x];
    mn[2*x+2]+=op[x];
    op[x]=0;
  }

  void add(int l, int r, int v, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r){
      op[x]=v;
      mn[x]+=op[x];
      push(x, lx, rx);
      return;
    }
    if(lx>=r || rx<=l) return;
    int m=(lx+rx)/2;
    add(l, r, v, 2*x+1, lx, m);
    add(l, r, v, 2*x+2, m, rx);
    mn[x]=min(mn[2*x+1], mn[2*x+2]);
  }

  void add(int l, int r, int v){
    if(r<=l) return;
    add(l, r, v, 0, 0, n);
  }

  void add(int i, int v){
    add(i, i+1, v);
  }

  ll get_min(int l, int r, int x, int lx, int rx){
    if(lx>=l && rx<=r) return mn[x];
    if(lx>=r || rx<=l) return LONG_LONG_MAX;
    push(x, lx, rx);
    int m=(lx+rx)/2;
    return min(get_min(l, r, 2*x+1, lx, m), get_min(l, r, 2*x+2, m, rx));
  }

  ll get_min(int l, int r){
    if(r<=l) return 1e18; // CHCK
    return get_min(l, r, 0, 0, n);
  }
};

