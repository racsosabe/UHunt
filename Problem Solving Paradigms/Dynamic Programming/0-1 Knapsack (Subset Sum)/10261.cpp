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

const int CMAX = 10000+5;
const int N = 500+5;

int n;
int m;
bool vis[N][CMAX];
int parent[N][CMAX];
int memo[N][CMAX];
bool choice[N][CMAX];
int peso[N];

int DP(int pos, int used_in_C1, int used_in_C2){
	if(pos == n){
		return 0;
	}
	if(vis[pos][used_in_C1]) return memo[pos][used_in_C1];
	int c1 = m-used_in_C1;
	int c2 = m-used_in_C2;
	int ans = 0;
	if(c1 >= peso[pos]){
		if(ans < 1+DP(pos+1,used_in_C1+peso[pos],used_in_C2)){
			ans = 1+DP(pos+1,used_in_C1+peso[pos],used_in_C2);
			parent[pos][used_in_C1] = used_in_C1+peso[pos];
			choice[pos][used_in_C1] = 0;
		}
	}
	if(c2 >= peso[pos]){
		if(ans < 1+DP(pos+1,used_in_C1,used_in_C2+peso[pos])){
			ans = 1+DP(pos+1,used_in_C1,used_in_C2+peso[pos]);
			parent[pos][used_in_C1] = used_in_C1;
			choice[pos][used_in_C1] = 1;
		}
	}
	vis[pos][used_in_C1] = true;
	return memo[pos][used_in_C1] = ans;
}

int main(){
	int t;
	ri(t);
	int x;
	while(t--){
		n = 0;
		ri(m);
		m *= 100;
		while(ri(x)==1 and x!=0){
			peso[n++] = x;
		}
		memset(vis,0,sizeof vis);
		memset(choice,0,sizeof choice);
		int ans = DP(0,0,0);
		printf("%d\n",ans);
		int startC1 = 0;
		for(int i=0; i<ans; i++){
			int nextC = parent[i][startC1];
			if(choice[i][startC1]){
				puts("port");
			}
			else{
				puts("starboard");
			}
			startC1 = nextC;
		}
		if(t) puts("");
	}
	return 0;
}
