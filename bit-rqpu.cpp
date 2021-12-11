const int mxN = 200000;
int bit[mxN + 5];
void upd(int i, int val) { // adds to, dummy
    i++;
    while(i < mxN + 5) {
        bit[i] += val;
        i += i & -i;
    }
}
int query(int i) { // PREFIX
    int ret = 0;
    i++;
    while(i > 0) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

int rquery(int l, int r) {
    return query(r)-query(l-1); // REVERSE
}