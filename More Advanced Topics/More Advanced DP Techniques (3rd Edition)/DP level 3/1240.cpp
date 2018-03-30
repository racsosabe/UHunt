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
int v[5][15];
int pos[(1<<12)+5];
int memo[5][285][(1<<12)+5];
bool vis[5][285][(1<<12)+5];
int pl[5][285][(1<<12)+5];
int pt[5][285][(1<<12)+5];
int pd[5][285][(1<<12)+5];

int DP(int last, int left, int not_done){
	if(left == 0 or not_done == 0) return 0;
	if(vis[last][left][not_done]) return memo[last][left][not_done];
	int ans = 0;
	pl[last][left][not_done] = -1;
	for(int i=1; i<=3; i++){
		if(i == last) continue;
		int carry = not_done;
		vi possible;
		while(carry > 0){
			int value = carry&(-carry);
			int problem = pos[value];
			possible.pb(problem);
			if(left >= v[i][problem]){
				if(ans < 1+DP(i,left-v[i][problem],not_done^value)){

					ans = 1+DP(i,left-v[i][problem],not_done^value);
					pl[last][left][not_done] = i;
					pt[last][left][not_done] = left-v[i][problem];
					pd[last][left][not_done] = not_done^value;
				}
			}
			carry &= carry-1;
		}
	}
	vis[last][left][not_done] = true;
	return memo[last][left][not_done] = ans;
}

int main(){
	int t;
	for(int i=0; i<12; i++){
		pos[1<<i] = i;
	}
	ri(t);
	while(t--){
		ri(n);
		for(int i=1; i<=3; i++){
			for(int j=0; j<n; j++){
				ri(v[i][j]);
			}
		}
		memset(vis,0,sizeof vis);
		printf("%d\n",DP(0,280,int(1<<n)-1));
	}
	return 0;
}
