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

const int N = 200+5;

int n;
vi G[N];
ii memo[N][3];
bool vis[N][3];
map<string,int> nodo;

ii DP(int u, int tomo, int p){
	if(vis[u][tomo]) return memo[u][tomo];
	ii ans = mp(0,1);
	if(tomo){
		int suma = 1, times = 1;
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			if(v!=p){
				ii aporte = DP(v,0,u);
				suma += aporte.first;
				if(aporte.second > 1) times = 2;
			}
		}
		ans = mp(suma,times);
	}
	else{
		int suma = 0, times = 1;
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			if(v!=p){
				ii aporte1 = DP(v,0,u);
				ii aporte2 = DP(v,1,u);
				if(aporte1.first == aporte2.first){
					suma += aporte1.first;
					times = 2;
				}
				else{
					if(aporte1 < aporte2){
						suma += aporte2.first;
						if(aporte2.second>1) times = 2;
					}
					else{
						suma += aporte1.first;
						if(aporte1.second > 1) times = 2;
					}
				}
			}
		}
		ans = mp(suma,times);
	}
	vis[u][tomo] = true;
	return memo[u][tomo] = ans;
}

int main(){
	int pos;
	string a,b,s;
	while(ri(n)==1 and n){
		cin >> s;
		for(int i=1; i<=n; i++) G[i].clear();
		nodo.clear();
		nodo[s] = 1;
		pos = 2;
		for(int i=0; i<n-1; i++){
			cin >> a >> b;
			if(nodo[a]==0) nodo[a] = pos++;
			if(nodo[b]==0) nodo[b] = pos++;
			G[nodo[a]].pb(nodo[b]);
			G[nodo[b]].pb(nodo[a]);
		}
		memset(vis,0,sizeof vis);
		ii ans = DP(1,0,0);
		if(ans.first == DP(1,1,0).first){
			ans.second = 2;
		}
		else{
			ans = max(ans,DP(1,1,0));
		}
		if(ans.second > 1) printf("%d No\n",ans.first);
		else printf("%d Yes\n",ans.first);
	}
	return 0;
}
