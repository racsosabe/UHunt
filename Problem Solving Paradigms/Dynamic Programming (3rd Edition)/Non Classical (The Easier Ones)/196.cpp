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
const int M = 18280 + 5;

int n, m;
int cols = 0;
map<string,int> col;
string v[N][M];
map<ii,bool> vis;
int memo[N][M];

int val(string s){
	int ans = 0;
	for(int i=0; i<s.size(); i++){
		ans = 10*ans + s[i]-'0';
	}
	return ans;
}

int DP(int i, int j){
	if(vis[mp(i,j)]) return memo[i][j];
	int ans = 0;
	string r = "";
	string c = "";
	for(int k=1; k<v[i][j].size(); k++){
		if(v[i][j][k]=='+'){
			ans += DP(val(r)-1,col[c]);
			r = "";
			c = "";
		}
		else if(v[i][j][k]>='A' and v[i][j][k] <= 'Z'){
			c = c + v[i][j][k];
		}
		else{
			r = r + v[i][j][k];
		}
	}
	ans += DP(val(r)-1,col[c]);
	vis[mp(i,j)] = true;
	return memo[i][j] = ans;
}

int main(){
	for(char i='A'; i<='Z'; i++){
		string carry = "";
		carry = carry + i;
		col[carry] = cols++;
	}
	for(char i='A'; i<='Z'; i++){
		for(char j='A'; j<='Z'; j++){
			string carry = "";
			carry = carry + i + j;
			col[carry] = cols++;
		}
	}
	for(char i='A'; i<='Z'; i++){
		for(char j='A'; j<='Z'; j++){
			for(char k='A'; k<='Z'; k++){
				string carry = "";
				carry = carry + i + j + k;
				col[carry] = cols++;
			}
		}
	}
	int t;
	ri(t);
	string s;
	while(t--){
		vis.clear();
		ri2(m,n);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				cin >> s;
				if(s[0]!='='){
					vis[mp(i,j)] = true;
					memo[i][j] = val(s);
				}
				else{
					v[i][j] = s;
				}
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(v[i][j][0] == '='){
					memo[i][j] = DP(i,j);
				}
			}
		}
		for(int i=0; i<n; i++){
			printf("%d",memo[i][0]);
			for(int j=1; j<m; j++){
				printf(" %d",memo[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
