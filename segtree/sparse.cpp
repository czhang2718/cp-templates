const int MX=7000000; // 4* log * N
int cnt;
int child[MX][2];
int on[MX], sum[MX];

void push(int x, int lx, int rx){
  if(!on[x]) return;
  if(!child[x][0]) child[x][0]=++cnt, child[x][1]=++cnt;
  on[child[x][0]]=on[child[x][1]]=1;
  int m=(lx+rx)/2;
  sum[child[x][0]]=m-lx;
  sum[child[x][1]]=rx-m;
}

void upd(int l, int r, int x, int lx, int rx){
  if(lx>=l && rx<=r){
    on[x]=1;
    sum[x]=rx-lx;
    return;
  }
  if(lx>=r || rx<=l) return;
  push(x, lx, rx);
  int m=(lx+rx)/2;
  if(!child[x][0]) child[x][0]=++cnt, child[x][1]=++cnt;
  upd(l, r, child[x][0], lx, m);
  upd(l, r, child[x][1], m, rx);
  sum[x]=sum[child[x][0]]+sum[child[x][1]];
}

void upd(int l, int r){
  upd(l, r, 0, 0, 1e9+1);
}

int calc(int l, int r, int x, int lx, int rx){
  if(lx>=l && rx<=r) return sum[x];
  if(lx>=r || rx<=l) return 0;
  push(x, lx, rx);
  int m=(lx+rx)/2;
  if(!child[x][0]) child[x][0]=++cnt, child[x][1]=++cnt;
  return calc(l, r, child[x][0], lx, m)+calc(l, r, child[x][1], m, rx);
}

int calc(int l, int r){
  return calc(l, r, 0, 0, 1e9+1);
}
