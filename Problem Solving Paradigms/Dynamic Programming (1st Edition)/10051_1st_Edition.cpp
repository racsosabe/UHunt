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

const int N = 500+5;

int n;
string face[] = {"front","back","left","right","top","bottom"};
int v[N][7];
int memo[N][7];
int face_parent[N][7];
int index_parent[N][7];
int bottom[] = {1,0,3,2,5,4};

int main(){
	int caso = 1;
	while(ri(n)==1 and n!=0){
		if(caso > 1) puts("");
		for(int i=0; i<n; i++){
			for(int j=0; j<6; j++){
				ri(v[i][j]);
			}
		}
		int ans = 1;
		for(int i=0; i<6; i++){
			memo[0][i] = 1;
			index_parent[0][i] = -1;
		}
		int start_i = 0;
		int start_c = 0;
		for(int i=1; i<n; i++){
			for(int j=0; j<6; j++){
				memo[i][j] = 1;
				index_parent[i][j] = -1;
			}
			for(int b_i = 0; b_i < 6; b_i++){
				for(int j=0; j<i; j++){
					for(int c_j = 0; c_j < 6; c_j++){
						if(v[j][c_j] == v[i][b_i]){
							if(memo[i][bottom[b_i]] < memo[j][c_j]+1){
								memo[i][bottom[b_i]] = memo[j][c_j]+1;
								face_parent[i][bottom[b_i]] = c_j;
								index_parent[i][bottom[b_i]] = j;
							}
						}
					}
				}
			}
			for(int j=0; j<6; j++){
				if(ans < memo[i][bottom[j]]){
					ans = memo[i][bottom[j]];
					start_i = i;
					start_c = bottom[j];
				}
				
			}
		}
		printf("Case #%d\n",caso++);
		cout << ans << endl;
		stack<int> S;
		while(start_i!=-1){
			S.push(start_i);
			S.push(start_c);
			int next_i = index_parent[start_i][start_c];
			int next_c = face_parent[start_i][start_c];
			start_i = next_i;
			start_c = next_c;
		}
		while(!S.empty()){
			start_c = S.top(); S.pop();
			start_i = S.top(); S.pop();
			printf("%d ",start_i+1);
			cout << face[bottom[start_c]] << endl;
		}
	}
	return 0;
}
