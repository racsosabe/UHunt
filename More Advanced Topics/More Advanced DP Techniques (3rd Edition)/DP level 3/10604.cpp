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

const int M = 10;
const int N = 2000000;

int m, k;
int type[M][M];
int heat[M][M];
int q[M];
int memo[N];
bool vis[N];

int DP(int mascara){
	int carry[M];
	int mask = mascara;
	int pos = 0;
	int sum = 0;
	for(int i=0; i<m; i++) carry[i] = 0;
	while(mask){
		carry[pos++] = mask % 11;
		sum += mask%11;
		mask /= 11;
	}
	if(sum == 1) return 0;
	if(vis[mascara]) return memo[mascara];
	int ans = INT_MAX;
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			if((i!=j and carry[i]>0 and carry[j]>0) or (i == j and carry[i]>1)){
				int new_one = type[i][j];
				int h = heat[i][j];
				int new_mascara = 0;
				int siz;
				for(int k=m-1; k>=0; k--){
					siz = carry[k];
					if(k == i) siz -=1;
					if(k == j) siz -=1;
					if(new_one == k) siz += 1;
					new_mascara = 11*new_mascara + siz;
				}
				ans = min(ans,h+DP(new_mascara));
			}
		}
	}
	vis[mascara] = true;
	return memo[mascara] = ans;
}

int main(){
	int x;
	char endline;
	int t;
	ri(t);
	while(t--){
		ri(m);
		for(int i=0; i<m; i++){
			q[i] = 0;
			for(int j=0; j<m; j++){
				ri2(type[i][j],heat[i][j]);
				type[i][j]-=1;
			}
		}
		ri(k);
		for(int i=0; i<k; i++){
			ri(x);
			x--;
			q[x] += 1;
		}
		cin >> endline;
		int mask = 0;
		for(int i=m-1; i>=0; i--){
			mask = 11*mask + q[i];
		}
		memset(vis,0,sizeof vis);
		printf("%d\n",DP(mask));
	}
	return 0;
}
