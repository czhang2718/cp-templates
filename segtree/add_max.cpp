struct segtree{
  vector<ll> op, mx;
  int n;

  segtree(int n){
    this->n=n;
    op.resize(4*n);
    mx.resize(4*n);
  }

  void push(int x, int lx, int rx){
    if(rx-lx==1 || !op[x]) return;
    op[2*x+1]+=op[x];
    mx[2*x+1]+=op[x];
    op[2*x+2]+=op[x];
    mx[2*x+2]+=op[x];
    op[x]=0;
  }

  void add(int l, int r, ll v, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r){
      op[x]=v;
      mx[x]+=op[x];
      push(x, lx, rx);
      return;
    }
    if(lx>=r || rx<=l) return;
    int m=(lx+rx)/2;
    add(l, r, v, 2*x+1, lx, m);
    add(l, r, v, 2*x+2, m, rx);
    mx[x]=max(mx[2*x+1], mx[2*x+2]);
  }

  void add(int l, int r, ll v){
    if(r<=l) return;
    add(l, r, v, 0, 0, n);
  }

  void add(int i, ll v){ add(i, i+1, v); }

  ll get_max(int l, int r, int x, int lx, int rx){
    if(lx>=l && rx<=r) return mx[x];
    if(lx>=r || rx<=l) return -inf;
    push(x, lx, rx);
    int m=(lx+rx)/2;
    return max(get_max(l, r, 2*x+1, lx, m), get_max(l, r, 2*x+2, m, rx));
  }

  ll get_max(int l, int r){
    if(r<=l) return -inf;
    return get_max(l, r, 0, 0, n);
  }

  ll get(int i){ return get_max(i, i+1); }

  void set(int i, ll v){ add(i, -get(i)+v); }

  void set_max(int i, ll v){ 
    ll cur=get(i);
    if(v>cur) set(i, v);
  }

  void set_min(int i, ll v){ 
    ll cur=get(i);
    if(v<cur) set(i, v);
  }
};