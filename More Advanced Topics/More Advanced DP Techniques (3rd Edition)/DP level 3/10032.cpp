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

const int N = 100+5;
const int MAX = 45000+5;

int n;
int v[N];
bool peso[MAX];
int L[MAX];
int R[MAX];

int main(){
	int t;
	ri(t);
	int S;
	while(t--){
		ri(n);
		S = 0;
		for(int i=0; i<n; i++){
			ri(v[i]);
			S += v[i];
		}
		for(int i=0; i<=S/2+5; i++){
			peso[i] = false;
			L[i] = INT_MAX;
			R[i] = 0;
		}
		peso[0] = true;
		L[0] = 0;
		for(int i=0; i<n; i++){
			
			for(int w = S/2+5; w>=0; w--){
				if(peso[w]){
					peso[w+v[i]] = true;
					L[w+v[i]] = min(L[w+v[i]],L[w]+1);
					R[w+v[i]] = max(R[w+v[i]],R[w]+1);
				}
			}
		}
		int g1,g2;
		for(int i=S/2; i>=0; i--){
			if(peso[i] and ((L[i] <= n/2 and n/2 <= R[i]) || (L[i] <= n/2+n%2 and n/2+n%2 <= R[i]))){
				g1 = i;
				break;
			}
		}
		g2 = S-g1;
		printf("%d %d\n",g1,g2);
		if(t) puts("");
	}
	return 0;
}
