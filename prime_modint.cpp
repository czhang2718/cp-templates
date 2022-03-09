#include "bits/stdc++.h"
using namespace std;
 
#define rep(i, a, b) for(int i=a; i<=b; i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define f first
#define s second
#define nl "\n"
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int MOD=1e9+7;

class  MMint     // MONTGOMERY FORM
{
  private:
    using u64  = uint64_t;
    using u128 = __uint128_t;

    static u64  mod;
    static u64  r;       // mod*r ≡ 1  MOD 2^64 ?
    static u64  n2;      // 2^128  MOD mod ?

    u64  x;

    static u64  reduce( const u128 &b )
  { return ( b + u128( u64( b ) * u64( -r ) ) * mod ) >> 64; }
    
  public:
    MMint() : x( 0 ) {}

    MMint( int64_t b ) : x( reduce( ( u128( b ) + mod ) * n2 ) ) {}

    static u64  get_r()  {
        u64  ret = mod;
        for( size_t i=0 ; i<5 ; ++i )  ret *= 2 - mod * ret;
        return  ret;
    }

    static u64  get_mod()  { return mod; }
    
    u64  get() const  {
        u64  ret = reduce( x );
        return  ret >= mod ? ret - mod : ret;
    }
    
    static void  set_mod( u64 m )  {
        assert( m < (1LL << 62) );
        assert( (m & 1) == 1 );
        mod = m;
        n2 = -u128( m ) % m;
        r = get_r();
        assert( r * mod == 1 );
    }

    MMint &operator += ( const MMint &p )  {
        if( (x += p.x) >= 2*mod )   x -= 2 * mod;
        return  *this;
    }
    MMint &operator -= ( const MMint &p )  {
        if( (x += 2*mod - p.x) >= 2*mod )   x -= 2*mod;
        return  *this;
    }
    MMint &operator *= ( const MMint &p )  {
        x = reduce( u128( x ) * p.x );
        return  *this;
    }
    MMint &operator /= ( const MMint &p )  {
        *this *= p.inverse();
        return  *this;
    }
    MMint &operator ++ ()  { return *this += MMint( 1 ); }
    MMint operator ++ ( int )  {
        MMint  tmp = *this;
        ++*this;
        return  tmp;
    }
    MMint &operator -- ()  { return *this -= MMint( 1 ); }
    MMint operator -- ( int )  {
        MMint  tmp = *this;
        --*this;
        return  tmp;
    }

    MMint operator + ( const MMint &p ) const { return MMint(*this) += p; };
    MMint operator - ( const MMint &p ) const { return MMint(*this) -= p; };
    MMint operator * ( const MMint &p ) const { return MMint(*this) *= p; };
    MMint operator / ( const MMint &p ) const { return MMint(*this) /= p; };

    bool operator == ( const MMint &p ) const
  { return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); };
    bool operator != ( const MMint &p ) const
  { return (x >= mod ? x - mod : x) != (p.x >= mod ? p.x - mod : p.x); };

  MMint  inverse()  const {
    u64  g = mod,  r = (*this).x,  x = 0,  y = 1;
    while( r != 0 )  {
      u64  q = g / r;
      g %= r;    swap( g, r );
      x -= q*y;  swap( x, y );
    }
    return  x < 0 ? x + mod : x;
  }

    MMint  pow( int64_t k ) const  {
        MMint  now = *this,  ret = 1;
        for( ; k > 0 ; k >>= 1, now *= now )  {
            if( k & 1 )  ret *= now;
        }
        return ret;
    }

    friend ostream &operator << ( ostream &os, const MMint &p )  { 
      return  os << p.get(); 
  }
    friend istream &operator >> ( istream &is, MMint &p )  {
        int64_t  a;
        is >> a;
        p = MMint( a );
        return  is;
    }
};


typename  MMint::u64  MMint::mod,  MMint::r,  MMint::n2;

int main(){
  cin.tie(0)->sync_with_stdio(0);

  MMint::set_mod(11);
  MMint a=19;
  cout << a;
  cout << MMint::get_mod();
}