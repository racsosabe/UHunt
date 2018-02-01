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
}

int modInverso(int a, int m){
	int x, y;
	int g = gcdExtendido(a,m,&x,&y);
	if(g!=1) return -1;
	else return (x%m + m)%m;
}

/****************************************
*************P*L*A*N*T*I*L*L*A************
*****************************************/


int m = 6;
int moneda[] = {5, 10, 20, 50, 100, 200};
int q[10];
int x;
bool vis2[100000+5];
bool vis[10][100000+5];
int memo[10][100000+5];
int memo2[100000+5];

int DP2(int val){
	if(val == 0) return 0;
	if(vis2[val]) return memo2[val];
	int ans = INT_MAX;
	for(int i=0; i<m; i++){
		if(val >= moneda[i])
		ans = min(ans,1+DP2(val-moneda[i]));
	}
	vis2[val] = true;
	return memo2[val] = ans;
}

int DP(int pos, int suma){
	if(pos == m){
		if(suma >= x){
			return DP2(suma-x);
		}
		else return (1<<20);
	}
	if(vis[pos][suma]) return memo[pos][suma];
	int ans = DP(pos+1,suma);
	int sum = 0;
	for(int k=1; k<=q[pos]; k++){
		sum += moneda[pos];
		ans = min(ans,k+DP(pos+1,suma+sum));
	}
	vis[pos][suma] = true;
	return memo[pos][suma] = ans;
}

int ReadInt(){
	char c = getchar();
	int ans = 0;
	while(c!='\n'){
		if(c!='.') ans = 10*ans+c-'0';
		c = getchar();
	}
	return ans;
}

int main(){
	while(ri3(q[0],q[1],q[2])==3){
		ri3(q[3],q[4],q[5]);
		getchar();
		bool can = false;
		for(int i=0; i<m; i++) can = can || q[i]>0;
		if(can){
			x = ReadInt();
			memset(vis,0,sizeof vis);
			printf("%3d\n",DP(0,0));
		}
		else break;
	
	}
	return 0;
}
