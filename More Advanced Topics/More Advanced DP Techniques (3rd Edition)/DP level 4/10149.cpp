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

const int N = 13+5;


int v[N][7];
int p[(1<<13)+2];
int memo[(1<<13)+2][200];
bool vis[(1<<13)+2][200];
int choice[(1<<13)+2][200];

int evaluate(int pos, int type){
	int ans = 0;
	bool can;
	int q[10];
	switch(type){
		case 0: for(int i=0; i<5; i++) ans += (v[pos][i]==1)*1; break;
		case 1: for(int i=0; i<5; i++) ans += (v[pos][i]==2)*2; break;
		case 2: for(int i=0; i<5; i++) ans += (v[pos][i]==3)*3; break;
		case 3: for(int i=0; i<5; i++) ans += (v[pos][i]==4)*4; break;
		case 4: for(int i=0; i<5; i++) ans += (v[pos][i]==5)*5; break;
		case 5: for(int i=0; i<5; i++) ans += (v[pos][i]==6)*6; break;
		case 6: for(int i=0; i<5; i++) ans += v[pos][i]; break;
		case 7: memset(q,0,sizeof q);
			for(int i=0; i<5; i++){
				ans += v[pos][i];
				q[v[pos][i]]++;
			}
			can = false;
			for(int i=1; i<=6; i++){
				if(q[i]>=3) can = true;
			}
			ans *= can;
			break;
		case 8: memset(q,0,sizeof q);
			for(int i=0; i<5; i++){
				ans += v[pos][i];
				q[v[pos][i]]++;
			}
			can = false;
			for(int i=1; i<=6; i++){
				if(q[i]>=4) can = true;
			}
			ans *= can;
			break;
		case 9: memset(q,0,sizeof q);
			for(int i=0; i<5; i++){
				q[v[pos][i]]++;
			}
			ans = 50;
			can = false;
			for(int i=1; i<=6; i++){
				if(q[i]>=5) can = true;
			}
			ans *= can;
			break;
		case 10: memset(q,0,sizeof q);
			for(int i=0; i<5; i++){
				q[v[pos][i]]++;
			}
			ans = 25;
			can = false;
			for(int i=1; i<=3; i++){
				bool act = true;
				for(int j=0; j<4; j++){
					act = act && q[i+j]>0;
				}
				can = can || act;
			}
			ans *= can;
			break;
		case 11: memset(q,0,sizeof q);
			for(int i=0; i<5; i++){
				q[v[pos][i]]++;
			}
			ans = 35;
			can = false;
			for(int i=1; i<=2; i++){
				bool act = true;
				for(int j=0; j<5; j++){
					act = act && q[i+j]>0;
				}
				can = can || act;
			}
			ans *= can;
			break;
		case 12: memset(q,0,sizeof q);
			for(int i=0; i<5; i++){
				q[v[pos][i]]++;
			}
			ans = 40;
			can = false;
			for(int i=1; i<=6; i++){
				for(int j=i+1; j<=6; j++){
					bool act = false;
					if(q[i]+q[j]==5){
						if(q[i]==2 or q[i]==3) act = true;
					}
					can = can || act;
				}
			}
			ans *= can;
			break;
	}
	return ans;
}

int DP(int libres, int sum){
	if(libres==0){
		return sum>=63?35:0;
	}
	if(vis[libres][sum]) return memo[libres][sum];
	int pos = 13-__builtin_popcount(libres);
	int ans = -1;
	for(int mask=libres; mask>0; mask &= mask-1){
		int type = p[mask&-mask];
		int s = sum;
		if(type < 6) s += evaluate(pos,type);
		int candidate = evaluate(pos,type)+DP(libres^(1<<type),s);
		if(ans < candidate){
			ans = candidate;
			choice[libres][sum] = type;
		}
	}
	vis[libres][sum] = true;
	return memo[libres][sum] = ans;
}

int main(){
	vi ans;
	for(int i=0; i<13; i++) p[1<<i] = i;
	while(ri(v[0][0])==1){
		for(int i=1; i<5; i++) ri(v[0][i]);
		for(int i=1; i<13; i++){
			for(int j=0; j<5; j++) ri(v[i][j]);
		}
		memset(vis,0,sizeof vis);
		int total = DP((1<<13)-1,0);
		ans.assign(15,0);
		ans[14] = total;
		int sl = (1<<13)-1;
		int sum = 0;
		for(int pos=0; pos<13; pos++){
			int type = choice[sl][sum];
			ans[type] = evaluate(pos,type);
			sl ^= 1<<type;
			if(type < 6) sum+=ans[type];
		}
		if(sum >= 63) ans[13] = 35;
		printf("%d",ans[0]);
		for(int i=1; i<15; i++){
			printf(" %d",ans[i]);
		}
		puts("");
	}	
	return 0;
}
