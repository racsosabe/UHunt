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
const int TAM = 64001+5;
const int Move = 32000;

int n, x;
int v[N];
bool memo[N][TAM];
bool vis[N][TAM];
char choice[N][TAM];

bool DP(int pos, int value){
	if(pos == n) return value==x+Move;
	if(vis[pos][value]) return memo[pos][value];
	bool ans = false;
	int actual_value = value-Move;
	if(actual_value%v[pos]==0){
		if(DP(pos+1,actual_value/v[pos]+Move)){
			ans = true;
			choice[pos][value] = '/';
		}
	}
	if(actual_value+v[pos] <= 32000 and actual_value+v[pos]>=-32000){
		if(DP(pos+1,actual_value+v[pos]+Move)){
			ans = true;
			choice[pos][value] = '+';
		}
	}
	if(actual_value-v[pos] <= 32000 and actual_value-v[pos]>=-32000){
		if(DP(pos+1,actual_value-v[pos]+Move)){
			ans = true;
			choice[pos][value] = '-';
		}
	}
	if(actual_value*v[pos] <= 32000 and actual_value*v[pos]>=-32000){
		if(DP(pos+1,actual_value*v[pos]+Move)){
			ans = true;
			choice[pos][value] = '*';
		}
	}
	vis[pos][value] = true;
	return memo[pos][value] = ans;
}

int main(){
	int t;
	ri(t);
	while(t--){
		ri(n);
		for(int i=0; i<n; i++){
			ri(v[i]);
		}
		ri(x);
		memset(vis,0,sizeof vis);
		if(DP(1,v[0]+Move)){
			int value = v[0]+Move;
			printf("%d",v[0]);
			for(int i=1; i<n; i++){
				char x = choice[i][value];
				printf("%c",x);
				int actual_value = value-Move;
				switch(x){
					case '/': actual_value /= v[i];
						  break;
					case '+': actual_value += v[i];
						  break;
					case '-': actual_value -= v[i];
						  break;
					case '*': actual_value *= v[i];
						  break;
				}
				value = actual_value + Move;
				printf("%d",v[i]);
			}
			printf("=%d\n",x);
		}
		else puts("NO EXPRESSION");
	}
	return 0;
}
