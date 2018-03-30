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

const int N = 20;

int n;
int v[N][N];
int p[(1<<15)+2];
bool vis[N][(1<<15)+2];
ll memo[N][(1<<15)+2];

ll DP(int good, int bitmask){
	if(bitmask == 0){
		return good==n;
	}
	if(vis[good][bitmask]) return memo[good][bitmask];
	int pos = n-__builtin_popcount(bitmask);
	ll ans = 0;
	for(int j=bitmask; j>0; j&=j-1){
		int next = p[j&-j];
		if(good == n){
			ans += DP(n,bitmask^(1<<next));
		}
		else{
			if(v[pos][next] == 2) ans += DP(n,bitmask^(1<<next));
			else ans += DP(good+v[pos][next],bitmask^(1<<next));
		}
	}
	vis[good][bitmask] = true;
	return memo[good][bitmask] = ans;
}

int main(){
	int t;
	for(int i=0; i<=15; i++) p[1<<i] = i;
	ri(t);
	int caso = 1;
	while(t--){
		ri(n);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				ri(v[i][j]);
			}
		}
		for(int i=0; i<=n; i++){
			for(int j=0; j<(1<<n); j++){
				vis[i][j] = false;
			}
		}
		printf("Case %d: %lld\n",caso++,DP(0,(1<<n)-1));
	}
	return 0;
}
