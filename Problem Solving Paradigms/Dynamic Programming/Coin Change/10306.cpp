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
}

int modInverso(int a, int m){
	int x, y;
	int g = gcdExtendido(a,m,&x,&y);
	if(g!=1) return -1;
	else return (x%m + m)%m;
}

/****************************************
*************P*L*A*N*T*I*L*L*A************
*****************************************/

const int N = 40+5;
const int M = 90000+5;

int n,S;
int a[N], b[N];
int memo[N][305][305];
bool vis[N][305][305];

int DP(int pos, int s1, int s2){
	if(pos == n){
		if(s1*s1 + s2*s2 == S) return 0;
		else return (1<<20);
	}
	if(vis[pos][s1][s2]) return memo[pos][s1][s2];
	int ans = (1<<20);
	int c1 = s1, c2 = s2;
	int k = 0;
	while(c1*c1+c2*c2 <= S){
		ans = min(ans,k+DP(pos+1,c1,c2));
		c1 += a[pos];
		c2 += b[pos];
		k+=1;
	}
	vis[pos][s1][s2] = true;
	return memo[pos][s1][s2] = ans;
}

int main(){
	int t;
	ri(t);
	while(t--){
		ri2(n,S);
		S *= S;
		for(int i=0; i<n; i++){
			ri2(a[i],b[i]);
		}
		memset(vis,0,sizeof vis);
		int ans = DP(0,0,0);
		if(ans >= (1<<20)){
			puts("not possible");
		}
		else printf("%d\n",ans);
	}	
	return 0;
}
