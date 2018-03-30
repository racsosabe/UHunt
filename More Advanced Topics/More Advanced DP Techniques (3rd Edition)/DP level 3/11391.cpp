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

const int N = 16+5;

int r,c,n;
ll memo[N][(1<<16)+5];
bool vis[N][(1<<16)+5];
int dx[] = {1,1,1,0,0,-1,-1,-1};
int dy[] = {1,0,-1,1,-1,1,0,-1};

bool validPos(int i, int j){ return i>=0 and j>=0 and i<r and j<c;}

ll DP(int left, int mask){
	if(left == 0) return __builtin_popcount(mask)==1;
	if(vis[left][mask]) return memo[left][mask];
	ll ans = 0;
	int tabla[5][5];
	for(int i=0; i<r ;i++){
		for(int j=0; j<c; j++){
			int p = i*c + j;
			tabla[i][j] = (mask>>p)&1;
		}
	}
	for(int x=0; x<r; x++){
		for(int y=0; y<c; y++){
			if(!tabla[x][y]) continue;
			for(int i=0; i<8; i++){
				if(validPos(x+dx[i],y+dy[i])){
					if(tabla[x+dx[i]][y+dy[i]]){
						if(validPos(x+2*dx[i],y+2*dy[i])){
							if(tabla[x+2*dx[i]][y+2*dy[i]]==0){
								int original = x*c+y;
								int p = (x+2*dx[i])*c + y+2*dy[i];
								int off = (x+dx[i])*c + y+dy[i];
								ans += DP(left-1,mask^(1<<off)^(1<<original)|1<<p);
							}
						}
					}
				}
			}
		}
	}
	vis[left][mask] = true;
	return memo[left][mask] = ans;
}

int main(){
	int t;
	ri(t);
	int mask;
	int x,y;
	for(int caso=1; caso<=t; caso++){
		ri3(r,c,n);
		mask = 0;
		for(int i=0; i<n; i++){
			ri2(x,y);
			x--; y--;
			int pos = x*c + y;
			mask |= 1<<pos;
		}
		memset(vis,0,sizeof vis);
		printf("Case %d: %lld\n",caso,DP(n-1,mask));
	}
	return 0;
}
