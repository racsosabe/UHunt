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

const int N = 2000+5;
const int H = 2000+5;

int n, h, f;
int acorns[N][H];
int memo[N][H];
int st[H][4*N];

void build(int altura, int pos=1, int l=0, int r=n-1){
	if(l == r){
		st[altura][pos] = 0;
		return;
	}
	int mi = (l+r)/2;
	build(altura,2*pos,l,mi);
	build(altura,2*pos+1,mi+1,r);
	st[altura][pos] = max(st[altura][2*pos],st[altura][2*pos+1]);
}

int query(int x, int y, int altura, int pos=1, int l=0, int r=n-1){
	if(y < l or r < x or y < x) return -1;
	if(x <= l and r <= y) return st[altura][pos];
	int mi = (l+r)/2;
	int L = query(x,y,altura,2*pos,l,mi);
	int R = query(x,y,altura,2*pos+1,mi+1,r);
	return max(L,R);
}

void update(int x, int y, int altura, int pos=1, int l=0, int r=n-1){
	if(l == r){
		st[altura][pos] = y;
		return;
	}
	int mi = (l+r)/2;
	if(l <= x and x <= mi) update(x,y,altura,2*pos,l,mi);
	else update(x,y,altura,2*pos+1,mi+1,r);
	st[altura][pos] = max(st[altura][2*pos],st[altura][2*pos+1]);
}

int main(){
	int t;
	int q;
	int x;
	ri(t);
	while(t--){
		ri3(n,h,f);
		for(int i=0; i<n; i++){
			for(int j=0; j<=h; j++) acorns[i][j] = 0;
			ri(q);
			while(q--){
				ri(x);
				acorns[i][x] += 1;
			}
		}
		for(int i=0; i<n; i++) build(i);
		for(int i=0; i<n; i++){
			memo[0][i] = 0;
		}

		for(int altura = 1; altura <= h; altura++){
			for(int pos=0; pos<n; pos++){
				if(altura >= f){
					memo[pos][altura] = acorns[pos][altura]+memo[pos][altura-1];
					memo[pos][altura] = max(memo[pos][altura],acorns[pos][altura]+query(0,pos-1,altura-f));
					memo[pos][altura] = max(memo[pos][altura],acorns[pos][altura]+query(pos+1,n-1,altura-f));
					update(pos,memo[pos][altura],altura);
				}
				else{
					memo[pos][altura] = acorns[pos][altura] +memo[pos][altura-1];
					update(pos,memo[pos][altura],altura);
				}
				
			}
		}
		printf("%d\n",query(0,n,h));
	}
	return 0;
}
