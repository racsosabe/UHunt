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

const int K = 200+5;
const int N = 11+5;

int n,x,t,k;
int p[K];
int w[K];
int memo[K][105*N][2*N];
bool vis[K][105*N][2*N];

int DP(int pos, int money, int left){
	if(pos == 2*k) return 0;
	if(vis[pos][money][left]) return memo[pos][money][left];
	int ans = DP(pos+1,money,left);
	if(money >= p[pos] and left > 0){
		ans = max(ans,w[pos]+DP(pos+1,money-p[pos],left-1));
	}
	vis[pos][money][left] = true;
	return memo[pos][money][left] = ans;
}

bool can(int val){
	int q = val+(n+1)*t + (val+(n+1)*t+9)/10;
	return q <= (n+1)*x;
}

int main(){
	int m;
	while(ri2(n,x)==2){
		ri2(t,k);
		if(n == 0) break;
		for(int i=0; i<k; i++){
			ri(p[i]);
			p[i+k] = p[i];
			w[i] = w[i+k] = 0;
			for(int j=0; j<n+1; j++){
				ri(m);
				w[i] += m;
				w[i+k] += m;
			}
		}
		memset(vis,0,sizeof vis);
		int lo = 0, hi = (n+1)*x;
		while(lo < hi){
			int mi = lo + (hi-lo+1)/2;
			if(can(mi)) lo = mi;
			else hi = mi-1;
		}
		int ans = DP(0,lo,2*(n+1));
		cout << setprecision(2) << fixed << 1.0*ans/(n+1) << endl;
	}
	return 0;
}
