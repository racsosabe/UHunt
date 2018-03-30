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

const int S = 8+5;
const int N = 100+5;
const int MAX = 20000;

int s,m,n;
int p[S];
int precio[N];
int v[N];
char last;
bool vis[N][MAX];
int memo[N][MAX];

int restar(int a, int b){
	int v[S] = {0};
	int pos = 0;
	while(a){
		v[pos++] = a%3;
		a /= 3;
	}
	int pos2 = 0;
	while(b){
		v[pos2] = max(v[pos2]-b%3,0);
		pos2 += 1;
		b /= 3;
	}
	int ans = 0;
	for(int i=s-1; i>=0; i--){
		ans = 3*ans + v[i];
	}
	return ans;
}

int ReadInt(){
	char c = getchar();
	last = c;
	int x = 0;
	while(c!='\n' and c!=' '){
		x = (x<<3)+(x<<1)+c-'0';
		c = getchar();
		last = c;
	}
	return x;
}

int DP(int pos, int mask){
	if(mask == 0) return 0;
	if(pos == n) return (1<<20);
	if(vis[pos][mask]) return memo[pos][mask];
	int ans = min(DP(pos+1,mask),precio[pos]+DP(pos+1,restar(mask,v[pos])));
	vis[pos][mask] = true;
	return memo[pos][mask] = ans;
}

int main(){
	int x;
	p[0] = 1;
	for(int i=1; i<S; i++){
		p[i] = p[i-1]*3;
	}
	last = ' ';
	while(ri3(s,m,n)==3 and s>0){
		int S = 0;
		int mask = 0;
		for(int i=0; i<s; i++){
			mask += 2*p[i];
		}
		for(int i=0; i<m; i++){
			ri(x);
			S += x;
			last = getchar();
			while(last!='\n'){
				x = ReadInt();
				x--;
				mask = restar(mask,p[x]);
			}
		}
		for(int i=0; i<n; i++){
			ri(precio[i]);
			last = getchar();
			v[i] = 0;
			while(last!='\n'){
				x = ReadInt();
				x--;
				v[i] += p[x];
			}
		}
		memset(vis,0,sizeof vis);
		printf("%d\n",S+DP(0,mask));
	}
	return 0;
}
