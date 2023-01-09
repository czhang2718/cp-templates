#include "bits/stdc++.h"
using namespace std;

#define rep(i, a, b) for(int i=a; i<=b; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define f first
#define s second
#define nl '\n'
typedef long long ll;
// #define int ll
typedef vector<int> vi;
typedef pair<int, int> pii;
#define nl '\n'

struct wavelet{
    int n;
    vi X,Y;
    vector<vector<ll>> cnt,sum;
    vector<vector<pii>> vec;

    wavelet(){}

    void init(vector<vi> pts){
        n=sz(pts);
        cnt.resize(4*n);
        vec.resize(4*n);
        sum.resize(4*n);
        sort(all(pts));
        for(auto p:pts){
            X.pb(p[0]);
            Y.pb(p[1]);
        }
        sort(all(X));
        sort(all(Y)); Y.erase(unique(all(Y)), Y.end());  
        for(auto &p:pts){
            p[1]=lower_bound(all(Y), p[1])-Y.begin();
            vec[0].push_back({p[1],p[2]});
        }
        build(0, 0, sz(Y));
    }

    void build(int x, int ly, int ry){
        assert(sz(vec)>x);
        if(ly>=ry || vec[x].empty()) return;
        int my=(ly+ry)/2;
        int n=sz(vec[x]);
        cnt[x].resize(n);
        sum[x].resize(n);
        if(ry-ly==1){
            for(int i=0; i<n; i++){
                sum[x][i]=(i?sum[x][i-1]:0)+vec[x][i].s;
            }
            return;
        }
        for(int i=0; i<n; i++){
            cnt[x][i]=(i?cnt[x][i-1]:0)+(vec[x][i].f<my);
            sum[x][i]=(i?sum[x][i-1]:0)+vec[x][i].s;
            (vec[x][i].f<my?vec[2*x+1]:vec[2*x+2]).pb(vec[x][i]);
        }
        build(2*x+1, ly, my);
        build(2*x+2, my, ry);
    }

    ll qry(int x, int ly, int ry, int ylim, int rx){
        if(ylim<ly || rx<0 || ry<=ly || !sz(vec[x])) return 0;
        if(ylim>=ry-1) return sum[x][rx];
        int left_r=cnt[x][rx]-1;
        int right_r=rx+1-cnt[x][rx]-1;
        int my=(ly+ry)/2;
        // return 0;
        return qry(2*x+1, ly, my, ylim, left_r)+qry(2*x+2, my, ry, ylim, right_r);
    }

    ll qry(int x, int y){
        int rx=upper_bound(all(X), x)-X.begin()-1;
        int ylim=upper_bound(all(Y), y)-Y.begin()-1;
        if(rx<0 || ylim<0) return 0;
        return qry(0, 0, sz(Y), ylim, rx);
    }

    ll rect(int a, int b, int c, int d){
        return qry(c,d)-qry(c,b-1)-qry(a-1,d)+qry(a-1,b-1);
    }
};

int n,q;

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    vector<vi> pts(n, vi(3));
    rep(i,0,n-1){
        cin >> pts[i][0] >> pts[i][1] >> pts[i][2];
    }
    wavelet wt; 
    // im
    wt.init(pts);

    while(q--){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        cout << wt.rect(a,b,c-1,d-1) << nl;
    }
}
