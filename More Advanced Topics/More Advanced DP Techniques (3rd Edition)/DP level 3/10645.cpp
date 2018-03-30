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

const int K = 21+5;
const int N = 50+5;
const int M = 100+5;

struct nodo{
	double benefit;
	int cost;
	nodo(){};
};

int n,m,k;
int c[N];
int v[N];
nodo ZERO;
nodo memo[K][N][M][K];
int choice[K][N][M][K];
bool vis[K][N][M][K];

bool menor(nodo a, nodo b){
	return a.benefit < b.benefit or a.benefit == b.benefit and a.cost > b.cost;
}

nodo DP(int pos, int last, int left, int times){
	if(pos == k) return ZERO;
	if(vis[pos][last][left][times]) return memo[pos][last][left][times];
	nodo ans;
	ans.cost = m+20;
	ans.benefit = 0.0;
	for(int i=0; i<n; i++){
		if(i != last){
			if(left >= c[i]){
				nodo candidate = DP(pos+1,i,left-c[i],1);
				if(candidate.cost+c[i] <= left){
					candidate.benefit += v[i];
					candidate.cost += c[i];
					if(menor(ans,candidate)){
						ans = candidate;
						choice[pos][last][left][times] = i;
					}
				}
			}
		}
		else{
			if(left >= c[i]){
				nodo candidate = DP(pos+1,i,left-c[i],times+1);
				if(times+1 == 2) candidate.benefit += v[i]/2.0;
				candidate.cost += c[i];
				if(candidate.cost <= left){
					if(menor(ans,candidate)){
						ans = candidate;
						choice[pos][last][left][times] = i;
					}
				}
			}
			
		}
	}
	vis[pos][last][left][times] = true;
	return memo[pos][last][left][times] = ans;
}

int main(){
	ZERO.benefit = 0;
	ZERO.cost = 0;
	while(ri3(k,n,m)==3 and k+n+m > 0){
		for(int i=0; i<n; i++){
			ri2(c[i],v[i]);
		}
		memset(vis,0,sizeof vis);
		nodo ans;
		ans.benefit = 0.0;
		ans.cost = m+20;
		int start = -1;
		for(int i=0; i<n; i++){
			if(m >= c[i]){
				nodo candidate = DP(1,i,m-c[i],1);
				if(candidate.cost <= m-c[i]){
					candidate.cost += c[i];
					candidate.benefit += v[i];
					if(menor(ans,candidate)){
						ans = candidate;
						start = i;
					}
				}
			}
		}
		cout << setprecision(1) << fixed << ans.benefit << endl;
		if(ans.cost <= m){
			printf("%d",start+1);
			int l = start;
			int left = m-c[start];
			int times = 1;
			for(int i=1; i<k; i++){
				int opcion = choice[i][l][left][times];
				printf(" %d",opcion+1);
				if(opcion == l){
					times += 1;
				}
				else{
					times = 1;
				}
				left -= c[opcion];
				l = opcion;
			}
			puts("");
		}
		else puts("");
	}
	return 0;
}
