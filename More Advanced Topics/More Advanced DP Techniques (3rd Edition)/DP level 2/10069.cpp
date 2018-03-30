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

const int N = 10000+5;
const int M = 100+5;

class BigInteger{
	int len;
	vi a;
	public:
	BigInteger(){
		len = 0;
		a.clear();
	}
	
	void use(int x){
		len = 0;
		if(x == 0){
			len = 1;
			a.pb(0);
			return;
		}
		while(x){
			a.pb(x%10);
			x /= 10;
			len += 1;
		}
	}

	void add(BigInteger b){
		int sum_lens = max(b.len,len);
		vi carry;
		carry.resize(sum_lens);
		for(int i=0; i<min(b.len,len); i++){
			carry[i] = b.a[i] + a[i];
		}
		if(b.len > len){
			for(int i=len; i<b.len; i++){
				carry[i] = b.a[i];
			}
		}
		else{
			for(int i=b.len; i<len; i++){
				carry[i] = a[i];
			}
		}
		for(int i=0; i<sum_lens-1; i++){
			if(carry[i] > 9){
				carry[i+1] += carry[i]/10;
				carry[i] %= 10;
			}
		}
		if(carry[sum_lens-1] > 9){
			carry.pb(carry[sum_lens-1]/10);
			carry[sum_lens-1] %= 10;
			sum_lens += 1;
		}
		len = sum_lens;
		a = carry;
	}

	void Print(){
		for(int i=len-1; i>=0; i--){
			putchar('0'+a[i]);
		}
		puts("");
	}

};

int n, m;
string a;
string b;
BigInteger UNO, ZERO;
BigInteger memo[N][M];
bool vis[N][M];

BigInteger DP(int posa, int last_b){
	if(posa == n) return last_b == m?UNO:ZERO;
	if(vis[posa][last_b]) return memo[posa][last_b];
	BigInteger ans = DP(posa+1,last_b);
	if(last_b < m and a[posa] == b[last_b]) ans.add(DP(posa+1,last_b+1));
	vis[posa][last_b] = true;
	return memo[posa][last_b] = ans;
}

int main(){
	UNO.use(1);
	ZERO.use(0);
	int t;
	ri(t);
	getline(cin,a);
	while(t--){
		getline(cin,a);
		getline(cin,b);
		n = a.size();
		m = b.size();
		memset(vis,0,sizeof vis);
		BigInteger ans = DP(0,0);
		ans.Print();
	}
	return 0;
}
