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

const int N = 25;
const int W = 205;

int m;
int n;
char last;
vi v;
bool vis[N][W];
bool memo[N][W];

bool DP(int pos, int left){
	if(pos == n) return left==0;
	if(vis[pos][left]) return memo[pos][left];
	bool ans = false;
	if(left >= v[pos]) ans = ans || DP(pos+1,left-v[pos]);
	ans = ans || DP(pos+1,left);
	vis[pos][left] = true;
	return memo[pos][left] = ans;
}

int ReadInt(){
	int x = 0;
	char c = getchar();
	while(c != ' ' and c!='\n'){
		x = int(x<<3) + int(x<<1) + c-'0';
		c = getchar();
	}
	last = c;
	return x;
}

int main(){
	m = ReadInt();
	int x;
	while(m--){
		v.clear();
		memset(vis,0,sizeof vis);
		int S = 0;
		last = '.';
		while(last!='\n'){
			x = ReadInt();
			v.pb(x);
			S += x;
		}
		n = v.size();
		puts(DP(0,S/2) and S%2==0?"YES":"NO");
	}
	return 0;
}
