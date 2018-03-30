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

const int N = 1000+5;

int n, m;
int OSSouth[N], priceSouth[N];
int OSNorth[N], priceNorth[N];
map<string,int> OS;
ii memo[N][N];
int pi[N][N];
int pj[N][N];

bool validPos(int i, int j){
	return i>=0 and i<n and j>=0 and j<m;
}

int main(){
	int t;
	ri(t);
	string s;
	int os;
	while(t--){
		ri(n);
		OS.clear();
		os = 1;
		for(int i=0; i<n; i++){
			cin >> s;
			cin >> s >> priceSouth[i];
			if(OS[s]==0){
				OS[s] = os++;
			}
			OSSouth[i] = OS[s];
		}
		ri(m);
		for(int i=0; i<m; i++){
			cin >> s;
			cin >> s >> priceNorth[i];
			if(OS[s] == 0){
				OS[s] = os++;
			}
			OSNorth[i] = OS[s];
		}
		
		for(int i=0; i<=n; i++) memo[i][m] = mp(0,0);
		for(int i=0; i<=m; i++) memo[n][i] = mp(0,0);

		for(int i=n-1; i>=0; i--){
			for(int j=m-1; j>=0; j--){
				memo[i][j] = mp(-1,0);
				if(OSSouth[i] == OSNorth[j]){
					if(memo[i][j].first < priceSouth[i]+priceNorth[j]+memo[i+1][j+1].first){
						memo[i][j] = mp(priceSouth[i]+priceNorth[j]+memo[i+1][j+1].first,memo[i+1][j+1].second+1);
					}
					else if(memo[i][j].first == priceSouth[i]+priceNorth[j]+memo[i+1][j+1].first){
						memo[i][j].second = min(memo[i][j].second,memo[i+1][j+1].second+1);
					}
				}
				if(memo[i][j].first < memo[i+1][j].first){
					memo[i][j] = memo[i+1][j];
				}
				else if(memo[i][j].first == memo[i+1][j].first){
					memo[i][j].second = min(memo[i][j].second,memo[i+1][j].second);
				}
				if(memo[i][j].first < memo[i][j+1].first){
					memo[i][j] = memo[i][j+1];
				}
				else if(memo[i][j].first == memo[i][j+1].first){
					memo[i][j].second = min(memo[i][j].second,memo[i][j+1].second);
				}
			}
		}		
		printf("%d %d\n",memo[0][0].first,memo[0][0].second);
	}
	return 0;
}
