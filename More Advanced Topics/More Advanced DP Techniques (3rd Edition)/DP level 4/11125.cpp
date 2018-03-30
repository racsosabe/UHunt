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

const int T = 3000+5;

int n;
int p[10];
int mask[T];
ll ans[T];
vii queries;
bool vis[5][5][5][5][2][5000];
ll memo[5][5][5][5][2][5000];

ll DP(int row, int last, int color_first, int size_first, bool last_first, int mascara){
	if(mascara == 0){
		return (color_first!=last and row!=size_first) or last_first;
	}
	if(vis[row][last][color_first][size_first][last_first][mascara]) return memo[row][last][color_first][size_first][last_first][mascara];
	ll act = 0;
	for(int i=0; i<n; i++){
		int q = (mascara%p[i+1])/p[i];
		if(q > 0 and i!=last){
			for(int j=1; j<=3 and j<=q; j++){
				if(j!=row){
					act += DP(j,i,color_first,size_first,0,mascara-j*p[i]);
				}
			}
		}
	}
	vis[row][last][color_first][size_first][last_first][mascara] = true;
	return memo[row][last][color_first][size_first][last_first][mascara] = act;
}

int main(){
	int t;
	ri(t);
	int x;
	p[0] = 1;
	for(int i=1; i<10; i++){
		p[i] = 8*p[i-1];
	}
	for(int caso=0; caso<t; caso++){
		ri(n);
		for(int i=0; i<n; i++){
			ri(x);
			mask[caso] += p[i]*x;
		}
		queries.pb(mp(n,caso));
	}
	sort(all(queries));
	int last_n = queries[0].first;
	n = queries[0].first;
	for(int i=0; i<t; i++){
		if(last_n == queries[i].first){
			ll act = 0;
			x = mask[queries[i].second];
			if(x == 0){
				ans[queries[i].second] = 1;
				continue;
			}
			for(int k=0; k<n; k++){
				int q = (x%p[k+1])/p[k];
				if(q > 0){
					for(int j=1; j<=3 and j<=q; j++){
						act += DP(j,k,k,j,1,x-j*p[k]);
					}
				}
			}
			ans[queries[i].second] = act;
		}
		else{
			memset(vis,0,sizeof vis);
			n = queries[i].first;
			last_n = n;
			i--;
		}
	}
	for(int i=0; i<t; i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
