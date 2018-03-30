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

const int N = 50+5;
const int B = 20+5;

struct nodo{
	int sum;
	set<int> values;
	nodo(){};
};

int n;
vi v[N];
nodo ZERO;
nodo memo[N];
bool vis[N];

nodo DP(int pos){
	if(pos == n) return ZERO;
	if(vis[pos]) return memo[pos];
	nodo ans;
	vi carry;
	int S = 0;
	int max_value = 0;
	for(int i=0; i<v[pos].size(); i++){
		int cuantos = i+1;
		S += 10 - v[pos][i];
		if(max_value < S){
			max_value = S;
			carry.clear();
			carry.pb(cuantos);
		}
		else if(max_value == S){
			carry.pb(cuantos);
		}
	}
	if(max_value == 0) carry.pb(0);
	nodo c = DP(pos+1);
	ans.sum = c.sum + max_value;
	for(int i=0; i<carry.size(); i++){
		for(set<int>::iterator it=c.values.begin(); it!=c.values.end(); it++){
			ans.values.insert(*it+carry[i]);
		}
	}
	vis[pos] = true;
	return memo[pos] = ans;
}

int main(){
	int x,w;
	ZERO.sum = 0;
	ZERO.values.clear();
	ZERO.values.insert(0);
	int caso = 1;
	while(ri(n)==1 and n!=0){
		if(caso > 1) puts("");
		for(int i=0; i<n; i++){
			ri(w);
			v[i].clear();
			for(int j=0; j<w; j++){
				ri(x);
				v[i].pb(x);
			}
		}
		memset(vis,0,sizeof vis);
		nodo ans = DP(0);
		printf("Workyards %d\n",caso++);
		printf("Maximum profit is %d.\n",ans.sum);
		printf("Number of pruls to buy:");
		int p = 0;
		for(set<int>::iterator it=ans.values.begin(); it!=ans.values.end() and p<10; it++){
			printf(" %d",*it);
			p+=1;
		}
		puts("");
	}
	return 0;
}
