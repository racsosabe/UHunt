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

int n,m;
vi G[N];
int q[N];
int in[N];
int subtree[N];
ll memo[N][N];
bool vis[N][N];
int abre[N];
int cierra[N];
vi nodos;
int T;
map<string,int> coord;

void DFS(int u){
	nodos.pb(u);
	abre[u] = T++;
	subtree[u] = 1;
	for(int j=0; j<G[u].size(); j++){
		int v = G[u][j];
		DFS(v);
		subtree[u] += subtree[v];
	}
	cierra[u] = T;
}

ll DP(int pos, int votes){
	if(votes >= m) return 0;
	if(pos >= nodos.size()) return (1<<20);
	if(vis[pos][votes]) return memo[pos][votes];
	ll ans = DP(pos+1,votes);
	ans = min(ans,q[nodos[pos]]+DP(cierra[nodos[pos]],votes+subtree[nodos[pos]]));
	vis[pos][votes] = true;
	return memo[pos][votes] = ans;
}

int to_i(string a){
	int len = a.size();
	int ans = 0;
	for(int i=0; i<len; i++){
		ans = 10*ans + a[i]-'0';
	}
	return ans;
}

int main(){
	string s;
	while(cin >> s and s!="#"){
		n = to_i(s);
		ri(m);
		coord.clear();
		int tam = 1;
		for(int i=0; i<=n; i++){
			q[i] = 0;
			subtree[i] = 0;
			G[i].clear();
			in[i] = 0;
		}
		for(int i=0; i<n; i++){
			cin >> s;
			if(coord[s]==0) coord[s] = tam++;
			int u = coord[s];
			ri(q[u]);
			getline(cin,s);
			istringstream is(s);
			while(is >> s){
				if(coord[s]==0) coord[s] = tam++;
				int v = coord[s];
				G[u].pb(v);
				in[v] += 1;
			}
		}
		for(int i=1; i<tam; i++){
			if(in[i]==0){
				G[0].pb(i);
				q[0] += q[i];
			}
		}
		T = 0;
		nodos.clear();
		DFS(0);
		memset(vis,0,sizeof vis);
		printf("%lld\n",DP(0,0));
	}
	return 0;
}
