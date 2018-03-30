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


int n,k,m;
bool p[1200];
int memo[1200][20][200];
vi primos;

void init(){
	for(int i=2; i*i<1200; i++){
		if(!p[i]){
			for(int j=i*i; j<1200; j+=i){
				p[j] = true;
			}
		}
	}
	for(int i=2; i<1200; i++){
		if(!p[i]) primos.pb(i);
	}
}

int DP(int left, int choose, int pos){
	if(choose == 0 and left == 0) return 1;
	if(choose == 0 and left>0) return 0;
	if(pos == m) return int(choose==0 and left==0);
	if(memo[left][choose][pos]!=-1) return memo[left][choose][pos];
	int ans = DP(left,choose,pos+1);
	if(left >= primos[pos] and choose>=1){
		ans += DP(left-primos[pos],choose-1,pos+1);
	}
	return memo[left][choose][pos] = ans;
}

int main(){
	init();
	m = primos.size();
	while(ri2(n,k)==2 and n+k!=0){
		memset(memo,-1,sizeof memo);
		printf("%d\n",DP(n,k,0));
	}
	return 0;
}
