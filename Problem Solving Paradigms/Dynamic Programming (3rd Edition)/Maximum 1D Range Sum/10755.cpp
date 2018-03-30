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

const int N = 22;

int a,b,c;
ll v[N][N][N];

int main(){
	int t;
	ri(t);
	while(t--){
		ri3(a,b,c);
		for(int i=0; i<a; i++){
			for(int j=0; j<b; j++){
				for(int k=0; k<c; k++){
					rll(v[i][j][k]);
				}
			}
		}
		for(int i=0; i<a; i++){
			for(int j=0; j<b; j++){
				for(int k=0; k<c; k++){
					if(i > 0) v[i][j][k] += v[i-1][j][k];
					if(j > 0) v[i][j][k] += v[i][j-1][k];
					if(k > 0) v[i][j][k] += v[i][j][k-1];
					if(i > 0 and j > 0) v[i][j][k] -= v[i-1][j-1][k];
					if(i > 0 and k > 0) v[i][j][k] -= v[i-1][j][k-1];
					if(j > 0 and k > 0) v[i][j][k] -= v[i][j-1][k-1];
					if(i > 0 and j > 0 and k > 0) v[i][j][k] += v[i-1][j-1][k-1];
				}
			}
		}
		ll ans = v[0][0][0];
		for(int f1 = 0; f1 < a; f1++){
			for(int f2=f1; f2<a; f2++){
				for(int c1=0; c1<b; c1++){
					for(int c2=c1; c2<b; c2++){
						for(int h1=0; h1<c; h1++){
							for(int h2=h1; h2<c; h2++){
								ll sum = v[f2][c2][h2];
								if(f1 > 0) sum -= v[f1-1][c2][h2];
								if(c1 > 0) sum -= v[f2][c1-1][h2];
								if(h1 > 0) sum -= v[f2][c2][h1-1];
								if(f1 > 0 and c1 > 0) sum += v[f1-1][c1-1][h2];
								if(f1 > 0 and h1 > 0) sum += v[f1-1][c2][h1-1];
								if(c1 > 0 and h1 > 0) sum += v[f2][c1-1][h1-1];
								if(f1 > 0 and c1 > 0 and h1 > 0) sum -= v[f1-1][c1-1][h1-1];
								ans = max(ans,sum);
							}
						}
					}
				}
			}
		}
		printf("%lld\n",ans);
		if(t > 0) puts("");
	}
	return 0;
}
