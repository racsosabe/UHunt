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

string v[5];
bool vis[5][(1<<16)+5];
int memo[5][(1<<16)+5];
int carry[5][5];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

bool validPos(int i, int j){ return i>=0 and j>=0 and i<4 and j<4;}

vi get(int bitmask){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			int d = 4*i+j;
			carry[i][j] = (bitmask>>d)&1;
		}
	}
	vi answer;
	bool vis[(1<<16)] = {0};
	for(int i=0; i<4; i++){
		
		// ARRIBA
		
		if(carry[0][i]){
			for(int k=0; k<1; k++){
				int d = 4*0+i;
				int steps = 1;
				int act = bitmask^(1<<d);
				int sx = 0;
				int sy = i;
				while(validPos(sx,sy) and carry[sx][sy] and steps < 4){
					if(!vis[act]){
						answer.pb(act);
						vis[act] = true;
					}
					sx += dx[k];
					sy += dy[k];
					steps += 1;
					d = 4*sx + sy;
					act ^= (1<<d);
				}
			}
		}

		// ABAJO
		
		if(carry[3][i]){
			for(int k=1; k<2; k++){
				int d = 4*3+i;
				int steps = 1;
				int act = bitmask^(1<<d);
				int sx = 3;
				int sy = i;
				
				while(validPos(sx,sy) and carry[sx][sy] and steps < 4){
					if(!vis[act]){
						answer.pb(act);
						vis[act] = true;
					}
					sx += dx[k];
					sy += dy[k];
					steps += 1;
					d = 4*sx + sy;
					act ^= (1<<d);
				}
			}
		}

		// DERECHA 
		
		if(carry[i][3]){
			for(int k=3; k<4; k++){
				int d = 4*i+3;
				int steps = 1;
				int act = bitmask^(1<<d);
				int sx = i;
				int sy = 3;
				
				while(validPos(sx,sy) and carry[sx][sy] and steps < 4){
					if(!vis[act]){
						answer.pb(act);
						vis[act] = true;
					}
					sx += dx[k];
					sy += dy[k];
					steps += 1;
					d = 4*sx + sy;
					act ^= (1<<d);
				}
			}
		}

		// IZQUIERDA
		
		if(carry[i][0]){
			for(int k=2; k<3; k++){
				int d = 4*i+0;
				int steps = 1;
				int act = bitmask^(1<<d);
				int sx = i;
				int sy = 0;
				
				while(validPos(sx,sy) and carry[sx][sy] and steps < 4){
					if(!vis[act]){
						answer.pb(act);
						vis[act] = true;
					}
					sx += dx[k];
					sy += dy[k];
					steps += 1;
					d = 4*sx + sy;
					act ^= (1<<d);
				}
			}
		}
		
	}
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(i == 0 or i == 3 or j==0 or j==3) continue;
			if(carry[i][j]){
				int d = 4*i+j;
				answer.pb(bitmask^(1<<d));
			}
		}
	}
	return answer;
}

int DP(int turn, int bitmask){
	if(bitmask == 0) return turn;
	if(vis[turn][bitmask]) return memo[turn][bitmask];
	int ans = 3-turn;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			int d = 4*i+j;
			carry[i][j] = (bitmask>>d)&1;
		}
	}
	vi candidates = get(bitmask);
	for(int i=0; i<candidates.size(); i++){
		if(DP(3-turn,candidates[i]) == turn) ans = turn;
	}
	vis[turn][bitmask] = true;
	return memo[turn][bitmask] = ans;
}

int main(){
	int t;
	ri(t);
	char c;
	while(t--){
		int start = 0;
		for(int i=0; i<4; i++){
			cin >> v[i];
			for(int j=0; j<4; j++){
				int d = 4*i+j;
				if(v[i][j] != 'X') start |= (1<<d);
			}
		}
		puts(DP(1,start)==1?"WINNING":"LOSING");
	}
	return 0;
}
