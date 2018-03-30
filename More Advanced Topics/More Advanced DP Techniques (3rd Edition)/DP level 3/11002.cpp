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

const int N = 900+5;
const int MAX = 6020;

int n;
int a[N];
int nodo[60][30];
vi G[N];
bitset<MAX> memo[N];

int main(){
	while(ri(n)==1 and n){
		int nodos = 0;
		for(int i=0; i<n*n; i++) G[i].clear();
		for(int i=0; i<n; i++){
			for(int j=0; j<=i; j++){
				ri(a[nodos]);
				nodo[i][j] = nodos++;
				if(i-1>=0 and j-1>=0){
					G[nodo[i][j]].pb(nodo[i-1][j-1]);
				}
				if(i-1>=0 and j>=0 and j<=i-1){
					G[nodo[i][j]].pb(nodo[i-1][j]);
				}
			}
		}
		for(int i=n; i<2*n-1; i++){
			for(int j=0; j<2*n-1-i; j++){
				ri(a[nodos]);
				nodo[i][j] = nodos++;
				G[nodo[i][j]].pb(nodo[i-1][j]);
				G[nodo[i][j]].pb(nodo[i-1][j+1]);
			}
		}
		memo[0].reset();
		memo[0][3010-a[0]] = memo[0][3010+a[0]] = 1;
		for(int i=1; i<n*n; i++){
			memo[i].reset();
			for(int j=0; j<G[i].size(); j++){
				int v = G[i][j];
				for(int k=0; k<MAX; k++){
					if(memo[v][k]){
						memo[i][k+a[i]] = 1;
						if(i!=n*n-1)
						memo[i][k-a[i]] = 1;
					}
				}
			}
		}
		int ans = INT_MAX;
		for(int k = 3010; k<MAX; k++){
			if(memo[n*n-1][k]){
				ans = min(ans,abs(k-3010));
				break;
			}
		}
		for(int k=3010; k>=0; k--){
			if(memo[n*n-1][k]){
				ans = min(ans,abs(k-3010));
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
