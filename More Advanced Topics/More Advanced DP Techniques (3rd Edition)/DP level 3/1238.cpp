#include<bits/stdc++.h>
#include<stdio.h>
#include<string.h>
#include<cstdio>
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

const int N = 30+5;
const int MAX = 6000+5;

int n;
int v[N];
int signo[N];
bool vis[N][N][MAX];
bool can[MAX];

void DP(int pos, int abren, int sum){
	if(pos == n){
		can[sum] = true;
		return;
	}
	if(vis[pos][abren][sum]) return;
	if(abren > 0){
		if(abren&1){
			DP(pos+1,abren,sum-signo[pos]*v[pos]);
			DP(pos+1,abren-1,sum-signo[pos]*v[pos]);
			if(signo[pos] == -1) DP(pos+1,abren+1,sum+v[pos]);
		}
		else{
			DP(pos+1,abren,sum+signo[pos]*v[pos]);
			DP(pos+1,abren-1,sum+signo[pos]*v[pos]);
			if(signo[pos] == -1) DP(pos+1,abren+1,sum-v[pos]);
		}
	}
	else{
		DP(pos+1,abren,sum+signo[pos]*v[pos]);
		if(signo[pos] == -1) DP(pos+1,abren+1,sum-v[pos]);
	}
	vis[pos][abren][sum] = true;
}

int main(){
	string s;
	int x;
	char buff[1000];
	while(fgets(buff,1000,stdin)){
		n = 0;
		int len = strlen(buff);
		for(int i=0; i<len-1; ){
			while(buff[i]==' ') i+=1;
			if('0' <= buff[i] and buff[i] <='9'){
				x = 0;
				while('0' <= buff[i] and buff[i] <= '9'){
					x = (x<<3) + (x<<1) + buff[i]-'0';
					i++;
				}
				v[n++] = x;
			}
			else if(buff[i] == '+'){
				signo[n] = 1;
				i++;
			}
			else if(buff[i] == '-'){
				signo[n] = -1;
				i++;
			}
		}
		memset(vis,0,sizeof vis);
		memset(can,0,sizeof can);
		signo[0] = 1;
		DP(0,0,3000);
		int ans = 0;
		for(int i=0; i<MAX; i++){
			ans += can[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
