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

int n,l,m;
int v[N];
vector< vector< vector<int> > > memo;
vector< vector< vector<bool> > > vis;

int DP(int pos, int left_time, int left_disc){
	if(left_disc == 0 or pos == n) return 0;
	if(vis[pos][left_time][left_disc]) return memo[pos][left_time][left_disc];
	int ans = max(DP(pos+1,left_time,left_disc),DP(pos,l,left_disc-1));
	if(v[pos] <= left_time){
		ans = max(ans,1+DP(pos+1,left_time-v[pos],left_disc));
	}
	vis[pos][left_time][left_disc] = true;
	return memo[pos][left_time][left_disc] = ans;
}

int main(){
	int t;
	char c;
	ri(t);
	while(t--){
		ri3(n,l,m);
		ri(v[0]);
		for(int i=1; i<n; i++){
			scanf("%c%d",&c,&v[i]);
		}
		vis.resize(n+3);
		memo.resize(n+3);
		for(int i=0; i<n+3; i++){
			vis[i].resize(l+3);
			memo[i].resize(l+3);
			for(int j=0; j<l+3; j++){
				vis[i][j].assign(m+3,0);
				memo[i][j].resize(m+3);
			}
		}
		printf("%d\n",DP(0,l,m));
		if(t) puts("");
	}
	return 0;
}
