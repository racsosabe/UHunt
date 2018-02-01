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

int n;
vii v;
int T;
bool memo[(1<<25)+5];
int vis[(1<<25)+5];

bool DP(int bitmask){
	if(bitmask+1 == int(1<<n)) return true;
	if(vis[bitmask]==T) return memo[bitmask];
	bool ans = false;
	int last_bm = 0;
	int last_char = -1;
	int last_q = 0;
	int bms[25+5];
	int characters[25+5];
	int q[25+5];
	int pos = 0;
	for(int i=0; i<n; i++){
		if((bitmask>>i)&1) continue;
		
		if(v[i].first!=last_char){
			if(last_char!=-1){
				bms[pos] = last_bm;
				characters[pos] = last_char;
				q[pos] = last_q;
				pos += 1;
			}
			last_q = v[i].second;
			last_bm = (1<<i);
		}
		else{
			last_bm |= (1<<i);
			last_q += v[i].second;
		}
		last_char = v[i].first;
	}
	bms[pos] = last_bm;
	characters[pos] = last_char;
	q[pos] = last_q;
	pos += 1;
	for(int i=0; i<pos; i++){
		if(q[i] > 1){
			ans = ans || DP(bitmask|bms[i]);
		}
	}
	vis[bitmask] = T;
	return memo[bitmask] = ans;
}

int main(){
	int t;
	ri(t);
	char last, c;
	int q;
	getchar();
	T = 1;
	while(t--){
		last = ' ';
		c = '.';
		q = 0;
		v.clear();
		while(c != '\n'){
			if(c!=last){
				if(q > 0) v.pb(mp(last-'a',q));
				if(c >='a' and c<='z') q = 1;
			}
			else q+=1;
			last = c;
			c = getchar();
		}
		v.pb(mp(last-'a',q));
		n = v.size();
		putchar(DP(0)+'0');
		putchar('\n');
		T += 1;
	}	
	return 0;
}
