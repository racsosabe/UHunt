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

const int N = 10+5;
const int M = 100+5;

int n, m;
int v[N][M];
int memo[M][N];
bool vis[M][N];
int p[M][N];
int dy[] = {-1,0,1};
vi a;
vi indices;

int DP(int pos, int row){
	if(pos == m-1){
		return v[row][pos];
	}
	if(vis[pos][row]) return memo[pos][row];
	int ans = INT_MAX;
	int start = -1;
	for(int k=0; k<3; k++){
		int next = (row+dy[k]+n)%n;

		if(ans > v[row][pos] + DP(pos+1,next)){
			ans = v[row][pos] + DP(pos+1,next);
			start = next;
		}
		else if(ans == v[row][pos] + DP(pos+1,next)){
			if(next < start) start = next;
		}
	}
	p[pos][row] = start;
	vis[pos][row] = true;
	return memo[pos][row] = ans;
}

int main(){
	while(ri2(n,m)==2){
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				ri(v[i][j]);
			}
		}
		int ans = INT_MAX;
		memset(vis,0,sizeof vis);
		for(int i=0; i<n; i++){
			if(ans > DP(0,i)){
				ans = DP(0,i);
			}
		}
		a.clear();
		indices.clear();
		for(int i=0; i<n; i++){
			int pos = 0;
			int actrow = i;
			vi carry;
			vi ind;
			if(ans == DP(0,i)){
				if(a.size()==0){
					while(pos < m){
						carry.pb(v[actrow][pos]);
						ind.pb(actrow);
						int next = p[pos][actrow];
						pos+=1;
						actrow = next;
					}
					a = carry;
					indices = ind;
				}
			}
		}
		printf("%d",indices[0]+1);
		for(int i=1; i<m; i++) printf(" %d",indices[i]+1);
		puts("");
		cout << ans << endl;
	}
	return 0;
}
