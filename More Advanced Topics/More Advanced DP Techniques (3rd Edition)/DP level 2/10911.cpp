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

const int N = 16+5;

int n;
int x[N], y[N];
double d[N][N];
double memo[(1<<16)+5];
bool vis[(1<<16)+5];
int p[(1<<17)+2];

double DP(int bitmask){
	if(bitmask+1 == int(1<<n)) return 0.0;
	if(vis[bitmask]) return memo[bitmask];
	int libres = bitmask ^ (int(1<<n) - 1);
	int m1 = p[libres&~(libres-1)];
	libres &= libres-1;
	double ans = DBL_MAX;
	while(libres > 0){
		int m2 = p[libres&~(libres-1)];
		ans = min(ans,d[m1][m2]+DP(bitmask|int(1<<m1)|int(1<<m2)));
		libres &= libres-1;
	}
	vis[bitmask] = true;
	return memo[bitmask] = ans;
}

int main(){
	string s;
	int caso = 1;
	for(int i=0; i<17; i++){
		p[1<<i] = i;
	}
	while(ri(n)==1 and n!=0){
		n *= 2;
		for(int i=0; i<n; i++){
			cin >> s;
			ri2(x[i],y[i]);
		}
		for(int i=0; i<n; i++){
			for(int j=i+1; j<n; j++){
				d[i][j] = d[j][i] = hypot(x[i]-x[j],y[i]-y[j]);
			}
		}
		printf("Case %d: ",caso++);
		for(int i=0; i<int(1<<n); i++) vis[i] = false;
		cout << setprecision(2) << fixed << DP(0) << endl;
	}
	return 0;
}
