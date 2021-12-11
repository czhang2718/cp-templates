const int MAXN=200000;
const int K=20;
ll st[MAXN][K + 1];
int lg[MAXN+1];

lg[1] = 0;
for (int i = 2; i <= MAXN; i++){
    lg[i] = lg[i/2] + 1;
}

for (int i=0; i<n; i++){
	st[i][0] = *ARRAY*[i];
}

for (int j=1; j<=K; j++){
    for (int i=0; i+(1<<j)<=n; i++){
        st[i][j]=min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    }
}

ll get_min(int l, int r){
	int j = lg[r-l+1];
	return(min(st[l][j], st[r-(1<<j)+1][j]));
}
