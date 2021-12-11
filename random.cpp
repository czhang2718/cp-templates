mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int l=1;
int r=10;
int x=uniform_int_distribution<int>(l, r)(rng);