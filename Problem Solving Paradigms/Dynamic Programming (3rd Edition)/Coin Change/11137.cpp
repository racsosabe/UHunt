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

const int N = 300+5;

bool vis[N][N][N];
ll memo[N][N][N];
ll ans[N][N];
vi query;

ll DP(int pos, int val, int left){
	if(val == 0) return left == 0;
	if(left == 0) return val == 0;
	if(pos == 301) return 0;
	if(vis[pos][val][left]) return memo[pos][val][left];
	ll ans = DP(pos+1,val,left);
	if(val >= pos) ans += DP(pos,val-pos,left-1);
	vis[pos][val][left] = true;
	return memo[pos][val][left] = ans;
}

int main(){
	for(int i=0; i<=300; i++) ans[0][i] = 1;
	for(int i=1; i<=300; i++){
		ans[i][0] = 0;
		ans[i][1] = 1;
		for(int j=2; j<=i; j++){

			ans[i][j] = DP(1,i,j);
			ans[i][j] += ans[i][j-1];
		}
	}
	string s;
	int n,l,r;
	while(getline(cin,s)){
		istringstream is(s);
		query.clear();
		while(is >> n){
			query.pb(n);
		}
		if(query.size() == 1){
			n = query[0];
			printf("%lld\n",ans[n][n]);
		}
		else if(query.size()==2){
			n = query[0];
			l = query[1];
			printf("%lld\n",ans[n][min(n,l)]);
		}
		else{
			n = query[0];
			l = query[1];
			r = query[2];
			if(l > 1)
			printf("%lld\n",ans[n][min(r,n)]-ans[n][min(n,l-1)]);
			else printf("%lld\n",ans[n][min(r,n)]);
		}
	}
	return 0;
}