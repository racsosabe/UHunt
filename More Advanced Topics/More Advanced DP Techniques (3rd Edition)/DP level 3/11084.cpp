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

const int R = 10000+5;
const int N = 10+5;

int n, d;
string s;
int p[N];
int f[N];
int q[11];
ll memo[(1<<10)+5][R];
bool vis[(1<<10)+5][R];

ll DP(int bitmask, int sum){
	if(bitmask+1 == int(1<<n)) return sum==0;
	if(vis[bitmask][sum]) return memo[bitmask][sum];
	ll ans = 0;
	int next_pos = 0;
	for(int i=0; i<n; i++){
		if((bitmask>>i)&1) next_pos += 1;
	}
	for(int i=0; i<n; i++){
		if((bitmask>>i)&1) continue;
		ans += DP(bitmask|1<<i,(sum+p[next_pos]*(s[i]-'0'))%d);
	}
	vis[bitmask][sum] = true;
	return memo[bitmask][sum] = ans;
}

int main(){
	int t;
	ri(t);
	f[0] = 1;
	for(int i=1; i<=10; i++) f[i] = i*f[i-1];
	while(t--){
		cin >> s >> d;
		n = s.size();
		p[0] = 1;
		for(int i=1; i<n; i++){
			p[i] = (p[i-1]*10)%d;
		}
		memset(vis,0,sizeof vis);
		ll ans = DP(0,0);
		memset(q,0,sizeof q);
		for(int i=0; i<n; i++){
			q[s[i]-'0'] += 1;
		}
		for(int i=0; i<10; i++){
			ans /= f[q[i]];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
