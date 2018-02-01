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

const int N = 30+5;
const int M = 20+5;
const int T1 = 300+5;

int n, t1, t2;
int m[N];
ll C[N][M][3];
bool vis[N][T1];
ll memo[N][T1];
vi ans;
int choice[N][T1];

ll DP(int pos, int q){
	if(pos == n){
		if(q == 0) return 0;
		else return 1LL<<20;
	}
	if(vis[pos][q]) return memo[pos][q];
	ll ans = LLONG_MAX;
	for(int k=0; k<=m[pos] and k<=q; k++){
		ll act = C[pos][k][0] + C[pos][m[pos]-k][1] + DP(pos+1,q-k);
		if(act < ans){
			ans = act;
			choice[pos][q] = k;
		}
	}
	vis[pos][q] = true;
	return memo[pos][q] = ans;
}

int main(){
	while(ri2(t1,t2)==2 and t1+t2>0){
		ri(n);
		for(int i=0; i<n; i++){
			ri(m[i]);
			for(int j=0; j<2; j++){
				for(int k=1; k<=m[i]; k++){
					rll(C[i][k][j]);
				}
			}
		}
		memset(vis,0,sizeof vis);
		printf("%lld\n",DP(0,t1));
		ans.clear();
		int t = t1;
		for(int i=0; i<n; i++){
			ans.pb(choice[i][t]);
			t -= choice[i][t];
		}
		printf("%d",ans[0]);
		for(int i=1; i<n; i++) printf(" %d",ans[i]);
		puts("");
		puts("");
	}
	return 0;
}
