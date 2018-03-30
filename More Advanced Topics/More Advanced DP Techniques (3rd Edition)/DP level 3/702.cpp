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

const int N = 23;

int n, m;
bool memo[N][N][3];
bool vis[N][N][3];
ll memo2[N][N][3];
bool vis2[N][N][3];

bool DP(int menores, int mayores, bool menor){
	if(menores == 0 and mayores == 0){
		return true;
	}
	if(vis[menores][mayores][menor]) return memo[menores][mayores][menor];
	bool ans = false;
	if(menor){
		for(int i=1; i<=menores; i++){
			ans = ans || DP(i-1,mayores+menores-i,0);
		}
	}
	else{
		for(int i=1; i<=mayores; i++){
			ans = ans || DP(menores+i-1,mayores-i,1);
		}
	}
	vis[menores][mayores][menor] = true;
	return memo[menores][mayores][menor] = ans;
	
}

ll DP2(int menores, int mayores, bool menor){
	if(menores == 0 and mayores == 0) return 1;
	if(vis2[menores][mayores][menor]) return memo2[menores][mayores][menor];
	ll ans = 0LL;
	if(menor){
		for(int i=1; i<=menores; i++){
			ans += DP2(i-1,mayores+menores-i,0);
		}
	}
	else{
		for(int i=1; i<=mayores; i++){
			ans += DP2(menores+i-1,mayores-i,1);
		}
	}
	vis2[menores][mayores][menor] = true;
	return memo2[menores][mayores][menor] = ans;
}

int main(){
	while(ri2(n,m)==2){
		memset(vis,0,sizeof vis);
		memset(vis2,0,sizeof vis2);
		if(m > 1){
			printf("%lld\n",DP2(m-1,n-m,1));
		}
		else{
			ll ans = 1;
			int pos = 2;
			while(pos <= n and !DP(pos-2,n-pos,1)){
				pos += 1;
			}
			if(pos <= n) ans = DP2(pos-2,n-pos,1);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
