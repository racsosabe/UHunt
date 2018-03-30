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

const int N = 1000+5;
const int M = 500+5;

int n, L, C;
int v[N];
ii memo[N][M];
bool vis[N][M];

ii DP(int pos, int left){
	if(pos == n){
		if(left == L){
			return mp(0,0);
		}
		else{
			int costo = 0;
			if(left >= 1 and left <= 10) costo = -C;
			else if(left > 10) costo = (left-10)*(left-10);
			return mp(1,costo);
		}
	}
	if(vis[pos][left]) return memo[pos][left];
	ii new_lecture = DP(pos+1,L-v[pos]);
	int costo = 0;
	if(left >= 1 and left <= 10) costo = -C;
	else if(left > 10) costo = (left-10)*(left-10);
	ii ans = mp(1+new_lecture.first,costo+new_lecture.second);
	if(left >= v[pos]){
		ans = min(ans,DP(pos+1,left-v[pos]));
	}
	vis[pos][left] = true;
	return memo[pos][left] = ans;
}

int main(){
	int caso = 1;
	while(ri(n)==1 and n!=0){
		if(caso > 1) puts("");
		ri2(L,C);
		for(int i=0; i<n; i++) ri(v[i]);
		memset(vis,0,sizeof vis);
		ii ans = DP(0,L);
		printf("Case %d:\nMinimum number of lectures: %d\nTotal dissatisfaction index: %d\n",caso++,ans.first,ans.second);
	}
	return 0;
}
