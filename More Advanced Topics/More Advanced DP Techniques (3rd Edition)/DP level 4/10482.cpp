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
const int M = 645;

int n;
int v[N];
int suma[N];
bool vis[N][M][M];
int memo[N][M][M];

int DP(int pos, int primero, int segundo){
	if(pos == n+1){
		int tercero = suma[pos-1] - primero - segundo;
		int maximo = max(primero,max(segundo,tercero));
		int minimo = min(primero,min(segundo,tercero));
		return maximo-minimo;
	}
	if(vis[pos][primero][segundo]) return memo[pos][primero][segundo];
	int ans = min(DP(pos+1,primero+v[pos],segundo),min(DP(pos+1,primero,segundo),DP(pos+1,primero,segundo+v[pos])));
	vis[pos][primero][segundo] = true;
	return memo[pos][primero][segundo] = ans;	
}

int main(){
	int t;
	ri(t);
	for(int caso=1; caso<=t; caso++){
		ri(n);
		for(int i=1; i<=n; i++){
			ri(v[i]);
			suma[i] = v[i] + suma[i-1];
		}
		memset(vis,0,sizeof vis);
		printf("Case %d: %d\n",caso,DP(1,0,0));
	}
	return 0;
}
