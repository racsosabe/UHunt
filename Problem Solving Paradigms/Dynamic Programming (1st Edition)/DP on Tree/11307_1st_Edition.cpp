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

const int N = 10000+5;
const int MAX = 7;

int n;
vi G[N];
string s;
char last;
int memo[N][MAX];
bool vis[N][MAX];
int padre[N];

int DP(int u, int last_color){
	if(G[u].size()==0){
		if(last_color ==1) return 2;
		return 1;
	}
	if(vis[u][last_color]) return memo[u][last_color];
	int ans = INT_MAX;
	for(int i=1; i<MAX; i++){
		if(i == last_color) continue;
		int act = i;
		for(int j=0; j<G[u].size(); j++){
			int v = G[u][j];
			act += DP(v,i);
		}
		ans = min(ans,act);
	}
	vis[u][last_color] = true;
	return memo[u][last_color] = ans;
}

int main(){
	int x;
	while(ri(n)==1 and n!=0){
		getchar();
		for(int i=0; i<n; i++){
			G[i].clear();
		}
		for(int i=0; i<n; i++) padre[i] = i;
		int leaf = 0;
		int indice;
		for(int i=0; i<n; i++){
			scanf("%d:",&indice);
			getline(cin,s);
			istringstream is(s);
			while(is >> x){
				G[indice].pb(x);
				padre[x] = indice;
			}
			if(G[indice].size()==0) leaf = indice;
		}
		while(leaf!=padre[leaf]){
			leaf = padre[leaf];
		}
		getchar();
		memset(vis,0,sizeof vis);
		printf("%d\n",DP(leaf,0));
	}
	return 0;
}
