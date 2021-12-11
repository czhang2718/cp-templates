// Updated 9/5/2021
// Verified on https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/D

struct segtree{
  int no_op, n;
  vector<ll> sum;
  vector<ll> op;

  segtree(int n){
    this->n=n;
    no_op=0; // *CHECK*
    sum.resize(4*n);
    op.resize(4*n, no_op);
  }

  void push(int x, int lx, int rx){
    if(rx-lx==1 || op[x]==no_op) return;
    op[2*x+1]+=op[x];
    op[2*x+2]+=op[x];
    int m=(lx+rx)/2;
    sum[2*x+1]+=op[x]*(m-lx);
    sum[2*x+2]+=op[x]*(rx-m);
    op[x]=no_op;
  }

  void add(int l, int r, ll v, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r){
      op[x]+=v;
      sum[x]+=v*(rx-lx);
      push(x, lx, rx); return;
    }
    if(lx>=r || rx<=l) return;
    int m=(lx+rx)/2;
    add(l, r, v, 2*x+1, lx, m);
    add(l, r, v, 2*x+2, m, rx);
    sum[x]=sum[2*x+1]+sum[2*x+2];
  }

  void add(int l, int r, ll v){ // [l, r)
    if(r<=l) return;
    add(l, r, v, 0, 0, n+1);
  }

  ll get_sum(int l, int r, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r) return sum[x];
    if(lx>=r || rx<=l) return 0;
    int m=(lx+rx)/2;
    return get_sum(l, r, 2*x+1, lx, m)+get_sum(l, r, 2*x+2, m, rx);
  }

  ll get_sum(int l, int r){
    if(r<=l) return 0;
    return get_sum(l, r, 0, 0, n+1);
  }
};