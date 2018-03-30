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

const int N = 100000+5;

struct nodo{
	int val;
	int id;
};

int n,d;
nodo NIL;
nodo st[4*N];
char s[N];

nodo merge(nodo a, nodo b){
	return a.val < b.val?b:a;
}

void build(int pos=1, int l=0, int r=n-1){
	if(l == r){
		st[pos].val = s[l]-'0';
		st[pos].id = l;
		return;
	}
	int mi = (l+r)/2;
	build(2*pos,l,mi);
	build(2*pos+1,mi+1,r);
	st[pos] = merge(st[2*pos],st[2*pos+1]);
}

void update(int x, int y, int pos=1, int l=0, int r=n-1){
	if(l == r){
		st[pos].val = y;
		return;
	}
	int mi = (l+r)/2;
	if(l <= x and x <= mi) update(x,y,2*pos,l,mi);
	else update(x,y,2*pos+1,mi+1,r);
	st[pos] = merge(st[2*pos],st[2*pos+1]);
}

nodo queryn(int x, int y, int pos=1, int l=0, int r=n-1){
	if(y < l or r < x) return NIL;
	if(x <= l and r <= y) return st[pos];
	int mi = (l+r)/2;
	nodo L = queryn(x,y,2*pos,l,mi);
	nodo R = queryn(x,y,2*pos+1,mi+1,r);	
	return merge(L,R);
}

int main(){
	NIL.val = -1;
	while(ri2(n,d)==2 and n+d){
		scanf("%s",s);
		if(d==0){
			printf("%s\n",s);
			continue;
		}
		build();
		int last = 0;
		for(int i=d; i<n; i++){
			nodo act = queryn(last,i);
			putchar('0'+act.val);
			update(act.id,-1);
			last = act.id;
		}
		puts("");
	}
	return 0;
}
