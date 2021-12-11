int n, m;
int q[300005];
int ans[300005];
vector<pii> st[1200020];
stack<pair<int, int>> s; //changes
int comp;
map<pii, int> mp;
int rnk[300001];
int par[300001];
 
int find(int x){
  if(par[x]==x) return x;
  return find(par[x]);
}
 
bool join(int x, int y){
  int a=find(x);
  int b=find(y);
  if(a==b) return false;
  comp--;
  if(rnk[a]<=rnk[b]){
    par[a]=b;
    if(rnk[a]==rnk[b]){
      rnk[b]++;
      s.push({a, b});
    }
    else s.push({a, 0});
  }
  else{
    par[b]=a;
    s.push({b, 0});
  }
  return true;
}
 
void upd(int x, int l, int r, int lx, int rx, pii e){
  if(l<=lx && r>=rx){
    st[x].pb(e); return;
  }
  if(lx>=r || rx<=l) return;
  int m=(lx+rx)/2;
  upd(2*x, l, r, lx, m, e);
  upd(2*x+1, l, r, m, rx, e);
}
 
void calc(int x, int lx, int rx){
  int cnt=0;
  trav(p, st[x]){
    if(join(p.f, p.s)) cnt++;
  }
  if(rx==lx+1){
    if(lx<=m) ans[q[lx]]=comp;
  }
  else{
    int m=(lx+rx)/2;
    calc(2*x, lx, m);
    calc(2*x+1, m, rx);
  }
  while(cnt--){
    pii p=s.top(); s.pop();
    par[p.f]=p.f;
    if(p.s) rnk[p.s]--;
    comp++;
  }
}
 
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  // freopen("input.txt", "r", stdin); 
  // freopen("output.txt", "w", stdout);
 
  upd(1, start_time, end_time, 0, M, {u, v});
  calc(1, 0, M);
}