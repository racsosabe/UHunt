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

const int M = 6+5;
const int N = 8+5;

int n, m;
int p[M];
int combos[N][8];
int pc[N];
int query[M];
int c[M];
int memo[N][11][11][11][11][11][11];

int main(){
	int q;
	int q1,q2,q3,q4,q5,q6;
	while(ri(m)==1){
		for(int i=0; i<m; i++) ri(p[i]);
		ri(n);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				ri(combos[i][j]);
			}
			for(int j=m; j<6; j++) combos[i][j] = 0;
			ri(pc[i]);
		}
		for(int c1 = 0; c1 < 10; c1++){
			for(int c2 = 0; c2 < 10; c2++){
				for(int c3 = 0; c3 < 10; c3++){
					for(int c4 = 0; c4 < 10; c4++){
						for(int c5 = 0; c5 < 10; c5++){
							for(int c6 = 0; c6 < 10; c6++){
								memo[n][c1][c2][c3][c4][c5][c6] = c1*p[0]+c2*p[1]+c3*p[2]+c4*p[3]+c5*p[4]+c6*p[5];
							}
						}
					}
				}
			}
		}
		for(int i=n-1; i>=0; i--){
			
			for(int c1 = 9; c1 >= 0; c1--){
			
				for(int c2 = 9; c2 >= 0; c2--){
					
					for(int c3 = 9; c3 >= 0; c3--){

						for(int c4 = 9; c4 >= 0; c4--){

							for(int c5 = 9; c5 >=0; c5--){

								for(int c6 = 9; c6 >= 0; c6--){


									
									c[0] = c1;
									c[1] = c2;
									c[2] = c3;
									c[3] = c4;
									c[4] = c5;
									c[5] = c6;
									int maximum_iteration = INT_MAX;

									for(int k=0; k<m; k++){
										if(combos[i][k]){
											maximum_iteration = min(maximum_iteration,c[k]/combos[i][k]);
										}							
									}
									
									memo[i][c1][c2][c3][c4][c5][c6] = INT_MAX;								
									for(int times = 0; times <= maximum_iteration; times++){

										memo[i][c1][c2][c3][c4][c5][c6] = min(memo[i][c1][c2][c3][c4][c5][c6],memo[i+1][c1-combos[i][0]*times][c2-combos[i][1]*times][c3-combos[i][2]*times][c4-combos[i][3]*times][c5-combos[i][4]*times][c6-combos[i][5]*times]+pc[i]*times);
									}
								}
							}
							
						}
					}
				}
			}
		}
		ri(q);
		while(q--){
			for(int i=0; i<m; i++){
				ri(query[i]);
			}
			for(int i=m; i<6; i++) query[i] = 0;
			q1 = query[0];
			q2 = query[1];
			q3 = query[2];
			q4 = query[3];
			q5 = query[4];
			q6 = query[5];
			printf("%d\n",memo[0][q1][q2][q3][q4][q5][q6]);
		}

	}
	return 0;
}
