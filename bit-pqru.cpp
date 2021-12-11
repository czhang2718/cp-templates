const int mxN = 200000;
int bit[mxN + 5];

void upd(int i, int x) { // updates suffix
    for(++i; i<mxN; i+=i&-i){
        bit[i]+=x; //OP
    }
}

int query(int i) {
    int ret = 0;
    i++;
    while(i > 0) {
        ret += bit[i]; //OP
        i -= i & -i;
    }
    return ret;
}

void upd(int l, int r, int val){ // [l, r]
  upd(l, val);
  upd(r+1, -val); //INVERSE OP
}