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

const int N = 2050;

int n, m;
int v[N];
bool primero;
int l[12][N];
int r[12][N];
int val[12][N];

void traverse(int depth, int pos){
	if(depth == 0){
		if(primero) printf("%d",val[depth][pos]);
		else printf(" %d",val[depth][pos]);
		primero = false;
		return;
	}
	traverse(depth-1,l[depth][pos]);
	traverse(depth-1,r[depth][pos]);
}

int main(){
	int x;
	while(ri(n)==1 and n!=0){
		m = int(n<<1)-1;
		for(int i=0; i<m; i++) ri(v[i]);
		for(int i=0; i<m; i++){
			l[0][i] = i;
			r[0][i] = i;
			val[0][i] = v[i];
		}
		int depth = 1;
		while(m > 1){
			int impar = -1, par = -1, nodos = 0;
			for(int i=0; i<m; i++){
				if(val[depth-1][i]&1){
					if(impar == -1){
						impar = i;
					}
					else{
						l[depth][nodos] = impar;
						r[depth][nodos] = i;
						int x = (val[depth-1][impar]+val[depth-1][i])/2;
						val[depth][nodos] = x;
						nodos+=1;
						impar = -1;
					}
				}
				else{
					if(par == -1){
						par = i;
					}
					else{
						l[depth][nodos] = par;
						r[depth][nodos] = i;
						int x = (val[depth-1][par]+val[depth-1][i])/2;
						val[depth][nodos] = x;
						nodos += 1;
						par = -1;
					}
				}
			}
			m >>= 1;
			depth += 1;
		}
		primero = true;
		puts("Yes");
		traverse(depth-1,0);
		puts("");
	}
	return 0;
}
