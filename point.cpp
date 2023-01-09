typedef long long ll;

struct P{
    int x,y;

    explicit P(int x=0, int y=0): x(x), y(y) {}

    P operator -(const P b){
        return P(x-b.x, y-b.y);
    }

    ll operator *(const P b){
        return x*b.y-y*b.x;
    }
};