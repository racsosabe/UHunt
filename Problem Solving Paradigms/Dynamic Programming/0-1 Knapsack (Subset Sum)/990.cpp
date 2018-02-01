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

const int N = 40;

int n;
int t,w;
int d[N];
int q[N];
int memo[N][1005];
int parentp[N][1005];
int parentt[N][1005];

int DP(int pos, int timeleft){
	if(pos == n) return 0;
	if(memo[pos][timeleft]!=-1) return memo[pos][timeleft];
	int ans = DP(pos+1,timeleft);
	parentp[pos][timeleft] = pos+1;
	parentt[pos][timeleft] = timeleft;
	if(timeleft >= 3*w*d[pos]){
		int next_ans = DP(pos+1,timeleft-3*w*d[pos]);
		if(q[pos]+next_ans > ans){
			parentp[pos][timeleft] = pos+1;
			parentt[pos][timeleft] = timeleft-3*w*d[pos];
			ans = q[pos]+next_ans;
		}
	}
	return memo[pos][timeleft] = ans;
}

int main(){
	int tc = 1;
	while(ri2(t,w)==2){
		if(tc++>1) puts("");
		ri(n);
		for(int i=0; i<n; i++){
			ri2(d[i],q[i]);
		}
		memset(memo,-1,sizeof memo);
		memset(parentp,-1,sizeof parentp);
		printf("%d\n",DP(0,t));
		int startp = 0;
		int startt = t;
		int c = 0;
		queue<int> ans;
		while(startp!=n){
			int next_p = parentp[startp][startt];
			int next_t = parentt[startp][startt];
			if(next_t < startt){
				ans.push(d[startp]);
				ans.push(q[startp]);
				c+=1;
			}
			startp = next_p;
			startt = next_t;
		}
		printf("%d\n",c);
		while(!ans.empty()){
			printf("%d ",ans.front());
			ans.pop();
			printf("%d\n",ans.front());
			ans.pop();
		}
	}
	return 0;
}
