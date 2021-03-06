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

int c;
int v[4];
int OriginalMoney;
bool vis[151][101][51];
int memo[151][101][51];

int DP(int pos, int fives, int tens){
	if(pos == c) return 0;
	if(vis[pos][fives][tens]) return memo[pos][fives][tens];
	int ans = INT_MAX;
	int ones = OriginalMoney - 8*pos - 5*fives - 10*tens;
	if(tens){
		ans = min(ans,1+DP(pos+1,fives,tens-1));
	}
	if(fives >= 2){
		ans = min(ans,2+DP(pos+1,fives-2,tens));
	}
	if(fives and ones>=3){
		ans = min(ans,4+DP(pos+1,fives-1,tens));
	}
	if(tens and ones>=3){
		ans = min(ans,4+DP(pos+1,fives+1,tens-1));
	}
	if(ones >= 8){
		ans = min(ans,8+DP(pos+1,fives,tens));
	}
	vis[pos][fives][tens] = true;
	return memo[pos][fives][tens] = ans;
}

int main(){
	int t;
	ri(t);
	while(t--){
		ri(c);
		ri3(v[0],v[1],v[2]);
		OriginalMoney = v[0] + 5*v[1] + 10*v[2];
		memset(vis,0,sizeof vis);
		printf("%d\n",DP(0,v[1],v[2]));
	}
	return 0;
}
