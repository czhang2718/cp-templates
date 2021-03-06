struct segtree{
  int n, no_op;
  vector<ll> mn, op;

  segtree(int n){
    this->n=n;
    mn.resize(4*n, 1e18);
    no_op=-1; // *CHECK*
    op.resize(4*n,  no_op);
  }

  void push(int x, int lx, int rx){
    if(rx-lx==1 || op[x]==no_op) return;
    op[2*x+1]=op[2*x+2]=op[x];
    mn[2*x+1]=mn[2*x+2]=op[x];
    op[x]=no_op;
  }

  void assign(int l, int r, ll v, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r){
      op[x]=mn[x]=v;
      push(x, lx, rx); return;
    }
    if(lx>=r || rx<=l) return;
    int m=(lx+rx)/2;
    assign(l, r, v, 2*x+1, lx, m);
    assign(l, r, v, 2*x+2, m, rx);
    mn[x]=min(mn[2*x+1], mn[2*x+2]);
  }

  void assign(int l, int r, ll v){
    if(r<=l) return;
    assign(l, r, v, 0, 0, n);
  }

  void assign(int i, ll v){
    assign(i, i+1, v);
  }

  ll get_min(int l, int r, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r) return mn[x];
    if(lx>=r || rx<=l) return LONG_LONG_MAX;
    int m=(lx+rx)/2;
    return min(get_min(l, r, 2*x+1, lx, m), get_min(l, r, 2*x+2, m, rx));
  }

  ll get_min(int l, int r){
    if(r<=l) return 1e18; // *CHECK*
    return get_min(l, r, 0, 0, n);
  }

  ll get(int i){
    return get_min(i, i+1);
  }
};