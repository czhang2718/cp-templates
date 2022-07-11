#include "bits/stdc++.h"
using namespace std;

const int N=8e5; // 4n
int n, q;
vector<int> A[N];
vector<int> cnt_left[N];
vector<int> ind_left[N], ind_right[N];
int mn[N], mx[N];
int ch[N][2];
int c;

// sparse wavelet
// you don't need sparse most of the times, coord compress

void build(int x){
  int n=A[x].size();
  if(!n) return;
  cnt_left[x].resize(n);
  ind_left[x].resize(n);
  ind_right[x].resize(n);
  mn[x]=1e9, mx[x]=0;
  for(int v:A[x]) mn[x]=min(mn[x], v), mx[x]=max(mx[x], v);
  if(mn[x]==mx[x]) return;
  int v=(mn[x]+mx[x])/2;
  ch[x][0]=++c;
  ch[x][1]=++c;
  for(int i=0; i<n; i++){
    if(i) cnt_left[x][i]=cnt_left[x][i-1];
    ind_left[x][i]=A[ch[x][0]].size();
    ind_right[x][i]=A[ch[x][1]].size();
    if(A[x][i]<=v) A[ch[x][0]].push_back(A[x][i]), cnt_left[x][i]++;
    else A[ch[x][1]].push_back(A[x][i]);
  }
  build(ch[x][0]);
  build(ch[x][1]);
}

int kth(int x, int l, int r, int k){
  if(l==r) return A[x][l];
  if(mn[x]==mx[x]) return A[x][0];
  int cnt_less=cnt_left[x][r]-(l?cnt_left[x][l-1]:0);
  if(cnt_less>k){
    return kth(ch[x][0], ind_left[x][l], ind_left[x][r]-(cnt_left[x][r]==cnt_left[x][r-1]), k);
  }
  else{
    return kth(ch[x][1], ind_right[x][l], ind_right[x][r]-(cnt_left[x][r]==cnt_left[x][r-1]+1), k-cnt_less);
  }
}

int main(){
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> q;
  A[0].resize(n);
  for(int i=0; i<n; i++){
    cin >> A[0][i];
  }
  build(0);

  while(q--){
    int l, r, k; cin >> l >> r >> k;
    cout << kth(0, l, r-1, k) << "\n";
  }
}

// a[i] >= ps[i-1]+2
// a[i]-ps[i-1]-2 >= 0
// a[i] >= a[1]+...+a[i-2] + 2

// https://ioi.te.lv/oi/pdf/v10_2016_19_37.pdf


