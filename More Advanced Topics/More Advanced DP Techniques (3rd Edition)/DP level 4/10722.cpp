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
const int B = 130;

class BigInteger{
	vi a;
	int len;
	public:
	BigInteger(){
		len = 0;
		a.clear();
	}
	void use(int x){
		a.clear();
		if(x == 0){
			len = 1;
			a.pb(0);
			return;
		}
		while(x){
			a.pb(x%10);
			len++;
			x /= 10;
		}
	}

	void sumar(BigInteger b){
		int act_len = min(len,b.len);
		vi carry(max(len,b.len));
		for(int i=0; i<act_len; i++){
			carry[i] += a[i];
			carry[i] += b.a[i];
		}
		for(int i=act_len; i<len; i++){
			carry[i] += a[i];
		}
		for(int i=act_len; i<b.len; i++){
			carry[i] += b.a[i];
		}
		for(int i=0; i<carry.size(); i++){
			if(carry[i] > 9){
				if(i == carry.size()-1){
					carry.pb(carry[i]/10);
					carry[i] %= 10;
				}
				else{
					carry[i+1] += carry[i]/10;
					carry[i] %= 10;
				}
			}
		}
		while(carry.back()==0) carry.ppb();
		a = carry;
		len = carry.size();
	}

	void Print(){
		for(int i=len-1; i>=0; i--){
			putchar('0'+a[i]);
		}
		puts("");
	}
	
};

int n,b;
vector<BigInteger> ans;
vii G[B];
bool vis[N][B];
BigInteger UNO, ZERO;
BigInteger memo[N][2];

BigInteger DP(int pos, bool one){
	if(pos == 0) return UNO;
	if(vis[pos][one]) return memo[pos][one];
	BigInteger act = DP(pos-1,1);
	if(one){
		for(int i=0; i<b-2; i++) act.sumar(DP(pos-1,0));
	}
	else{
		for(int i=0; i<b-1; i++) act.sumar(DP(pos-1,0));
	}
	vis[pos][one] = true;
	return memo[pos][one] = act;
}

int main(){
	ZERO.use(0);
	UNO.use(1);
	int tc = 1;
	while(ri2(b,n)==2 and n+b>0){
		G[b].pb(mp(n,tc++));
	}
	ans.resize(tc+2);
	for(int i=4; i<=128; i++){
		if(G[i].size()==0) continue;
		memset(vis,0,sizeof vis);
		b = i;
		for(int j=0; j<G[i].size(); j++){
			BigInteger act = ZERO;
			for(int k=1; k<b; k++){
				act.sumar(DP(G[i][j].first-1,k==1));
			}
			ans[G[i][j].second] = act;
		}
	}
	for(int i=1; i<tc; i++){
		ans[i].Print();
	}
	return 0;
}
