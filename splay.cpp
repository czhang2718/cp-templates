#include "bits/stdc++.h"
using namespace std;

const int N=1e5;
int ch[N][2];
int par[N];

void rotate(int x){
    if(!x) return;
    // x par[x]
    int y=par[x];
    ch[par[y]][y==ch[par[y]][1]]=x;
    par[x]=par[y];
    par[y]=x;
    if(x==ch[y][0]){
        ch[x][1]=y;
        ch[y][0]=ch[x][1];
        par[ch[x][1]]=y;
    } else{
        ch[x][0]=y;
        ch[y][1]=ch[x][0];
        par[ch[x][0]]=y;
    }
}

void access(int x){ // root = 0
    if(!x) return;
    if(!par[x]){
        rotate(x);
        return;
    }
    int d1=x==ch[par[x]][0];
    int d2=par[x]==ch[par[par[x]]][0];
    if(d1^d2) rotate(x), rotate(x);
    else rotate(par[x]), rotate(x);
    access(par[x]);
}

int main(){
    
}