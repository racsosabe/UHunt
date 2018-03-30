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

const int N = 130+5;

int n,m;
int bm[N];
bool vis[(1<<11)+5][(1<<11)+5];
int memo[(1<<11)+5][(1<<11)+5];

int DP(int questions_used, int answer_expected){
	int matches = 0;
	for(int i=0; i<n; i++){
		if((bm[i]&questions_used) == answer_expected) matches++;
	}
	if(matches <= 1) return 0;
	if(vis[questions_used][answer_expected]) return memo[questions_used][answer_expected];
	int ans = m+1;
	for(int i=0; i<m; i++){
		if((questions_used>>i)&1) continue;
		ans = min(ans,1+max(DP(questions_used|1<<i,answer_expected),DP(questions_used|1<<i,answer_expected|1<<i)));
	}
	vis[questions_used][answer_expected] = true;
	return memo[questions_used][answer_expected] = ans;
}

int main(){
	char c;
	string s;
	while(ri2(m,n)==2 and n+m>0){
		for(int i=0; i<n; i++){
			bm[i] = 0;
			cin >> s;
			for(int j=0; j<m; j++){
				c = s[j];
				if(c == '1') bm[i] |= 1<<j;
			}
		}
		memset(vis,0,sizeof vis);
		printf("%d\n",DP(0,0));
	}
	return 0;
}
