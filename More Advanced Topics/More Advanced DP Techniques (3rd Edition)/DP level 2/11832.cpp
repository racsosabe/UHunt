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

const int N = 40+5;
const int MAX = 16000;

int n, m;
int v[N];
char op[] = {'?','+','-','?'};
int choice[N];
bool memo[N][2*MAX+5];
bool vis[N][2*MAX+5];

bool DP(int pos, int sum){
	if(pos == n){
		return sum-MAX == m;
	}
	if(vis[pos][sum]) return memo[pos][sum];
	int act_sum = sum - MAX;
	bool suma = DP(pos+1,act_sum+v[pos]+MAX);
	bool resta = DP(pos+1,act_sum-v[pos]+MAX);
	if(suma) choice[pos] |= 1;
	if(resta) choice[pos] |= 2;
	vis[pos][sum] = true;
	return memo[pos][sum] = suma || resta;
}

int main(){
	while(ri2(n,m)==2 and n > 0){
		for(int i=0; i<n; i++) ri(v[i]);
		memset(vis,0,sizeof vis);
		for(int i=0; i<n; i++) choice[i] = 0;
		if(DP(0,MAX)){
			for(int i=0; i<n; i++) putchar(op[choice[i]]);
			putchar('\n');
		}
		else puts("*");
	}
	return 0;
}
