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

const int N = 1000+5;

int n;
vi G[N];
int memo[N][3];
bool vis[N][3];

int DP(int u, int choice, int parent){
	if(parent!=0 and G[u].size()==1) return choice;
	if(vis[u][choice]) return memo[u][choice];
	int ans = 0;
	if(choice){
		ans += 1;
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			if(v!=parent){
				ans += min(DP(v,0,u),DP(v,1,u));
			}
		}
	}
	else{
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			if(v != parent) ans += DP(v,1,u);
		}
	}
	vis[u][choice] = true;
	return memo[u][choice] = ans;
}

int main(){
	int x,q;
	while(ri(n)==1 and n!=0){
		for(int i=1; i<=n; i++) G[i].clear();
		for(int i=1; i<=n; i++){
			ri(q);
			for(int j=0; j<q; j++){
				ri(x);
				G[i].pb(x);
			}
		}
		memset(vis,0,sizeof vis);
		if(n == 1) puts("1");
		else printf("%d\n",min(DP(1,0,0),DP(1,1,0)));
	}
	return 0;
}
