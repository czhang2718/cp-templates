#include "bits/stdc++.h"
using namespace std;


// https://judge.yosupo.jp/problem/rectangle_sum
// finds the sum of weighted (x,y) in a given rectangle
// 0<= x,y <= 10^9
struct wavelet{
    int n;
    vector<vector<int>> cnt;
    vector<vector<long long>> sum;
    vector<vector<pair<int,int>>> vec;
    vector<int> X, Y;

    wavelet(){
    }

    void init(vector<vector<int>> v){
        n=v.size();
        vec.resize(4*n);
        cnt.resize(4*n);
        sum.resize(4*n);
        for(auto p:v) X.push_back(p[0]), Y.push_back(p[1]);
        sort(X.begin(), X.end()); 
        sort(Y.begin(), Y.end());
        Y.erase(unique(Y.begin(), Y.end()), Y.end());
        sort(v.begin(), v.end());
        for(auto p:v){
            vec[0].push_back({lower_bound(Y.begin(), Y.end(), p[1])-Y.begin(), p[2]});
        }
        build(0, 0, Y.size());
    }

    void build(int x, int l, int r){
    	cnt[x].resize(vec[x].size());
        sum[x].resize(vec[x].size());
    	for(int i=0; i<vec[x].size(); i++) sum[x][i]=(i?sum[x][i-1]:0)+vec[x][i].second;
        if(r==l+1) return;
        int m=(l+r)/2;
        for(int i=0; i<vec[x].size(); i++){
            cnt[x][i]=(i?cnt[x][i-1]:0)+(vec[x][i].first<m);
            vec[2*x+1+(vec[x][i].first>=m)].push_back(vec[x][i]);
        }
        build(2*x+1, l, m);
        build(2*x+2, m, r);
    }

    long long query(int x, int l, int r, int li, int ri, int a, int b){ // ind [l,r] vals [a,b)
        if(l>=b || r<=a || ri<li) return 0;
        if(l>=a && r<=b) return sum[x][ri]-(li?sum[x][li-1]:0);
        
        int m=(l+r)/2;
        int left_li=cnt[x][li]-(vec[x][li].first<m);
        int left_ri=cnt[x][ri]-1;
        int right_li=li-cnt[x][li]+(vec[x][li].first<m);
        int right_ri=ri-cnt[x][ri];
        return query(2*x+1, l, m, left_li, left_ri, a, b) + query(2*x+2, m, r, right_li, right_ri, a, b);
    }

    long long rect(int a, int c, int b, int d){
        a=lower_bound(X.begin(), X.end(), a)-X.begin();
        b=upper_bound(X.begin(), X.end(), b)-X.begin()-1;
        c=lower_bound(Y.begin(), Y.end(), c)-Y.begin();
        d=upper_bound(Y.begin(), Y.end(), d)-Y.begin();
        return query(0, 0, Y.size(), a, b, c, d);
    }
};

int main(){
	cin.tie(0)->sync_with_stdio(0);

	wavelet tree;
	
	int n, q;
	cin >> n >> q;
	vector<vector<int>> vec(n, vector<int>(3));
	for(auto &v:vec) cin >> v[0] >> v[1] >> v[2]; // x y weight
	tree.init(vec);

	while(q--){
		int a,b,c,d; cin >> a >> b >> c >> d;
		cout << tree.rect(a,b,c-1,d-1) << "\n";
	}
}