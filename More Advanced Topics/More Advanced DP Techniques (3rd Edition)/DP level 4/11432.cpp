#include<bits/stdc++.h>
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ri(x) scanf("%d",&(x))
#define ri2(x,y) scanf("%d %d",&(x),&(y))
#define ri3(x,y,z) scanf("%d %d %d",&(x),&(y),&(z))
#define rll(x) scanf("%lld",&(x))
#define rll2(x,y) scanf("%lld %lld",&(x),&(y))
#define rll3(x,y,z) scanf("%lld %lld %lld",&(x),&(y),&(z))
#define rc(x) scanf("%c",&(x))
using namespace::std;

const long double PI = acos(-1);
const int MOD = 1000000000 +7;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> tll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<tll> vtll;
typedef vector<string> vs;
typedef set<int> si;
typedef set<ii> sii;
typedef set<iii> siii;

ll gcd(ll a, ll b){ return b==0?a:gcd(b,a%b);}

int add(ll a, ll b){ return (a%MOD + b%MOD+2*MOD)%MOD;}

int mul(ll a, ll b){ return ((a%MOD+MOD)*(b%MOD+MOD))%MOD;}

ll pow_mod(ll a, ll b){
	ll res = 1LL;
	a = add(a,0);
	while(b){
		if(b&1) res = mul(res,a);
		b >>= 1;
		a = mul(a,a);
	}
	return res;
}

ll fastexp(ll a, ll b){
	ll res = 1LL;
	while(b){
		if(b&1) res = res*a;
		b >>= 1;
		a *= a;
	}
	return res;
}

int gcdExtendido(int a, int b, int *x, int *y){
	if(a == 0){
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtendido(b%a,a,&x1,&y1);
	
	*x = y1-(b/a)*x1;
	*y = x1;
	return gcd;
};

int modInverso(int a, int m){
	int x, y;
	int g = gcdExtendido(a,m,&x,&y);
	if(g!=1) return -1;
	else return (x%m + m)%m;
}

/****************************************
*************P*L*A*N*T*I*L*L*A************
*****************************************/

const int N = 35;

int d, g;
bool vis[2*N][N][N][3];
ll memo[2*N][N][N][3];
// Asumir que se empieza con el trabajo 1, pues la cantidad para empezar con 1
// o 2 es la misma

ll DP(int pos, int streak, int fworked, int work){
	if(pos == 2*d) return 1LL;
	int sworked = pos-fworked;
	if(sworked == d) return 0LL;
	if(fworked == d){
		return 1LL;
	}
	if(vis[pos][streak][fworked][work]) return memo[pos][streak][fworked][work];
	ll ans = 0LL;
	if(streak+1 <= g) ans += DP(pos+1,streak+1,fworked+(work==1),work);
	ans += DP(pos+1,1,fworked+(work==2),3-work);
	vis[pos][streak][fworked][work] = true;
	return memo[pos][streak][fworked][work] = ans;
	
}

int main(){
	int caso = 1;
	while(ri2(d,g)==2 and d+g>=0){
		memset(vis,0,sizeof vis);
		if(g == 0) printf("Case %d: 0\n",caso++);
		else printf("Case %d: %lld\n",caso++,2LL*DP(1,1,1,1));
	}
	return 0;
}
