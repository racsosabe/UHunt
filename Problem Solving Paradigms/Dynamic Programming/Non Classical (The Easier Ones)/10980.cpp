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

const int N = 200+5;

int n;
int q[N];
double v[N];
double memo[N];
bool vis[N];

double DP(int val){
	if(val == 0) return 0.0;
	if(vis[val]) return memo[val];
	double ans = DBL_MAX;
	for(int i=0; i<n; i++){
		if(val >= q[i])
		ans = min(ans,v[i]+DP(val-q[i]));
	}
	vis[val] = true;
	return memo[val] = ans;
}

int main(){
	int caso = 1;
	string s;
	int k;
	q[0] = 1;
	while(cin >> v[0]){
		ri(n);
		for(int i=1; i<=n; i++){
			ri(q[i]);
			cin >> v[i];
		}
		n+=1;
		memset(vis,0,sizeof vis);
		for(int i=200; i>=1; i--){
			double x = DP(i);
		}
		for(int i=200; i>=1; i--){
			
			for(int j=i+1; j<=200; j++){
				memo[i] = min(memo[i],memo[j]);
			}
		}
		getchar();
		getline(cin,s);
		printf("Case %d:\n",caso++);
		istringstream is(s);
		while(is >> k){
			printf("Buy %d for $%.2f\n",k,memo[k]);
		}
	}
	return 0;
}
